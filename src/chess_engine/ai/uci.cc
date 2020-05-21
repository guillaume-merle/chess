#include <fnmatch.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "search.hh"
#include "uci.hh"
#include "move-ordering.hh"
#include "zobrist.hh"
#include "logger.hh"

namespace ai
{
    namespace
    {
        std::string get_input(const std::string& expected = "*")
        {
            // Get a command following the expected globbing
            // Ignoring all unrecognized commands
            std::string buffer;
            do
            {
                std::getline(std::cin, buffer);
                if ("quit" == buffer || "stopuci" == buffer)
                    exit(0);
            } while (fnmatch(expected.c_str(), buffer.c_str(), 0));
            return buffer;
        }
    } // namespace

    void init(const std::string& name)
    {
        get_input("uci");
        std::cout << "id name " << name << '\n';
        std::cout << "id author " << name << '\n';
        std::cout << "uciok" << std::endl;
        get_input("isready");
        std::cout << "readyok" << std::endl;
    }

    void play_move(const std::string& move)
    {
        // Send the computed move
        std::cout << "bestmove " << move << std::endl;
    }

    std::string get_board()
    {
        auto board = get_input("position *"); // Get the board
        get_input("go *"); // Wait for a go from GUI
        return board;
    }

    void start()
    {
        Search search;
        Chessboard& board = search.get_board();

        std::string input_position = get_board();
        parse_uci_position(input_position, board);

        search.add_board_disposition(board.get_zobrist_key().get());

        board::Move move = search.find_move();

        play_move(move.to_string());
        board.do_move(move);

        search.add_board_disposition(board.get_zobrist_key().get());

        while (true)
        {
            std::string input_position = get_board();
            parse_uci_position(input_position, board);

            search.add_board_disposition(board.get_zobrist_key().get());

            board::Move move = search.find_move();

            play_move(move.to_string());
            board.do_move(move);

            search.add_board_disposition(board.get_zobrist_key().get());
        }
    }

    void parse_uci_position(std::string& input, board::Chessboard& board)
    {
        std::string token;
        std::istringstream input_stream(input);

        // remove token position
        input_stream >> token;

        input_stream >> token;

        if (token == "startpos")
        {
            board::FenObject fen_obj = perft_parser::parse_fen(START_POS);
            board.set_from_fen(fen_obj);
        }

        else
        {
            std::string fen;

            while (input_stream >> token && token != "moves")
            {
                fen += token + " ";
            }

            board::FenObject fen_obj = perft_parser::parse_fen(fen);
            board.set_from_fen(fen_obj);
        }
        while (input_stream >> token)
        {
            if (token == "moves")
            {
                continue;
            }

            std::vector<board::Move> moves = board.generate_legal_moves();

            for (auto& move : moves)
            {
                if (move.to_string() == token)
                {
                    board.do_move(move);
                    break;
                }
            }
        }
    }

} // namespace ai

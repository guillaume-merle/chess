#include "search.hh"
#include "uci.hh"

#include <fnmatch.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

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
        board::Chessboard board;

        std::string input_position = get_board();
        parse_uci_position(input_position, board);
        board::Move move = board::search_move(board);
        play_move(move.to_string());
        board.do_move(move);

        while (!board.is_checkmate(board.current_color())
               && !board.is_draw(board.current_color()))
        {
            std::string input_position = get_board();
            parse_uci_position(input_position, board);
            board::Move move = board::search_move(board);
            play_move(move.to_string());
            board.do_move(move);
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
            board::FenObject fen_obj = perft_parser::parse_fen(
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
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

            for (board::Move move : moves)
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

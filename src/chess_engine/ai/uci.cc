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

    board::PerftObject parse_uci_perft(std::string& input)
    {
        std::istringstream input_stream(input);
        std::vector<std::string> splited_input;
        std::string token;

        while (input_stream >> token)
        {
            splited_input.emplace_back(token);
        }
        
        return board::PerftObject(perft_parser::parse_fen(splited_input),
                std::stoi(splited_input.back()));
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
            std::string startpos = 
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            board::PerftObject perft_obj = parse_uci_perft(startpos);
            board.set_from_fen(perft_obj.fen_get());
        }   
        else
        {
            // remove token fen
            input_stream >> token;

            std::string fen;

            while (input_stream >> token && token != "moves")
            {
                fen += token + " ";
            }

            board::PerftObject perft_obj = parse_uci_perft(fen);
            board.set_from_fen(perft_obj.fen_get());

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

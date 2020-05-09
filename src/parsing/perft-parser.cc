#include <fstream>
#include <iostream>

#include "perft-parser.hh"

namespace perft_parser
{
    board::PerftObject parse_perft(std::string input)
    {
        std::vector<std::string> splited_input;

        std::ifstream file(input);
        if (!file.is_open())
        {
            std::cerr << "Failed to open" << std::endl;
            //TODO error
        }
        for(std::string line; getline(file, line, ' ');)
        {
            splited_input.push_back(line);
        }
        return board::PerftObject(parse_fen(splited_input), 0); //TODO depth
    }

    board::FenObject parse_fen(std::vector<std::string> splited_input)
    {
        std::vector<board::FenRank> ranks;
        board::Color side_to_move;
        std::vector<char> castling;

        //piece placement
        for (size_t i = 0; i < splited_input[0].size(); ++i)
        {
            //ranks.push_back(); TODO
        }


        //side to move
        if (splited_input[1][0] == 'w')
            side_to_move = board::Color::WHITE;
        else
            side_to_move = board::Color::BLACK;

        //castling ability
        for (size_t i = 0; i < splited_input[2].size(); ++i)
        {
            castling.push_back(splited_input[2][i]);
        }

        //en passant target square
        board::File file;
        board::Rank rank;

        if (splited_input[3][0] == '-')
        {
            file = board::File::A;
            rank = board::Rank::ONE;
        }
        /*else
        {
            board::File file;
            board::Rank rank;
        }*/
        board::Position en_passant_target = board::Position(file, rank);

        return board::FenObject(ranks, side_to_move, castling, en_passant_target);
    }
} // namespace perft_parser

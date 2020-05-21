#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <iterator>

#include "perft-parser.hh"

namespace perft_parser
{
    static board::FenObject parse_fen(std::vector<std::string> splited_input)
    {
        //piece placement
        std::vector<board::FenRank> ranks;

        size_t pos = 0;
        std::string placement = splited_input[0];
        std::string token;
        while ((pos = placement.find('/')) != std::string::npos)
        {
            token = placement.substr(0, pos);
            ranks.push_back(board::FenRank(token));
            placement.erase(0, pos + 1);
        }

        ranks.push_back(board::FenRank(placement));

        //side to move
        board::Color side_to_move;

        if (splited_input[1][0] == 'w')
            side_to_move = board::Color::WHITE;
        else
            side_to_move = board::Color::BLACK;

        //castling ability
        std::vector<char> castling;

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
        else
        {
            switch (splited_input[3][0])
            {
            case 'a':
                file = board::File::A;
                break;
            case 'b':
                file = board::File::B;
                break;
            case 'c':
                file = board::File::C;
                break;
            case 'd':
                file = board::File::D;
                break;
            case 'e':
                file = board::File::E;
                break;
            case 'f':
                file = board::File::F;
                break;
            case 'g':
                file = board::File::G;
                break;
            case 'h':
                file = board::File::H;
                break;
            default:
                std::cerr << "Error in en passant Fen parsing." << std::endl;
                file = board::File::A; //TODO
            }

            if (splited_input[3][1] == '3')
                rank = board::Rank::THREE;
            else
                rank = board::Rank::SIX;
        }
        board::Position en_passant_target = board::Position(file, rank);

        return board::FenObject(ranks, side_to_move, castling,
                                en_passant_target);
    }

    board::FenObject parse_fen(std::string fen)
    {
        std::istringstream iss(fen);
        std::vector<std::string> splited((
                    std::istream_iterator<std::string>(iss)),
                    std::istream_iterator<std::string>());

        return parse_fen(splited);
    }


    board::PerftObject parse_perft(std::string input)
    {
        std::vector<std::string> splited_input;

        std::ifstream file(input);

        if (!file.is_open())
        {
            throw std::invalid_argument("Failed to open perft file.");
        }

        for (std::string line; getline(file, line, ' ');)
        {
            splited_input.push_back(line);
        }

        return board::PerftObject(parse_fen(splited_input),
                                            std::stoi(splited_input.back()));
    }

} // namespace perft_parser

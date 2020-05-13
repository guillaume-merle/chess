#include <string>
#include <iostream>

#include "fen-rank.hh"

namespace board
{
    FenRank::FenRank(std::string rank)
    {
        for (size_t i = 0; i < rank.size(); ++i)
        {
            if (rank[i] >= 'a')
            {
                //black
                Color color = Color::BLACK;
                PieceType piece = char_to_black_piece(rank[i]);
                side_piece_t side_piece = std::make_pair(piece, color);
                pieces_.push_back(side_piece);
            }
            else if (rank[i] < 'A')
            {
                int empty_squares = rank[i] - '0';
                side_piece_t side_piece = std::make_pair(ALL, BLACK);

                for (int i = 0; i < empty_squares; i++)
                    pieces_.push_back(side_piece);
            }
            else
            {
                //white
                Color color = Color::WHITE;
                PieceType piece = char_to_piece(rank[i]);
                side_piece_t side_piece = std::make_pair(piece, color);
                pieces_.push_back(side_piece);
            }
        }
    }

    FenRank::side_piece_t FenRank::operator[](int file)
    {
        return pieces_.at(file);
    }

    size_t FenRank::size()
    {
        return pieces_.size();
    }

} // namespace board

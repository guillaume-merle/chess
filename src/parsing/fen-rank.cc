#include "fen-rank.hh"

namespace board
{
    
    FenRank::FenRank(std::string rank)
    {
        for (size_t i = 0; i < rank.size(); ++i)
        {
            if (rank[i] > 90)
            {
                //black
                Color color = Color::BLACK;
                PieceType piece = char_to_black_piece(rank[i]);
                side_piece_t side_piece = std::make_pair(piece, color);
                pieces_.push_back(side_piece);
            }
            else if (rank[i] < 65)
            {
                //number
                continue;
            }
            else
            {
                //white
                Color color = Color::WHITE;
                PieceType piece = char_to_piece(rank[i]);
                side_piece_t side_piece = std::make_pair(piece, color);
                pieces_.push_back(side_piece);
                
                //pieces_.push_back(std::pair<piece, color>);
            }
        }
    }

    
    //operator[] TODO

} // namespace board

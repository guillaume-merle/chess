#include "king.hh"

namespace board
{
    std::vector<Move>
    King::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Chessboard board;
        return generate_moves(moves, bitboard, board);
    }

    std::vector<Move>
    King::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                   Chessboard& board, Color color)
    {
        add_move(moves, bitboard, north(bitboard, 1), PieceType::KING, color,
                 board);

        add_move(moves, bitboard, south(bitboard, 1), PieceType::KING, color,
                 board);

        // check if the king is not on the left side
        if ((EmptyFileABB & bitboard) != 0)
        {
            add_move(moves, bitboard, west(bitboard, 1), PieceType::KING, color,
                     board);

            add_move(moves, bitboard, northwest(bitboard, 1), PieceType::KING,
                     color, board);

            add_move(moves, bitboard, southwest(bitboard, 1), PieceType::KING,
                     color, board);
        }

        // check if the king is not on the right side
        if ((EmptyFileHBB & bitboard) != 0)
        {
            add_move(moves, bitboard, east(bitboard, 1), PieceType::KING,
                     color, board);

            add_move(moves, bitboard, northeast(bitboard, 1), PieceType::KING,
                     color, board);

            add_move(moves, bitboard, southeast(bitboard, 1), PieceType::KING,
                     color, board);
        }

        return moves;
    }
}

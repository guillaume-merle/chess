#include "bishop.hh"
#include "move.hh"

namespace board
{
    std::vector<Move>
    Bishop::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Chessboard board;
        return generate_moves(moves, bitboard, board);
    }

    std::vector<Move>
    Bishop::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                           Chessboard& board, Color color)
    {
        PieceType piece = PieceType::BISHOP;

        Bitboard pos = northeast(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = northeast(pos);
        }

        pos = northwest(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = northwest(pos);
        }

        pos = southeast(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = southeast(pos);
        }

        pos = southwest(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = southwest(pos);
        }

        return moves;
    }
}

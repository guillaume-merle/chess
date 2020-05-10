#pragma once

#include "move.hh"
#include "chessboard.hh"

namespace board
{
    class MoveGen
    {
    public:
        MoveGen(Chessboard& board);

        std::vector<Move> get_moves();

    private:
        std::vector<Move> moves_;

        void generate_moves(Chessboard& board);

        void generate_pawn_moves(Chessboard& board, Color color);

        void generate_knight_moves(Chessboard& board, Color color);

        void generate_king_moves(Chessboard& board, Color color);

        void generate_rook_moves(Chessboard& board, Color color);

        void generate_bishop_moves(Chessboard& board, Color color);

        void generate_queen_moves(Chessboard& board, Color color);

        void add_move(Chessboard& board, PieceType piece, Color color,
                      unsigned from, Bitboard moves);

        static const int MAX_MOVES_SIZE = 220;
    };
}

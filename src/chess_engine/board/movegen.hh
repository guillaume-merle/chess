#pragma once

#include "move.hh"
#include "chessboard.hh"

namespace board
{
    class MoveGen
    {
    public:
        explicit MoveGen(Chessboard& board);

        explicit MoveGen(Chessboard& board, Color color);

        std::vector<Move> get();

        // Maximum number of moves per round
        static const int MAX_MOVES_SIZE = 220;

    private:
        std::vector<Move> moves_;

        void generate_moves(Chessboard& board);
        void generate_moves_for_color(Chessboard& board, Color color);

        void generate_pawn_moves(Chessboard& board, Color color);

        void generate_knight_moves(Chessboard& board, Color color);

        void generate_king_moves(Chessboard& board, Color color);

        void generate_rook_moves(Chessboard& board, Color color);

        void generate_bishop_moves(Chessboard& board, Color color);

        void generate_queen_moves(Chessboard& board, Color color);

        void add_moves(Chessboard& board, PieceType piece, Color color,
                      Square from, Bitboard moves);
    };
}

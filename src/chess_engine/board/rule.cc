#include "rule.hh"
#include "pawn.hh"

namespace board
{
    std::vector<Move> generate_pawn_moves(Chessboard chessboard)
    {
        std::vector<Move> moves;

        for(unsigned i = 0; i < 64; i++)
        {
            Bitboard current;

            if (chessboard.is_white_turn())
            {
                current = (1ULL << i)
                    & chessboard.get_bitboard(BitboardPiece::WHITEPAWN);

                if (current)
                    moves = Pawn::generate_moves(moves, current, Color::WHITE);
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get_bitboard(BitboardPiece::BLACKPAWN);

                if (current)
                    moves = Pawn::generate_moves(moves, current, Color::BLACK);
            }
        }

        return moves;
    }
}

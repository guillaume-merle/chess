#include "rule.hh"
#include "pawn.hh"
#include "king.hh"

namespace board
{
    std::vector<Move> generate_pawn_moves(Chessboard& chessboard)
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

    std::vector<Move> generate_king_moves(Chessboard& chessboard)
    {
        std::vector<Move> moves;

        if (chessboard.is_white_turn())
        {
            King::generate_moves(
                moves, chessboard.get_bitboard(BitboardPiece::WHITEKING));
        }
        else
        {
            King::generate_moves(
                moves, chessboard.get_bitboard(BitboardPiece::BLACKKING));
        }

        return moves;
    }
}

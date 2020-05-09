#include "rule.hh"
#include "pawn.hh"
#include "king.hh"
#include "queen.hh"
#include "bishop.hh"
#include "knight.hh"
#include "rook.hh"

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
                    & chessboard.get(BitboardType::WHITEPAWN);

                if (current)
                    moves = Pawn::generate_moves(moves, current, Color::WHITE,
                                                 chessboard);
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKPAWN);

                if (current)
                    moves = Pawn::generate_moves(moves, current, Color::BLACK,
                                                 chessboard);
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
                moves, chessboard.get(BitboardType::WHITEKING), chessboard);
        }
        else
        {
            King::generate_moves(
                moves, chessboard.get(BitboardType::BLACKKING), chessboard,
                                      Color::BLACK);
        }

        return moves;
    }

    std::vector<Move> generate_knight_moves(Chessboard& chessboard)
    {
        std::vector<Move> moves;

        for(unsigned i = 0; i < 64; i++)
        {
            Bitboard current;

            if (chessboard.is_white_turn())
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::WHITEKNIGHT);
                moves = Knight::generate_moves(moves, current, chessboard);
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKKNIGHT);
                moves = Knight::generate_moves(moves, current, chessboard,
                                               Color::BLACK);
            }
        }

        return moves;
    }

    std::vector<Move> generate_bishop_moves(Chessboard& chessboard)
    {
        std::vector<Move> moves;

        for(unsigned i = 0; i < 64; i++)
        {
            Bitboard current;

            if (chessboard.is_white_turn())
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::WHITEBISHOP);
                moves = Bishop::generate_moves(moves, current, chessboard);
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKBISHOP);
                moves = Bishop::generate_moves(moves, current, chessboard,
                                               Color::BLACK);
            }
        }

        return moves;
    }

    std::vector<Move> generate_rook_moves(Chessboard& chessboard)
    {
        std::vector<Move> moves;

        for(unsigned i = 0; i < 64; i++)
        {
            Bitboard current;

            if (chessboard.is_white_turn())
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::WHITEROOK);
                moves = Rook::generate_moves(moves, current, chessboard);
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKROOK);
                moves = Rook::generate_moves(moves, current, chessboard,
                                               Color::BLACK);
            }
        }

        return moves;
    }

    std::vector<Move> generate_queen_moves(Chessboard& chessboard)
    {
        std::vector<Move> moves;

        if (chessboard.is_white_turn())
        {
            Queen::generate_moves(
                moves, chessboard.get(BitboardType::WHITEQUEEN), chessboard);
        }
        else
        {
            Queen::generate_moves(
                moves, chessboard.get(BitboardType::BLACKQUEEN), chessboard,
                                      Color::BLACK);
        }

        return moves;
    }
}

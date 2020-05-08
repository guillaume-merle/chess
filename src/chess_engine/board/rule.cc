#include "rule.hh"
#include "pawn.hh"
#include "king.hh"
#include "queen.hh"
#include "bishop.hh"

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
                    moves = Pawn::generate_moves(moves, current, Color::WHITE);
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKPAWN);

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
                moves, chessboard.get(BitboardType::WHITEKING));
        }
        else
        {
            King::generate_moves(
                moves, chessboard.get(BitboardType::BLACKKING));
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
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKBISHOP);
            }

            if (current)
                moves = Bishop::generate_moves(moves, current);
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
            }
            else
            {
                current = (1ULL << i)
                    & chessboard.get(BitboardType::BLACKROOK);
            }

            if (current)
                moves = Bishop::generate_moves(moves, current);
        }

        return moves;
    }

    std::vector<Move> generate_queen_moves(Chessboard& chessboard)
    {
        std::vector<Move> moves;

        if (chessboard.is_white_turn())
        {
            Queen::generate_moves(
                moves, chessboard.get(BitboardType::WHITEQUEEN));
        }
        else
        {
            Queen::generate_moves(
                moves, chessboard.get(BitboardType::BLACKQUEEN));
        }

        return moves;
    }
}

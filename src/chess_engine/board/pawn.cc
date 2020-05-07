#include "pawn.hh"

namespace board
{
    Bitboard Pawn::single_push(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return north(bitboard, 1);

        return south(bitboard, 1);
    }

    Bitboard Pawn::double_push(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return north(bitboard, 2);

        return south(bitboard, 2);
    }

    Bitboard Pawn::left_attack(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northwest(bitboard, 1);

        return southeast(bitboard, 1);
    }

    Bitboard Pawn::right_attack(Bitboard bitboard, Color color)
    {
        if (color == Color::WHITE)
            return northeast(bitboard, 1);

        return southwest(bitboard, 1);
    }

    std::vector<Move>
    Pawn::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                         Color color)
    {
        Chessboard board = Chessboard();
        return generate_moves(moves, bitboard, color, board);
    }

    std::vector<Move>
    Pawn::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                         Color color, Chessboard& board)
    {
        auto all_pieces = board.get(BitboardType::ALLWHITE)
                          | board.get(BitboardType::ALLBLACK);

        auto move = single_push(bitboard, color);

        if ((move & all_pieces) == 0)
            add_move(moves, bitboard, move, PieceType::PAWN);

        if ((color == Color::WHITE && bitboard <= white_pawn_start)
                || (color == Color::BLACK && bitboard >= black_pawn_start))
        {
            move = double_push(bitboard, color);
            if ((move & all_pieces) == 0)
                add_move(moves, bitboard, move, PieceType::PAWN);
        }

        // moves.emplace_back(Move(bitboard, Pawn::left_attack(bitboard, color),
                                // PieceType.PAWN));
        // moves.emplace_back(Move(bitboard, Pawn::right_attack(bitboard, color),
                                // PieceType.PAWN));

        return moves;
    }
}

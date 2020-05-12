#include "knight.hh"

namespace board
{
    Bitboard Knight::northwestwest(Bitboard bitboard)
    {
        return northwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::northeasteast(Bitboard bitboard)
    {
        return northeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::northnorthwest(Bitboard bitboard)
    {
        return northwest(north(bitboard, 1), 1);
    }

    Bitboard Knight::northnortheast(Bitboard bitboard)
    {
        return northeast(north(bitboard, 1), 1);
    }

    Bitboard Knight::southwestwest(Bitboard bitboard)
    {
        return southwest(west(bitboard, 1), 1);
    }

    Bitboard Knight::southeasteast(Bitboard bitboard)
    {
        return southeast(east(bitboard, 1), 1);
    }

    Bitboard Knight::southsouthwest(Bitboard bitboard)
    {
        return southwest(south(bitboard, 1), 1);
    }

    Bitboard Knight::southsoutheast(Bitboard bitboard)
    {
        return southeast(south(bitboard, 1), 1);
    }

    std::vector<Move>
    Knight::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Chessboard board = Chessboard();
        return generate_moves(moves, bitboard, board);
    }

    std::vector<Move>
    Knight::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
                           Chessboard& board, Color color)
    {
        add_move(moves, bitboard, northnorthwest(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, northnortheast(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, southsouthwest(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, southsoutheast(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, northwestwest(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, northeasteast(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, southwestwest(bitboard), PieceType::KNIGHT,
                 color, board);

        add_move(moves, bitboard, southeasteast(bitboard), PieceType::KNIGHT,
                 color, board);

        return moves;
    }
}

#include "move.hh"

namespace board
{
    Move::Move(Bitboard from, Bitboard to, PieceType piece)
        : from_(from), to_(to), piece_(piece)
    {}

    PieceType Move::piece_get()
    {
        return piece_;
    }

    Bitboard Move::get_from()
    {
        return from_;
    }

    Bitboard Move::get_to()
    {
        return to_;
    }

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece)
    {
        if (to == 0)
            return false;

        moves.emplace_back(Move(from, to, piece));
        return true;
    }

    bool add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece, Color color, Chessboard& board)
    {
        auto all_white_pieces = board.get(BitboardType::ALLWHITE);
        auto all_black_pieces = board.get(BitboardType::ALLBLACK);

        if ((color == Color::WHITE && (to & all_white_pieces) == 0)
            || (color == Color::BLACK && (to & all_black_pieces) == 0))
            return add_move(moves, from, to, piece);

        return false;
    }

    Bitboard combine_moves(std::vector<Move>& moves)
    {
        Bitboard all_moves = 0;
        for (auto& move : moves)
        {
            all_moves |= move.get_to();
        }

        return all_moves;
    }
}

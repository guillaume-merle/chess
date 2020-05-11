#include "move.hh"
#include <iostream>

namespace board
{
    Move::Move(Bitboard from, Bitboard to, PieceType piece, int flags)
        : from_(from), to_(to), piece_(piece), promotion_(ALL)
        , capture_(ALL), is_capture_(false)
    {
        parse_flags(flags);
    }

    Move::Move(Bitboard from, Bitboard to, PieceType piece, PieceType capture,
               int flags)
        : from_(from), to_(to), piece_(piece), promotion_(ALL)
        , capture_(capture), is_capture_(true)
    {
        parse_flags(flags);
    }

    void Move::parse_flags(int flags)
    {
        double_pawn_push_ = MoveFlag::DOUBLE_PAWN_PUSH & flags;
        en_passant_ = MoveFlag::EN_PASSANT & flags;
        king_castling_ = MoveFlag::KING_CASTLING & flags;
        queen_castling_ = MoveFlag::QUEEN_CASTLING & flags;
    }

    PieceType Move::get_piece()
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

    PieceType Move::get_capture()
    {
        return capture_;
    }

    bool Move::is_capture()
    {
        return is_capture_;
    }

    bool Move::is_double_pawn_push()
    {
        return double_pawn_push_;
    }

    bool Move::is_en_passant()
    {
        return en_passant_;
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
        // if there is an opponant piece to capture on the square
        if (board.would_capture(to, color))
        {
            PieceType start = PieceType::QUEEN;

            for (int i = start; i < BITBOARDS_NUMBER; i++)
            {
                if (to & board.get(opposite_color(color), i))
                {
                    PieceType capture = static_cast<PieceType>(i);
                    moves.emplace_back(Move(from, to, piece, capture));

                    // return false to stop sliding pieces movements
                    return false;
                }
            }

            throw std::runtime_error("add_move: invalid bitboards");
        }
        // else if there is an ally piece on the square
        else if (board.would_collide(to, color))
            return false;

        // the square is free
        return add_move(moves, from, to, piece);
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

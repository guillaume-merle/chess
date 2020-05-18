#include <iostream>

#include "move.hh"

namespace board
{
    Move::Move()
        : none_(true)
    {}

    Move::Move(Bitboard from, Bitboard to, PieceType piece, int flags)
        : from_(from), to_(to), piece_(piece), promotion_(ALL)
        , capture_(ALL), is_capture_(false)
    {
        parse_flags(flags);
    }

    Move::Move(Bitboard from, Bitboard to, PieceType piece, PieceType capture,
               int flags)
        : from_(from), to_(to), piece_(piece), promotion_(ALL)
        , capture_(ALL)
    {
        parse_flags(flags);
        if (is_capture_ || en_passant_)
            capture_ = capture;
        else
            promotion_ = capture;
    }

    Move::Move(Bitboard from, Bitboard to, PieceType piece, PieceType promotion,
               PieceType capture, int flags)
        : from_(from), to_(to), piece_(piece), promotion_(promotion)
        , capture_(capture)
    {
        parse_flags(flags);
    }

    bool Move::is_none()
    {
        return none_;
    }

    void Move::set_grade(int grade)
    {
        grade_ = grade;
    }

    int Move::get_grade()
    {
        return grade_;
    }

    std::string Move::to_string()
    {
        std::string move_str;

        // from: file
        move_str += 'a' + from_ % 8;

        // from: rank
        move_str += '1' + from_ / 8;

        // to : file
        move_str += 'a' + to_ % 8;

        // to : rank
        move_str += '1' + to_ / 8;

        // case promotion
        if (is_promotion_)
        {
            switch(promotion_)
            {
                case QUEEN:
                    move_str += 'q';
                    break;
                case KNIGHT:
                    move_str += 'n';
                    break;
                case BISHOP:
                    move_str += 'b';
                    break;
                case ROOK:
                    move_str = 'r';
                    break;
                default:
                    break;
            }
        }

        return move_str;
    }

    bool Move::operator==(const Move& rhs) const
    {
        return this->from_ == rhs.from_
            && this->to_ == rhs.to_
            && this->piece_ == rhs.piece_
            && this->promotion_ == rhs.promotion_
            && this->capture_ == rhs.capture_
            && this->is_capture_ == rhs.is_capture_
            && this->double_pawn_push_ == rhs.double_pawn_push_
            && this->king_castling_ == rhs.king_castling_
            && this->queen_castling_ == rhs.queen_castling_
            && this->en_passant_ == rhs.en_passant_;
    }

    void Move::parse_flags(int flags)
    {
        double_pawn_push_ = MoveFlag::DOUBLE_PAWN_PUSH & flags;
        en_passant_ = MoveFlag::EN_PASSANT & flags;
        king_castling_ = MoveFlag::KING_CASTLING & flags;
        queen_castling_ = MoveFlag::QUEEN_CASTLING & flags;
        is_promotion_ = MoveFlag::PROMOTION & flags;
        is_capture_ = MoveFlag::CAPTURE & flags;
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

    PieceType Move::get_promotion()
    {
        return promotion_;
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

    bool Move::is_promotion()
    {
        return is_promotion_;
    }

    bool Move::is_king_side_castling()
    {
        return king_castling_;
    }

    bool Move::is_queen_side_castling()
    {
        return queen_castling_;
    }

    Bitboard combine_moves(std::vector<Move>& moves)
    {
        Bitboard all_moves = 0;
        for (auto& move : moves)
        {
            all_moves |= 1ULL << move.get_to();
        }

        return all_moves;
    }
}

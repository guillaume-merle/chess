#include "pgn-move.hh"

namespace board
{
    PgnMove::PgnMove(const Position& start, const Position& end,
                     PieceType piece, bool capture, ReportType report,
                     const PgnMove::opt_piece_t& promotion)
        : start_(start)
        , end_(end)
        , piece_(piece)
        , promotion_(promotion)
        , capture_(capture)
        , report_(report)
    {}

    PgnMove PgnMove::generate_castling(bool queen_side, Color color)
    {
        static const Position wking_pos{File::E, Rank::ONE};
        static const Position bking_pos{File::E, Rank::EIGHT};
        static const PgnMove w_small{wking_pos,
                                     {File::G, Rank::ONE},
                                     PieceType::KING,
                                     false,
                                     ReportType::NONE};
        static const PgnMove w_big{wking_pos,
                                   {File::C, Rank::ONE},
                                   PieceType::KING,
                                   false,
                                   ReportType::NONE};
        static const PgnMove b_small{bking_pos,
                                     {File::G, Rank::EIGHT},
                                     PieceType::KING,
                                     false,
                                     ReportType::NONE};
        static const PgnMove b_big{bking_pos,
                                   {File::C, Rank::EIGHT},
                                   PieceType::KING,
                                   false,
                                   ReportType::NONE};

        if (color == Color::WHITE)
            return queen_side ? w_big : w_small;

        return queen_side ? b_big : b_small;
    }

    void PgnMove::report_set(ReportType report)
    {
        report_ = report;
    }

    bool PgnMove::is_queen_side_castling(Color color)
    {
        if (piece_ != KING)
            return false;

        Square from;

        if (color == WHITE)
            from = 4;
        else
            from = 60;


        return start_.to_square() == from && end_.to_square() == from - 2;
    }

    bool PgnMove::is_king_side_castling(Color color)
    {
        if (piece_ != KING)
            return false;

        Square from;

        if (color == WHITE)
            from = 4;
        else
            from = 60;

        return start_.to_square() == from && end_.to_square() == from + 2;
    }

    bool PgnMove::is_double_pawn_push(Color color)
    {
        if (piece_ != PAWN)
            return false;

        return start_.to_square()
                    == end_.to_square() + (color == WHITE ? -16 : +16);
    }

    Move PgnMove::to_move(Chessboard& board)
    {
        Square from = start_.to_square();
        Square to = end_.to_square();
        Color them = opposite_color(board.current_color());

        Move move;

        if (piece_ == PAWN && board.would_capture_en_passant(1ULL << to))
        {
            move = Move(from, to, PAWN, PAWN, MoveFlag::EN_PASSANT);
        }
        else if (promotion_.has_value() && capture_)
        {
            move = Move(from, to, piece_, promotion_.value(),
                        board.get_piece_type(to, them),
                        MoveFlag::CAPTURE | MoveFlag::PROMOTION);
        }
        else if (capture_)
        {
            move = Move(from, to, piece_, board.get_piece_type(to, them),
                        MoveFlag::CAPTURE);
        }
        else if (is_queen_side_castling(board.current_color()))
        {
            move = Move(from, to, piece_, MoveFlag::QUEEN_CASTLING);
        }
        else if (is_king_side_castling(board.current_color()))
        {
            move = Move(from, to, piece_, MoveFlag::KING_CASTLING);
        }
        else if (is_double_pawn_push(board.current_color()))
        {
            move = Move(from, to, piece_, MoveFlag::DOUBLE_PAWN_PUSH);
        }
        else
        {
            move = Move(from, to, piece_);
        }

        return move;
    }

} // namespace board

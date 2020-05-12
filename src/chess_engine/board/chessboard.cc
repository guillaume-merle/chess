#include <iostream>

#include "chessboard.hh"
#include "rule.hh"
#include "utils.hh"
#include "move.hh"
#include "attacks.hh"
#include "movegen.hh"

namespace board
{
    Chessboard::Chessboard()
        : bitboards_{{0}}, white_turn_(true)
    {}

    Chessboard::Chessboard(const Chessboard& board)
        : bitboards_{{0}}, white_turn_(board.white_turn_)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < BITBOARDS_NUMBER; j++)
            {
                bitboards_[i][j] = board.bitboards_[i][j];
            }
        }
    }

    Chessboard& Chessboard::operator=(const Chessboard& board)
    {
        white_turn_ = board.white_turn_;

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < BITBOARDS_NUMBER; j++)
            {
                bitboards_[i][j] = board.bitboards_[i][j];
            }
        }

        return *this;
    }

    Bitboard Chessboard::get(Color color, PieceType piece) const
    {
        return bitboards_[color][piece];
    }

    Bitboard Chessboard::get(Color color, int piece) const
    {
        return bitboards_[color][piece];
    }

    Bitboard Chessboard::get_all()
    {
        return bitboards_[WHITE][ALL] | bitboards_[BLACK][ALL];
    }

    void Chessboard::update_all_boards()
    {
        Bitboard all_white = 0;
        Bitboard all_black = 0;

        for (int i = 1; i < BITBOARDS_NUMBER; i++)
        {
            all_white |= get(WHITE, i);
            all_black |= get(BLACK, i);
        }

        set(WHITE, ALL, all_white);
        set(BLACK, ALL, all_black);
    }

    PieceType Chessboard::get_piece_type(Square square, Color color)
    {
        Bitboard piece = 1ULL << square;

        for (int i = 1; i < BITBOARDS_NUMBER; i++)
        {
            if (piece & get(color, i))
                return static_cast<PieceType>(i);
        }

        throw std::runtime_error("get_piece_type: the given square doesn't"
                                 "match a piece.");
    }

    bool Chessboard::is_white_turn()
    {
        return white_turn_;
    }

    Color Chessboard::current_color()
    {
        return white_turn_ ? WHITE : BLACK;
    }

    bool Chessboard::set(Color color, PieceType piece, Bitboard value)
    {
        if (piece < 0 || piece >= BITBOARDS_NUMBER)
            return false;

        bitboards_[color][piece] = value;
        return true;
    }

    bool Chessboard::would_collide(Bitboard pos, Color color)
    {
        return (pos & get(color, ALL));
    }

    bool Chessboard::would_capture(Bitboard pos, Color color)
    {
        return (pos & get(opposite_color(color), ALL));
    }

    bool Chessboard::would_capture_en_passant(Bitboard pos)
    {
        return (pos & (1ULL << en_passant_));
    }

    bool Chessboard::square_attacks(Color color, Square square)
    {
        Bitboard all_pieces = get_all();
        Color them = opposite_color(color);

        Bitboard attackers = 0;

        attackers |= attacks::get_king_attacks(square)
                     & get(them, KING);
        attackers |= attacks::get_knight_attacks(square)
                     & get(them, KNIGHT);
        attackers |= attacks::get_pawn_attacks(square, color)
                     & get(them, PAWN);
        attackers |= attacks::get_bishop_attacks(square, all_pieces)
                     & get(them, BISHOP);
        attackers |= attacks::get_rook_attacks(square, all_pieces)
                     & get(them, ROOK);
        attackers |= attacks::get_queen_attacks(square, all_pieces)
                     & get(them, QUEEN);

        return attackers;
    }

    bool Chessboard::is_check(Color color)
    {
        Square king_square = bitscan(get(color, KING));
        if (king_square > 63)
            return false;

        Bitboard attackers = square_attacks(color, king_square);

        // remove opposite king attacks as they are not permitted
        attackers &= ~get(opposite_color(color), KING);

        if (attackers)
            return true;

        return false;
    }

    bool Chessboard::illegal_king_check(Color color)
    {
        Square king_square = bitscan(get(color, KING));

        if (king_square > 63)
            return false;

        Color them = opposite_color(color);

        if (attacks::get_king_attacks(king_square) & get(them, KING))
            return true;

        return false;
    }

    bool Chessboard::is_checkmate(Color color)
    {
        return is_check(color) && generate_legal_moves(color).empty();
    }

    bool Chessboard::is_draw(Color color)
    {
        Bitboard all_knight = get(WHITE, KNIGHT) | get(BLACK, BLACK);
        Bitboard all_bishop = get(WHITE, BISHOP) | get(BLACK, BISHOP);
        //check if there is only two bare king
        if (popcount(get(WHITE, ALL) | get(BLACK, ALL)) == 2 && get(WHITE, KING)
                                                            && get(BLACK, KING))
        {
            return true;
        }

        //check if there is only bare king and a knight (whatever his color).
        if (popcount(get(WHITE, ALL) | get(BLACK, ALL)) == 3
                                     && get(WHITE, KING)
                                     && get(BLACK, KING)
                                     && all_knight)
        {
            return true;
        }

        //check if there is only bare king and a bishop (whatever his color).
        if (popcount(get(WHITE, ALL) | get(BLACK, ALL)) == 3
                                     && get(WHITE, KING)
                                     && get(BLACK, KING)
                                     && all_bishop)
        {
            return true;
        }

        //check if the game lasts more than 50 turns
        if (last_fifty_turn_ > 50)
            return true;

        //first verify that my king is not in check
        if (is_check(color))
            return false;

        std::vector<Move> legal_moves = generate_legal_moves(color);
        //verify if legal_moves are available.
        if (!legal_moves.empty())
            return false;

        return true;
    }

    void Chessboard::do_move(Move& move)
    {
        do_move(move, current_color());
    }

    void Chessboard::do_move(Move& move, Color color)
    {
        PieceType piece = move.get_piece();

        // reset en_passant_
        en_passant_ = 0;

        if (move.is_capture())
        {
            remove_piece(opposite_color(color), move.get_capture(),
                         move.get_to());
        }
        else if (move.is_double_pawn_push())
        {
            en_passant_ = move.get_from() + (color == WHITE ? 8 : -8);
        }
        else if (move.is_en_passant())
        {
            if (color == WHITE)
                remove_piece(BLACK, move.get_capture(), move.get_to() - 8);
            else
                remove_piece(WHITE, move.get_capture(), move.get_to() + 8);
        }
        else if (move.is_king_side_castling())
        {
            Square rook_from = color == WHITE ? 7 : 63;
            move_piece(color, ROOK, rook_from, rook_from - 2);
        }
        else if (move.is_queen_side_castling())
        {
            Square rook_from = color == WHITE ? 0 : 56;
            move_piece(color, ROOK, rook_from, rook_from + 3);
        }

        // check if move is capture or a pawn is moving
        if (move.is_capture() || move.get_piece() == PAWN)
            last_fifty_turn_ = 0;
        else
            last_fifty_turn_++;

        move_piece(color, piece, move.get_from(), move.get_to());

        if (move.is_promotion())
        {
            remove_piece(color, PieceType::PAWN, move.get_to());
            add_piece(color, PieceType::QUEEN, move.get_to());
        }

        // set next turn
        white_turn_ = !white_turn_;
    }

    void Chessboard::add_piece(Color color, PieceType piece, Square pos)
    {
        Bitboard mask = 1ULL << pos;

        bitboards_[color][piece] |= mask;
    }

    void Chessboard::update_castling_abilities(Color color, PieceType piece,
                                               Square from)
    {
        if (piece == KING)
        {
            if (color == WHITE)
            {
                white_king_side_castling_ = false;
                white_queen_side_castling_ = false;
            }
            else
            {
                black_king_side_castling_ = false;
                black_queen_side_castling_ = false;
            }
        }
        else if (piece == ROOK)
        {
            if (from == 0)
                white_queen_side_castling_ = false;
            if (from == 7)
                white_king_side_castling_ = false;
            if (from == 56)
                black_queen_side_castling_ = false;
            if (from == 63)
                black_king_side_castling_ = false;
        }
    }

    void Chessboard::move_piece(Color color, PieceType piece, Square from,
                                Square to)
    {
        Bitboard from_to = 1ULL << from | 1ULL << to;

        // xor "from" and "to" bits to update position
        bitboards_[color][piece] ^= from_to;
        // update all white pieces bitboard as well
        bitboards_[color][ALL] ^= from_to;

        update_castling_abilities(color, piece, from);

    }

    void Chessboard::remove_piece(Color color, PieceType piece, Square pos)
    {
        Bitboard mask = 1ULL << pos;

        // xor the square bit of the piece to remove it from the board
        bitboards_[color][piece] ^= mask;
        bitboards_[color][piece] ^= mask;
    }

    std::vector<Move> Chessboard::generate_legal_moves()
    {
        return generate_legal_moves(current_color());
    }

    std::vector<Move> Chessboard::generate_legal_moves(Color color)
    {
        std::vector<Move> moves = MoveGen(*this, color).get();

        std::vector<Move> legal_moves;
        legal_moves.reserve(MoveGen::MAX_MOVES_SIZE);

        for (auto& move : moves)
        {
            Chessboard temp_board = *this;
            temp_board.do_move(move, color);

            //check if the piece is in check and if it's not a bad check (king)
            if (!temp_board.is_check(color))
            {
                if (move.get_piece() == KING
                    && temp_board.illegal_king_check(color))
                    continue;

                legal_moves.emplace_back(move);
            }
        }

        return legal_moves;
    }

    bool Chessboard::is_move_legal(const Move& move)
    {
        std::vector<Move> moves = generate_legal_moves();

        for (const Move& generate_move : moves)
        {
            if (generate_move == move)
                return true;
        }

        return false;
    }

    bool Chessboard::can_king_side_castling(Color color)
    {
        if (is_check(color))
            return false;

        Bitboard movement_squares = 0;
        Bitboard attacked = 0;

        if (color == WHITE)
        {
            if (!white_king_side_castling_)
                return false;

            Bitboard rook = 1 << 7;
            Bitboard king = 1 << 4;

            if (!(get(WHITE, ROOK) & rook) && !(get(WHITE, KING) & king))
            {
                white_king_side_castling_ = false;
                return false;
            }

            movement_squares= 1 << 5 | 1 << 6;
            attacked = square_attacks(color, 5) | square_attacks(color, 6);
        }
        else
        {
            if (!black_king_side_castling_)
                return false;

            Bitboard rook = 1ULL << 63;
            Bitboard king = 1ULL << 60;

            // check that the king and the rook are at the start pos
            if (!(get(BLACK, ROOK) & rook) && !(get(BLACK, KING) & king))
            {
                black_king_side_castling_ = false;
                return false;
            }

            movement_squares= 1ULL << 61 | 1ULL << 62;
            attacked = square_attacks(color, 61) | square_attacks(color, 62);
        }

        Bitboard occupied = movement_squares & get_all();

        return !occupied && !attacked;
    }

    bool Chessboard::can_queen_side_castling(Color color)
    {
        if (is_check(color))
            return false;

        Bitboard movement_squares = 0;
        Bitboard attacked = 0;

        if (color == WHITE)
        {
            if (!white_queen_side_castling_)
                return false;

            Bitboard rook = 1;
            Bitboard king = 1 << 4;

            // check that the king and the rook are at the start pos
            if (!(get(WHITE, ROOK) & rook) && !(get(WHITE, KING) & king))
            {
                white_queen_side_castling_ = false;
                return false;
            }

            movement_squares = 1 << 3 | 1 << 2 | 1 << 1;
            attacked = square_attacks(color, 2) | square_attacks(color, 3);
        }
        else
        {
            if (!black_queen_side_castling_)
                return false;

            Bitboard rook = 1UL << 56;
            Bitboard king = 1ULL << 60;

            if (!(get(BLACK, ROOK) & rook) && !(get(BLACK, KING) & king))
            {
                black_queen_side_castling_ = false;
                return false;
            }

            movement_squares = 1ULL << 59 | 1ULL << 58 | 1ULL << 57;
            attacked = square_attacks(color, 2) | square_attacks(color, 3);
        }

        Bitboard occupied = movement_squares & get_all();

        return !occupied && !attacked;
    }

    Chessboard::opt_piece_t
    Chessboard::operator[](const Position& pos) const
    {
        Square square = pos.file_get() + pos.rank_get() * 8;
        Bitboard piece_board = 1ULL << square;

        Color color = WHITE;

        if (piece_board & get(BLACK, ALL))
            color = BLACK;
        else if (!(piece_board & get(WHITE, ALL)))
            return std::nullopt;

        for (int i = 1; i < BITBOARDS_NUMBER; i++)
        {
            if (piece_board & get(color, i))
                return std::make_pair(static_cast<PieceType>(i), color);
        }

        return std::nullopt;
    }
}

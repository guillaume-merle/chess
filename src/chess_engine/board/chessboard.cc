#include <iostream>

#include "chessboard.hh"
#include "utils.hh"
#include "move.hh"
#include "attacks.hh"
#include "movegen.hh"
#include "perft-parser.hh"

namespace board
{
    Chessboard::Chessboard()
        : bitboards_{{0}}, white_turn_(true)
        , white_king_side_castling_(true)
        , white_queen_side_castling_(true)
        , black_king_side_castling_(true)
        , black_queen_side_castling_(true)
        , en_passant_(-1)
        , turn_(0)
        , last_fifty_turns_(0)
    {}

    Chessboard::Chessboard(std::string fen)
        : bitboards_{{0}}, white_turn_(true)
        , white_king_side_castling_(true)
        , white_queen_side_castling_(true)
        , black_king_side_castling_(true)
        , black_queen_side_castling_(true)
        , en_passant_(-1)
        , turn_(0)
        , last_fifty_turns_(0)
    {
        set_from_fen(perft_parser::parse_fen(fen));
    }

    Chessboard::Chessboard(const Chessboard& board)
        : bitboards_{{0}}, white_turn_(board.white_turn_)
        , white_king_side_castling_(board.white_king_side_castling_)
        , white_queen_side_castling_(board.white_queen_side_castling_)
        , black_king_side_castling_(board.black_king_side_castling_)
        , black_queen_side_castling_(board.black_queen_side_castling_)
        , en_passant_(board.en_passant_)
        , turn_(board.turn_)
        , last_fifty_turns_(board.last_fifty_turns_)
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
        white_queen_side_castling_ = board.white_queen_side_castling_;
        white_king_side_castling_ = board.white_king_side_castling_;
        black_queen_side_castling_ = board.black_queen_side_castling_;
        black_king_side_castling_ = board.black_king_side_castling_;
        en_passant_ = board.en_passant_;
        turn_ = board.turn_;
        last_fifty_turns_ = board.last_fifty_turns_;

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

        for (int i = QUEEN; i < BITBOARDS_NUMBER - 1; i++)
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

        for (int i = QUEEN; i < BITBOARDS_NUMBER - 1; i++)
        {
            if (piece & get(color, i))
                return PieceType(i);
        }

        throw std::runtime_error("get_piece_type: the given square doesn't "
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

    void Chessboard::set_from_fen(FenObject fen)
    {
        clear();
        for (size_t i = 0; i < fen.size(); i++)
        {
            for (size_t j = 0; j < fen[i].size(); j ++)
            {
                FenRank::side_piece_t piece = fen[i][j];
                if (piece.first != ALL)
                    bitboards_[piece.second][piece.first]
                        |= 1ULL << ((7 - i) * 8 + j);
            }
        }

        update_all_boards();

        white_turn_ = fen.side_to_move_get() == WHITE;
        Position en_passant_pos = fen.en_passant_target_get();
        en_passant_ = en_passant_pos.rank_get() * 8 + en_passant_pos.file_get();

        white_king_side_castling_ = false;
        white_queen_side_castling_ = false;
        black_king_side_castling_ = false;
        black_queen_side_castling_ = false;

        for (auto castling : fen.castling_get())
        {
            if (castling == 'K')
                white_king_side_castling_ = true;
            else if (castling == 'Q')
                white_queen_side_castling_ = true;
            else if (castling == 'k')
                black_king_side_castling_ = true;
            else if (castling == 'q')
                black_queen_side_castling_ = true;
        }
    }

    void Chessboard::clear()
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < BITBOARDS_NUMBER; j++)
            {
                bitboards_[i][j] = 0;
            }
        }
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
        return en_passant_ != -1 && (pos & (1ULL << en_passant_));
    }

    Bitboard Chessboard::square_attacks(Color color, Square square)
    {
        Bitboard all_pieces = get_all();
        Color them = opposite_color(color);

        Bitboard attackers = 0;

        attackers |= attacks_g.get_king_attacks(square)
                     & get(them, KING);
        attackers |= attacks_g.get_knight_attacks(square)
                     & get(them, KNIGHT);
        attackers |= attacks_g.get_pawn_attacks(square, color)
                     & get(them, PAWN);
        attackers |= attacks_g.get_bishop_attacks(square, all_pieces)
                     & get(them, BISHOP);
        attackers |= attacks_g.get_rook_attacks(square, all_pieces)
                     & get(them, ROOK);
        attackers |= attacks_g.get_queen_attacks(square, all_pieces)
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

        if (attacks_g.get_king_attacks(king_square) & get(them, KING))
            return true;

        return false;
    }

    bool Chessboard::is_checkmate(Color color)
    {
        return is_check(color) && generate_legal_moves(color).empty();
    }

    bool Chessboard::is_stalemate(Color color)
    {
        return !is_check(color) && generate_legal_moves(color).empty();
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
        if (last_fifty_turns_ > 50)
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
        en_passant_ = -1;

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
            last_fifty_turns_ = 0;
        else
            last_fifty_turns_++;

        move_piece(color, piece, move.get_from(), move.get_to());

        if (move.is_promotion())
        {
            remove_piece(color, PieceType::PAWN, move.get_to());
            add_piece(color, move.get_promotion(), move.get_to());
        }

        // set next turn
        white_turn_ = !white_turn_;
        turn_ += 1;
    }

    void Chessboard::add_piece(Color color, PieceType piece, Square pos)
    {
        Bitboard mask = 1ULL << pos;

        bitboards_[color][piece] |= mask;
        bitboards_[color][ALL] |= mask;
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
        // update the all bitboard as well
        bitboards_[color][ALL] ^= from_to;

        update_castling_abilities(color, piece, from);

    }

    void Chessboard::remove_piece(Color color, PieceType piece, Square pos)
    {
        Bitboard mask = 1ULL << pos;

        // xor the square bit of the piece to remove it from the board
        bitboards_[color][piece] ^= mask;
        bitboards_[color][ALL] ^= mask;
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

            if (!(get(WHITE, ROOK) & rook) || !(get(WHITE, KING) & king))
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
            if (!(get(BLACK, ROOK) & rook) || !(get(BLACK, KING) & king))
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
            if (!(get(WHITE, ROOK) & rook) || !(get(WHITE, KING) & king))
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

            if (!(get(BLACK, ROOK) & rook) || !(get(BLACK, KING) & king))
            {
                black_queen_side_castling_ = false;
                return false;
            }

            movement_squares = 1ULL << 59 | 1ULL << 58 | 1ULL << 57;
            attacked = square_attacks(color, 59) | square_attacks(color, 58);
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

        for (int i = QUEEN; i < BITBOARDS_NUMBER - 1; i++)
        {
            if (piece_board & get(color, i))
                return std::make_pair(PieceType(i), color);
        }

        return std::nullopt;
    }

    void Chessboard::set_turn(Color color)
    {
        white_turn_ = color == WHITE;
    }
}

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

    bool Chessboard::is_check(Color color)
    {
        Square king_square = bitscan(get(color, KING));
        if (king_square > 63)
            return false;

        Bitboard all_pieces = get(WHITE, ALL) | get(BLACK, ALL);
        Color them = opposite_color(color);

        Bitboard attackers = 0;
        attackers |= attacks::get_knight_attacks(king_square)
                     & get(them, KNIGHT);
        attackers |= attacks::get_pawn_attacks(king_square, color)
                     & get(them, PAWN);
        attackers |= attacks::get_bishop_attacks(king_square, all_pieces)
                     & get(them, BISHOP);
        attackers |= attacks::get_rook_attacks(king_square, all_pieces)
                     & get(them, ROOK);
        attackers |= attacks::get_queen_attacks(king_square, all_pieces)
                     & get(them, QUEEN);

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

        std::cout << "ILLEGAL KING CHECK:\n";
        print_bitboard(attacks::get_king_attacks(king_square));

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

        // check if move is capture or a pawn is moving
        if (move.is_capture() || move.get_piece() == PAWN)
            last_fifty_turn_ = 0;
        else
            last_fifty_turn_++;

        move_piece(color, piece, move.get_from(), move.get_to());

        // set next turn
        white_turn_ = !white_turn_;
    }

    void Chessboard::move_piece(Color color, PieceType piece, Square from,
                                Square to)
    {
        Bitboard from_to = 1ULL << from | 1ULL << to;

        // xor "from" and "to" bits to update position
        bitboards_[color][piece] ^= from_to;
        // update all white pieces bitboard as well
        bitboards_[color][ALL] ^= from_to;
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

            std::cout << "Move: " << move.get_from() << " to " << move.get_to() << "\n";

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

#pragma once

#include <vector>

#include "chessboard-interface.hh"
#include "bitboard.hh"

namespace board
{
    constexpr int BITBOARDS_NUMBER = 7;

    class Move;

    /*
    ** \brief class of the chessboard.
    */
    class Chessboard : public ChessboardInterface
    {
    public:
        Chessboard();

        Chessboard(const Chessboard&);

        Chessboard& operator=(const Chessboard&);

        std::vector<Move> generate_legal_moves();

        std::vector<Move> generate_legal_moves(Color color);

        void do_move(Move& move);

        void do_move(Move& move, Color color);

        bool is_move_legal(const Move& move);

        bool is_check(Color color);

        bool square_attacks(Color color, Square square);

        bool illegal_king_check(Color color);

        bool is_checkmate(Color color);

        bool is_draw(Color color);

        Bitboard get(Color color, PieceType piece) const;

        Bitboard get(Color color, int piece) const;

        Bitboard get_all();

        void update_all_boards();

        PieceType get_piece_type(Square square, Color color);

        bool set(Color color, PieceType piece, Bitboard value);

        bool is_white_turn();

        Color current_color();

        bool would_collide(Bitboard pos, Color color);

        bool would_capture(Bitboard pos, Color color);

        // check for en_passant capture
        bool would_capture_en_passant(Bitboard pos);

        bool can_queen_side_caslting(Color color);

        bool can_king_side_castling(Color color);

        opt_piece_t operator[](const Position& position) const override;

    private:
        Bitboard bitboards_[2][BITBOARDS_NUMBER];

        bool white_turn_;

        bool white_king_side_castling_;
        bool white_queen_side_castling_;
        bool black_king_side_castling_;
        bool black_queen_side_castling_;

        Square en_passant_;
        unsigned int turn_;
        int last_fifty_turn_ = 0;

        void move_piece(Color color, PieceType piece, Square from, Square to);

        void remove_piece(Color color, PieceType piece, Square pos);

        void add_piece(Color color, PieceType piece, Square pos);
    };

} // namespace board

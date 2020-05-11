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

        void do_move(Move move);

        bool is_move_legal(Move move);

        bool is_check(Color color);

        bool is_checkmate(Color color);

        bool is_draw();

        Bitboard get(Color color, PieceType piece);

        Bitboard get(Color color, int piece);

        void update_all_boards();

        PieceType get_piece_type(Square square, Color color);

        bool set(Color color, PieceType piece, Bitboard value);

        bool is_white_turn();

        virtual opt_piece_t operator[](const Position& position) const;

        bool would_collide(Bitboard pos, Color color);

        bool would_capture(Bitboard pos, Color color);

    private:
        Bitboard bitboards_[2][BITBOARDS_NUMBER];

        bool white_turn_;
        bool white_king_castling_;
        bool white_queen_castling_;
        bool black_king_castling_;
        bool black_queen_castling_;
        //en_passant_; TODO
        unsigned int turn_;
        //last_fifty_turn_; TODO
    };

} // namespace board

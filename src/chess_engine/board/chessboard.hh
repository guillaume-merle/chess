#pragma once

#include <vector>
#include <map>

#include "chessboard-interface.hh"
#include "bitboard.hh"
#include "move.hh"
#include "fen-object.hh"
#include "zobrist.hh"

namespace board
{
    constexpr int BITBOARDS_NUMBER = 7;
    const std::string START_POS =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    /**
     * @brief Class representing a chessboard.
     *
     * 14 bitboard are used to represent a chess board:
     * 12 for each piece of each color and 2 representing all pieces of
     * each color.
     *
     */
    class Chessboard : public ChessboardInterface
    {
    public:
        /**
         * @brief Construct a new blank chessboard.
         */
        explicit Chessboard();

        /**
         * @brief Construct a new chessboard and set it the the given position.
         */
        explicit Chessboard(std::string fen);

        /**
         * @brief Construct a new chessboard from an existing board.
         *
         * @param board the Chessboard to copy.
         */
        Chessboard(const Chessboard& board);

        /**
         * @brief Copy assignment operator.
         *
         * @param board the Chessboard to copy.
         */
        Chessboard& operator=(const Chessboard& board);

        /**
         * @brief Set all the bitboard with the field of the fen object
         *
         * @param the FenObject with all the information about the game
         */
        void set_from_fen(FenObject fen);

         /**
         * @brief clear all the bitboards
         */
        void clear();

        /**
         * @brief Generate all legal moves for the current color and board.
         *
         * @return a vector of moves.
         */
        std::vector<Move> generate_legal_moves();

        /**
         * @brief Generate all legal moves for the given color and
         * the current board.
         *
         * @param color the color to generate moves for.
         * @return a vector of moves.
         */
        std::vector<Move> generate_legal_moves(Color color);

        /**
         * @brief Generate all legal captures for the current color and board.
         *
         * @return a vector of moves.
         */
        std::vector<Move> generate_legal_captures();

        /**
         * @brief apply a move to the board for the current color.
         *
         * @param move the move to apply.
         */
        void do_move(Move& move);

        /**
         * @brief apply a move to the board for the given color.
         *
         * @param move the move to apply.
         * @color the color to play the move for.
         */
        void do_move(Move& move, Color color);

        /**
         * @brief verify if a move is legal.
         *
         * @param move the move to verify.
         * @return true if the move is legal.
         */
        bool is_move_legal(const Move& move);

        /**
         * @brief verify if a color is in check.
         *
         * @param color the side to verify for check.
         * @return true if the side is in check.
         */
        bool is_check(Color color);

        /**
         * @brief get the attackers bitboard for a certain square.
         *
         * @param color the color of the attacked square.
         * @param square to check for.
         */
        Bitboard square_attacks(Color color, Square square);

        /**
         * @brief verify if there is a check by the other king.
         *
         * @param color the color of the attacking king.
         * @return true if there is an illegal king check.
         */
        bool illegal_king_check(Color color);

        /**
         * @brief verify is the color is in checkmate.
         *
         * @param color the color the verify the checkmate for.
         * @return true if the color is in checkmate.
         */
        bool is_checkmate(Color color);

        /**
         * @brief verify is the color is in stalemate.
         *
         * @param color the color the verify the checkmate for.
         * @return true if the color is in checkmate.
         */
        bool is_stalemate(Color color);

        /**
         * @brief verify if there is a draw.
         *
         * @return true if there is a draw.
         */
        bool is_draw();

        /**
         * @brief get a specifig bitboard.
         *
         * @param color the color of the bitboard.
         * @param piece the piece type of the bitboard.
         * @return the corresponding bitboard.
         */
        Bitboard get(Color color, PieceType piece) const;

        /**
         * @brief get a specifig bitboard.
         *
         * @param color the color of the bitboard.
         * @param piece the piece type of the bitboard.
         * @return the corresponding bitboard.
         */
        Bitboard get(Color color, int piece) const;

        /**
         * @brief get a bitboard of all pieces.
         *
         * @return a bitboard of all pieces.
         */
        Bitboard get_all();

        /**
         * @brief update the bitboards containing all the pieces of a color.
         */
        void update_all_boards();

        /**
         * @brief get a piece type from it's position.
         *
         * @param square of the piece.
         * @param color of the piece.
         * @return the piece type.
         */
        PieceType get_piece_type(Square square, Color color);

        /**
         * @brief set a bitboard to a specific value.
         *
         * @param color of the bitboard to set.
         * @param piece type to set.
         * @param value of the bitboard.
         */
        bool set(Color color, PieceType piece, Bitboard value);

        /**
         * @brief get the white_turn value.
         *
         * @return true if the turn is for the color white.
         */
        bool is_white_turn();

        /**
         * @brief get the current_color.
         *
         * @return the current color.
         */
        Color current_color();

        /**
         * @brief check if a move would collide with an ally piece.
         *
         * @param pos the bitboard after of the position the move.
         * @param color to check for.
         * @return true if the move collides.
         */
        bool would_collide(Bitboard pos, Color color);

        /**
         * @brief check if a move would capture an enemy piece.
         *
         * @param pos the bitboard of the position after the move.
         * @param color to check for.
         * @return true if the move captures.
         */
        bool would_capture(Bitboard pos, Color color);

        /**
         * @brief check if a moves captures en passant.
         *
         * @param pos the bitboard of the position after the move.
         * @return true if the moves captures en passant.
         */
        bool would_capture_en_passant(Bitboard pos);

        /**
         * @brief check if a castling is possible on the queen side.
         *
         * @param color to check for.
         * @return true if the move can be done.
         */
        bool can_queen_side_castling(Color color);

        /**
         * @brief check if a castling is possible on the king side.
         *
         * @param color to check for.
         * @return true if the move can be done.
         */
        bool can_king_side_castling(Color color);

        /**
         * @brief get a piece type and color from a position on the board.
         *
         * @param position a Position object.
         * @return the piece type and color or std::nullopt.
         */
        opt_piece_t operator[](const Position& position) const override;

        /**
         * @brief set the turn color.
         *
         * @param color to set the turn to.
         */
        void set_turn(Color color);

        /**
         * @brief Get the castling right for the given color and side.
         *
         * @param color the color of the castling right.
         * @param side the side of the caslting, either KING or QUEEN.
         * @return true if the corresponding right is set.
         */
        bool get_castling(Color color, PieceType side);

        /**
         * @brief Get the current en_passant square.
         *
         * @return the current en_passant Square or -1 if there is none.
         */
        Square get_en_passant();

        /**
         * @brief Get the current zobrist key of the board
         *
         * @return the zobrist key representation of the board
         */
        Zobrist get_zobrist_key();

        /**
         * @brief Regiseter a pointer to a dispositions history map.
         *
         * @param disps the pointer to the dispositions history map.
         */
        void register_dispositions_history(std::map<uint64_t, int>* disps);

    private:
        /**
         * @brief Array of Bitboards, arranged by Color and PieceType.
         */
        Bitboard bitboards_[2][BITBOARDS_NUMBER];

        /**
         * @brief Boolean determining the turn color.
         */
        bool white_turn_;

        /**
         * @brief Boolean for the white king side castling state.
         */
        bool white_king_side_castling_;

        /**
         * @brief Boolean for the white queen side castling state.
         */
        bool white_queen_side_castling_;

        /**
         * @brief Boolean for the black king side castling state.
         */
        bool black_king_side_castling_;

        /**
         * @brief Boolean for the black queen side castling state.
         */
        bool black_queen_side_castling_;

        /**
         * @brief Square of the en passant position of the last move.
         */
        Square en_passant_;

        /**
         * @brief Number of turn played.
         */
        unsigned int turn_;

        /**
         * @brief Number of turns whitout a capture or a pawn move.
         */
        int last_fifty_turns_ = 0;

        /**
         * @brief Zobrist key representing the current board in a 64 bits int.
         */
        Zobrist zobrist_key_;

        /**
         * @brief History of the game dispositions.
         */
        std::map<uint64_t, int>* dispositions_ = nullptr;

        /**
         * @brief Update the castling abilities after a move.
         *
         * @param color of the piece.
         * @param piece type.
         * @param from the square of the begining of the move.
         */
        void update_castling_abilities(Color color, PieceType piece,
                                       Square from);

        /**
         * @brief Move a piece on the board.
         *
         * @param color of the piece.
         * @param piece type
         * @param from the square of the begining of the move.
         * @param to the square of the end of the move.
         */
        void move_piece(Color color, PieceType piece, Square from, Square to);

        /**
         * @brief Remove a piece from the board.
         *
         * @param color of the piece.
         * @param piece type.
         * @param pos the square of the piece to remove.
         */
        void remove_piece(Color color, PieceType piece, Square pos);

        /**
         * @brief Add a piece on the board.
         *
         * @param color of the piece.
         * @param piece type.
         * @param pos the square where to add the piece.
         */
        void add_piece(Color color, PieceType piece, Square pos);
    };

} // namespace board

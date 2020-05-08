#include "chessboard-interface.hh"

namespace listener
{

    /**
     ** \brief Register the ChessboardInterface for later use.
     ** Called once per game at the beginning.
     **
     ** @param board_interface: The chessboard interface, part of
     ** the adapter design pattern
     */
    void register_board(const board::ChessboardInterface& board_interface)
    {}

    /**
     ** \brief Event when the game finishes.
     ** It is always the last method called.
     */
    void on_game_finished()
    {}

    /**
     ** \brief Must be called when a piece is moved.
     **
     ** @param piece: The moving piece.
     ** @param from:  The initial position of the piece.
     ** @param to:    The final position of the piece.
     */
    void on_piece_moved(const board::PieceType piece,
            const board::Position& from,
            const board::Position& to)
    {}

    /**
     ** \brief Must be called every time a piece is taken.
     ** It is always called *after* the move that causes the attack.
     **
     ** @param piece: The taken piece.
     ** @param at:    The position where the piece is taken.
     */
    void on_piece_taken(const board::PieceType piece,
            const board::Position& at)
    {}

    /**
     ** \brief Must be called when a pawn is promoted.
     ** It always happens *after* the pawn was moved
     **
     ** @param piece: The chosen type of piece of the promotion.
     ** @param at:    The position of the piece promoted.
     */
    void on_piece_promoted(const board::PieceType piece,
            const board::Position& at)
    {}

    /**
     ** \brief Event when a Kingside castling happens.
     ** It always happens *after* the move of the king was logged.
     ** The move of the rook must not be logged!
     **
     ** @param color: The color of the player concerned by the castling.
     */
    void on_kingside_castling(const board::Color color)
    {}

    /**
     ** \brief Event when a Queenside castling happens
     ** It always happens *after* the move of the king was logged.
     ** The move of the rook must not be logged!
     **
     ** @param color: The color of the player concerned by the castling
     */
    void on_queenside_castling(const board::Color color)
    {}

    /**
     ** \brief Event when a King is in check.
     ** Called after the move that put the King in check.
     **
     ** @param color: The color of the player whose King is in check
     */
    void on_player_check(const board::Color color)
    {}

    /**
     ** \brief Event when a King is checkmate.
     ** Called after the move that made it checkmate
     **
     ** @param color: The color of the player whose King is checkmate
     */
    void on_player_mat(const board::Color color)
    {}

    /**
     ** \brief Event when a player is pat.
     ** Called after the move that made it pat.
     **
     ** @param color: The color of the player who is pat.
     */
    void on_player_pat(const board::Color color)
    {}

    /**
     ** \brief Event when a player is disqualified.
     ** If the disqualification happends because of a move, this specific
     ** move is not logged but the previous ones are.
     **
     ** @param color: The color of the player who is disqualified.
     */
    void on_player_disqualified(const board::Color color)
    {}

    /**
     ** \brief Event when there is a draw game.
     */
    void on_draw()
    {}

} // namespace listener

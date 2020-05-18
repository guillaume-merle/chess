#include <iostream>

#include "pgn.hh"
#include "chessboard.hh"
#include "listener.hh"
#include "listener-manager.hh"

namespace board
{
    void pgn(std::vector<PgnMove> moves)
    {
        Chessboard board(START_POS);
        listener::listener_manager.register_board(board);

        for (auto& pgn_move : moves)
        {
            Move move = pgn_move.to_move(board);

            if (!board.is_move_legal(move))
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_player_disqualified,
                            board.current_color());
                listener::listener_manager
                    .notify(&listener::Listener::on_game_finished);
                break;
            }

            listener::listener_manager
                .notify(&listener::Listener::on_piece_moved,
                        pgn_move.piece_, pgn_move.start_, pgn_move.end_);

            if (move.is_queen_side_castling())
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_queenside_castling,
                            board.current_color());
            }
            if (move.is_king_side_castling())
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_kingside_castling,
                            board.current_color());
            }
            if (move.is_capture())
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_piece_taken,
                            move.get_capture(), pgn_move.end_);
            }
            if (move.is_en_passant())
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_piece_taken,
                            move.get_capture(), pgn_move.end_);
            }
            if (move.is_promotion())
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_piece_promoted,
                            move.get_promotion(), pgn_move.end_);
            }

            board.do_move(move);

            if (board.is_checkmate(board.current_color()))
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_player_mat,
                            board.current_color());
                listener::listener_manager
                    .notify(&listener::Listener::on_game_finished);
                break;
            }
            else if (board.is_check(board.current_color()))
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_player_check,
                            board.current_color());
            }
            else if (board.is_stalemate(board.current_color()))
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_player_pat,
                            board.current_color());
                listener::listener_manager
                    .notify(&listener::Listener::on_draw);
                listener::listener_manager
                    .notify(&listener::Listener::on_game_finished);
                break;
            }

            if (board.is_draw() || board.is_stalemate(board.current_color()))
            {
                listener::listener_manager
                    .notify(&listener::Listener::on_draw);
                listener::listener_manager
                    .notify(&listener::Listener::on_game_finished);
                break;
            }
        }

    }
} // namespace board

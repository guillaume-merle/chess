#include "movegen.hh"
#include "attacks.hh"
#include "pawn.hh"
#include <iostream>

namespace board
{
    MoveGen::MoveGen(Chessboard& board)
    {
        generate_moves(board);
    }

    MoveGen::MoveGen(Chessboard& board, Color color)
    {
        generate_moves_for_color(board, color);
    }

    std::vector<Move> MoveGen::get()
    {
        return moves_;
    }

    void MoveGen::generate_moves(Chessboard& board)
    {
        Color color = board.current_color();
        generate_moves_for_color(board, color);
    }

    void MoveGen::generate_moves_for_color(Chessboard& board, Color color)
    {
        moves_.reserve(MAX_MOVES_SIZE);

        generate_pawn_moves(board, color);
        generate_knight_moves(board, color);
        generate_king_moves(board, color);

        // ignore the opposite king for sliding pieces attacks, to avoid false
        // check evasions
        // Bitboard king = board.get(opposite_color(color), KING);
        // board.set(opposite_color(color), KING, 0);

        generate_rook_moves(board, color);
        generate_bishop_moves(board, color);
        generate_queen_moves(board, color);

        // board.set(opposite_color(color), KING, king);
    }

    void MoveGen::generate_king_moves(Chessboard& board, Color color)
    {
        Bitboard king = board.get(color, KING);
        if (!king)
            return;

        Square square = bitscan(king);

        Bitboard moves = attacks::get_king_attacks(square);
        add_moves(board, KING, color, square, moves);

        Square from = color == WHITE ? 4 : 60;

        if (board.can_king_side_castling(color))
        {
            Square to = from + 2;
            moves_.emplace_back(Move(from, to, KING, MoveFlag::KING_CASTLING));
        }

        if (board.can_queen_side_castling(color))
        {
            Square to = from - 2;
            moves_.emplace_back(Move(from, to, KING, MoveFlag::QUEEN_CASTLING));
        }
    }

    void MoveGen::generate_knight_moves(Chessboard& board, Color color)
    {
        Bitboard knights = board.get(color, KNIGHT);

        while (knights)
        {
            Square square = pop(knights);
            Bitboard moves = attacks::get_knight_attacks(square);

            add_moves(board, KNIGHT, color, square, moves);
        }
    }

    void MoveGen::generate_pawn_moves(Chessboard& board, Color color)
    {
        Bitboard pawns = board.get(color, PAWN);
        auto all_pieces = board.get(WHITE, ALL)
                          | board.get(BLACK, ALL);

        while (pawns)
        {
            Square square = pop(pawns);
            Bitboard bitboard = 1ULL << square;

            auto move = Pawn::single_push(bitboard, color);

            if (move && (move & all_pieces) == 0)
            {
                if ((color == WHITE && (move & Rank8BB) != 0)
                    || (color == BLACK && (move & Rank1BB) != 0))
                {
                    moves_.emplace_back(Move(square, bitscan(move), PAWN, QUEEN,
                                             MoveFlag::PROMOTION));

                    moves_.emplace_back(Move(square, bitscan(move), PAWN,
                                             KNIGHT, MoveFlag::PROMOTION));

                    moves_.emplace_back(Move(square, bitscan(move), PAWN,
                                             BISHOP, MoveFlag::PROMOTION));

                    moves_.emplace_back(Move(square, bitscan(move), PAWN,
                                             ROOK, MoveFlag::PROMOTION));
                }
                else
                {
                    moves_.emplace_back(Move(square, bitscan(move), PAWN));
                }

                if ((color == WHITE && (bitboard & Rank2BB))
                     || (color == BLACK && (bitboard & Rank7BB)))
                {
                    move = Pawn::double_push(bitboard, color);
                    if (move && (move & all_pieces) == 0)
                        moves_.emplace_back(Move(square, bitscan(move), PAWN,
                                                 MoveFlag::DOUBLE_PAWN_PUSH));
                }
            }

            Bitboard attacks = attacks::get_pawn_attacks(square, color);

            while (attacks)
            {
                Square attacked_square = pop(attacks);
                Bitboard attacked = 1ULL << attacked_square;

                if (board.would_capture(attacked, color))
                {
                    PieceType capture = board.get_piece_type(attacked_square,
                                                        opposite_color(color));
                    if ((color == WHITE && (attacked & Rank8BB) != 0)
                        || (color == BLACK && (attacked & Rank1BB) != 0))
                    {
                        moves_.emplace_back(Move(square, attacked_square, PAWN,
                                      QUEEN, capture,
                                      MoveFlag::PROMOTION | MoveFlag::CAPTURE));

                        moves_.emplace_back(Move(square, attacked_square, PAWN,
                                      KNIGHT, capture,
                                      MoveFlag::PROMOTION | MoveFlag::CAPTURE));

                        moves_.emplace_back(Move(square, attacked_square, PAWN,
                                      BISHOP, capture,
                                      MoveFlag::PROMOTION | MoveFlag::CAPTURE));

                        moves_.emplace_back(Move(square, attacked_square, PAWN,
                                      ROOK, capture,
                                      MoveFlag::PROMOTION | MoveFlag::CAPTURE));
                    }
                    else
                    {
                        moves_.emplace_back(Move(square, attacked_square, PAWN,
                                                 capture, MoveFlag::CAPTURE));
                    }
                }
                else if (board.would_capture_en_passant(attacked))
                {
                    auto move = Move(square, attacked_square, PAWN, PAWN,
                                     MoveFlag::EN_PASSANT);
                    moves_.emplace_back(move);
                }
            }
        }
    }

    void MoveGen::generate_rook_moves(Chessboard& board, Color color)
    {
        Bitboard rook = board.get(color, ROOK);

        Bitboard occupancy = board.get(color, ALL)
                             | board.get(opposite_color(color), ALL);

        while (rook)
        {
            Square square = pop(rook);
            Bitboard moves = attacks::get_rook_attacks(square, occupancy);

            add_moves(board, ROOK, color, square, moves);
        }
    }

    void MoveGen::generate_bishop_moves(Chessboard& board, Color color)
    {
        Bitboard bishop = board.get(color, BISHOP);

        Bitboard occupancy = board.get(color, ALL)
                             | board.get(opposite_color(color), ALL);

        while (bishop)
        {
            Square square = pop(bishop);
            Bitboard moves = attacks::get_bishop_attacks(square, occupancy);

            add_moves(board, BISHOP, color, square, moves);
        }
    }

    void MoveGen::generate_queen_moves(Chessboard& board, Color color)
    {
        Bitboard queen = board.get(color, QUEEN);

        Bitboard occupancy = board.get(color, ALL)
                             | board.get(opposite_color(color), ALL);

        while (queen)
        {
            Square square = pop(queen);
            Bitboard moves = attacks::get_queen_attacks(square, occupancy);

            add_moves(board, QUEEN, color, square, moves);
        }
    }

    void MoveGen::add_moves(Chessboard& board, PieceType piece, Color color,
                  Square from, Bitboard moves)
    {
        Bitboard attacks = moves & board.get(opposite_color(color), ALL);

        while (attacks)
        {
            Square to = pop(attacks);
            PieceType capture =
                board.get_piece_type(to, opposite_color(color));

            moves_.emplace_back(Move(from, to, piece,
                                     capture, MoveFlag::CAPTURE));
        }

        Bitboard other_moves = moves & ~board.get(color, ALL)
                                     & ~board.get(opposite_color(color), ALL);

        while (other_moves)
        {
            Square to = pop(other_moves);
            moves_.emplace_back(Move(from, to, piece));
        }
    }
}

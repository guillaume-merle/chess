#include "movegen.hh"
#include "attacks.hh"

namespace board
{
    MoveGen::MoveGen(Chessboard& board)
    {
        generate_moves(board);
    }

    void MoveGen::generate_moves(Chessboard& board)
    {
        Color color = board.is_white_turn() ? WHITE : BLACK;

        generate_pawn_moves(board, color);
        generate_knight_moves(board, color);
        generate_king_moves(board, color);
        generate_rook_moves(board, color);
        generate_bishop_moves(board, color);
        generate_queen_moves(board, color);
    }

    void MoveGen::generate_king_moves(Chessboard& board, Color color)
    {
        Bitboard king = board.get(color, KING);
        if (!king)
            return;

        Square square = bitscan(king);

        Bitboard moves = attacks::get_king_attacks(square);
        add_moves(board, KING, color, king, moves);
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

    void MoveGen::generate_pawn_moves(Chessboard&, Color)
    {

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
        Bitboard bishop = board.get(color, ROOK);

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
            Bitboard moves = attacks::get_bishop_attacks(square, occupancy);

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

            moves_.emplace_back(Move(from, to, piece, capture));
        }

        Bitboard other_moves = moves & ~board.get(color, ALL) & ~attacks;

        while (other_moves)
        {
            Square to = pop(other_moves);
            moves_.emplace_back(Move(from, to, piece));
        }
    }
}

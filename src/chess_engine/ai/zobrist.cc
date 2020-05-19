#include <random>

#include "zobrist.hh"
#include "chessboard.hh"

namespace board
{
    uint64_t Zobrist::pieces_[2][6][64];
    uint64_t Zobrist::white_turn_;
    uint64_t Zobrist::king_side_castling_[2];
    uint64_t Zobrist::queen_side_castling_[2];
    uint64_t Zobrist::en_passant_[8];

    void Zobrist::init()
    {
        // Pseudo Random Number Generator,
        // based on the mersenne twister algorithm
        std::mt19937_64 prng;

        // Generates random values used to seed the PRNG
        std::random_device device;

        // Seed sequence to seed the PRNG
        std::seed_seq seed_seq{device(), device(), device(), device()};

        prng.seed(seed_seq);

        // Used to distribute the random numbers in a uniform way
        std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);

        for (int color = 0; color < 2; color++)
        {
            for (int piece = 0; piece < 6; piece++)
            {
                for (Square square = 0; square < 64; square++)
                {
                    pieces_[color][piece][square] = distribution(prng);
                }
            }
        }

        white_turn_ = distribution(prng);

        for (int color = 0; color < 2; color++)
        {
            king_side_castling_[color] = distribution(prng);
            queen_side_castling_[color] = distribution(prng);
        }

        for (int file = 0; file < 8; file++)
        {
            en_passant_[file] = distribution(prng);
        }
    }

    Zobrist::Zobrist(Chessboard& board)
        : key_(0)
    {
        for (auto piece : { QUEEN, ROOK, BISHOP, KNIGHT, PAWN, KING })
        {
            for (auto color : { WHITE, BLACK })
            {
                Bitboard pieces = board.get(color, piece);

                while (pieces)
                {
                    Square square = pop(pieces);
                    key_ ^= pieces_[color][piece][square];
                }
            }
        }

        if (board.is_white_turn())
            key_ ^= white_turn_;

        for (auto color : { WHITE, BLACK })
        {
            if (board.get_castling(color, QUEEN))
                key_ ^= queen_side_castling_[color];

            if (board.get_castling(color, KING))
                key_ ^= king_side_castling_[color];
        }

        en_passant_square_ = board.get_en_passant();
        if (en_passant_square_ != -1)
        {
            // the en_passant_square % 8 is to get the File of the square
            key_ ^= en_passant_[en_passant_square_ % 8];
        }
    }

    void Zobrist::update_piece(Color color, PieceType piece, Square pos)
    {
        // update piece at the given position
        key_ ^= pieces_[color][piece][pos];
    }

    // void Zobrist::update_key(Color color, Move& move)
    // {
    //     if (move.is_capture())
    //         key_ ^= pieces_[color][move.get_capture()][move.get_to()];
    //
    //     // double pawn push
    //     else if (move.is_double_pawn_push())
    //     {
    //         // unset last en_passant
    //         if (en_passant_square_ != -1)
    //             key_ ^= en_passant_[en_passant_square_ % 8];
    //
    //         en_passant_square_ = move.get_from() + (color == WHITE ? 8 : -8);
    //
    //         // set new en_passant
    //         key_ ^= en_passant_[en_passant_square_ % 8];
    //     }
    //     // en_passant
    //     else if (move.is_en_passant())
    //     {
    //         // remove piece captured en_passant
    //         Square capture = move.get_to() + (color == WHITE ? -8 : 8);
    //         key_ ^= pieces_[color][move.get_capture()][capture];
    //     }
    //     // queen castling
    //     if (move.is_queen_side_castling())
    //     {
    //         Square rook_from = color == WHITE ? 7 : 63;
    //         key_ ^= pieces_[color][ROOK][rook_from];
    //     }
    //     // king castling
    //
    //     // remove piece at the from position
    //     key_ ^= pieces_[color][move.get_piece()][move.get_from()];
    //     // add piece at the to position
    //     key_ ^= pieces_[color][move.get_piece()][move.get_to()];
    //
    //     // promotion
    //     if (move.is_promotion())
    //     {
    //         // remove promoted piece
    //         key_ ^= pieces_[color][move.get_piece()][move.get_to()];
    //         // add new piece
    //         key_ ^= pieces_[color][move.get_promotion()][move.get_to()];
    //     }
    //
    //     // update turn
    //     key_ ^= white_turn_;
    // }

} // namespace board

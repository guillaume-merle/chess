#include <random>

#include "zobrist.hh"

namespace ai
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
}

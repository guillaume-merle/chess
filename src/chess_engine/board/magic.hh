#pragma once

#include "bitboard.hh"

#define MINIMAL_B_BITS_SHIFT(square) 55
#define MINIMAL_R_BITS_SHIFT(square) 52

namespace board
{
    /**
     * @brief Class containing the magic moves of the bishop and rook.
     *
     * Magic numbers and shifts are used to store moves corresponding
     * to the different occupancies.
     *
     */
    class Magic
    {
    public:
        /**
         * @brief Initialize magic moves.
         */
        Magic();

        /**
         * @brief Initialize magic moves.
         */
        Bitboard get_bishop_moves(Square square, Bitboard occupancy) const;

        /**
         * @brief Initialize magic moves.
         */
        Bitboard get_rook_moves(Square square, Bitboard occupancy) const;

    private:
        /**
         * @brief All possible bishop moves.
         */
        Bitboard bishop_moves_[5248];

        /**
         * @brief All possible rook moves.
         */
        Bitboard rook_moves_[102400];
        /**
         * @brief Initialize magic moves.
         */
        Bitboard* bishop_indices_[64]=
        {
            bishop_moves_+4992, bishop_moves_+2624,  bishop_moves_+256,  bishop_moves_+896,
            bishop_moves_+1280, bishop_moves_+1664, bishop_moves_+4800, bishop_moves_+5120,
            bishop_moves_+2560, bishop_moves_+2656,  bishop_moves_+288,  bishop_moves_+928,
            bishop_moves_+1312, bishop_moves_+1696, bishop_moves_+4832, bishop_moves_+4928,
            bishop_moves_+0,     bishop_moves_+128,  bishop_moves_+320,  bishop_moves_+960,
            bishop_moves_+1344, bishop_moves_+1728, bishop_moves_+2304, bishop_moves_+2432,
            bishop_moves_+32,    bishop_moves_+160,  bishop_moves_+448, bishop_moves_+2752,
            bishop_moves_+3776, bishop_moves_+1856, bishop_moves_+2336, bishop_moves_+2464,
            bishop_moves_+64,    bishop_moves_+192,  bishop_moves_+576, bishop_moves_+3264,
            bishop_moves_+4288, bishop_moves_+1984, bishop_moves_+2368, bishop_moves_+2496,
            bishop_moves_+96,    bishop_moves_+224,  bishop_moves_+704, bishop_moves_+1088,
            bishop_moves_+1472, bishop_moves_+2112, bishop_moves_+2400, bishop_moves_+2528,
            bishop_moves_+2592, bishop_moves_+2688,  bishop_moves_+832, bishop_moves_+1216,
            bishop_moves_+1600, bishop_moves_+2240, bishop_moves_+4864, bishop_moves_+4960,
            bishop_moves_+5056, bishop_moves_+2720,  bishop_moves_+864, bishop_moves_+1248,
            bishop_moves_+1632, bishop_moves_+2272, bishop_moves_+4896, bishop_moves_+5184
        };

        Bitboard* rook_indices_[64]=
        {
            rook_moves_+86016, rook_moves_+73728, rook_moves_+36864, rook_moves_+43008,
            rook_moves_+47104, rook_moves_+51200, rook_moves_+77824, rook_moves_+94208,
            rook_moves_+69632, rook_moves_+32768, rook_moves_+38912, rook_moves_+10240,
            rook_moves_+14336, rook_moves_+53248, rook_moves_+57344, rook_moves_+81920,
            rook_moves_+24576, rook_moves_+33792,  rook_moves_+6144, rook_moves_+11264,
            rook_moves_+15360, rook_moves_+18432, rook_moves_+58368, rook_moves_+61440,
            rook_moves_+26624,  rook_moves_+4096,  rook_moves_+7168,     rook_moves_+0,
            rook_moves_+2048, rook_moves_+19456, rook_moves_+22528, rook_moves_+63488,
            rook_moves_+28672,  rook_moves_+5120,  rook_moves_+8192,  rook_moves_+1024,
            rook_moves_+3072, rook_moves_+20480, rook_moves_+23552, rook_moves_+65536,
            rook_moves_+30720, rook_moves_+34816,  rook_moves_+9216, rook_moves_+12288,
            rook_moves_+16384, rook_moves_+21504, rook_moves_+59392, rook_moves_+67584,
            rook_moves_+71680, rook_moves_+35840, rook_moves_+39936, rook_moves_+13312,
            rook_moves_+17408, rook_moves_+54272, rook_moves_+60416, rook_moves_+83968,
            rook_moves_+90112, rook_moves_+75776, rook_moves_+40960, rook_moves_+45056,
            rook_moves_+49152, rook_moves_+55296, rook_moves_+79872, rook_moves_+98304
        };
        void init();
    };

    extern Magic magic;
} // namespace board

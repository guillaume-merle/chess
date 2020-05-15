#include "magic.hh"

namespace board
{
    Magic magic;

    const unsigned int rook_shift[64] =
    {
        52, 53, 53, 53, 53, 53, 53, 52,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 53, 53, 53, 53, 53
    };

    const Bitboard rook_magics[64] =
    {
        0x0080001020400080ULL, 0x0040001000200040ULL, 0x0080081000200080ULL,
        0x0080040800100080ULL, 0x0080020400080080ULL, 0x0080010200040080ULL,
        0x0080008001000200ULL, 0x0080002040800100ULL, 0x0000800020400080ULL,
        0x0000400020005000ULL, 0x0000801000200080ULL, 0x0000800800100080ULL,
        0x0000800400080080ULL, 0x0000800200040080ULL, 0x0000800100020080ULL,
        0x0000800040800100ULL, 0x0000208000400080ULL, 0x0000404000201000ULL,
        0x0000808010002000ULL, 0x0000808008001000ULL, 0x0000808004000800ULL,
        0x0000808002000400ULL, 0x0000010100020004ULL, 0x0000020000408104ULL,
        0x0000208080004000ULL, 0x0000200040005000ULL, 0x0000100080200080ULL,
        0x0000080080100080ULL, 0x0000040080080080ULL, 0x0000020080040080ULL,
        0x0000010080800200ULL, 0x0000800080004100ULL, 0x0000204000800080ULL,
        0x0000200040401000ULL, 0x0000100080802000ULL, 0x0000080080801000ULL,
        0x0000040080800800ULL, 0x0000020080800400ULL, 0x0000020001010004ULL,
        0x0000800040800100ULL, 0x0000204000808000ULL, 0x0000200040008080ULL,
        0x0000100020008080ULL, 0x0000080010008080ULL, 0x0000040008008080ULL,
        0x0000020004008080ULL, 0x0000010002008080ULL, 0x0000004081020004ULL,
        0x0000204000800080ULL, 0x0000200040008080ULL, 0x0000100020008080ULL,
        0x0000080010008080ULL, 0x0000040008008080ULL, 0x0000020004008080ULL,
        0x0000800100020080ULL, 0x0000800041000080ULL, 0x00FFFCDDFCED714AULL,
        0x007FFCDDFCED714AULL, 0x003FFFCDFFD88096ULL, 0x0000040810002101ULL,
        0x0001000204080011ULL, 0x0001000204000801ULL, 0x0001000082000401ULL,
        0x0001FFFAABFAD1A2ULL
    };

    const Bitboard rook_mask[64]=
    {
        0x000101010101017EULL, 0x000202020202027CULL, 0x000404040404047AULL,
        0x0008080808080876ULL, 0x001010101010106EULL, 0x002020202020205EULL,
        0x004040404040403EULL, 0x008080808080807EULL, 0x0001010101017E00ULL,
        0x0002020202027C00ULL, 0x0004040404047A00ULL, 0x0008080808087600ULL,
        0x0010101010106E00ULL, 0x0020202020205E00ULL, 0x0040404040403E00ULL,
        0x0080808080807E00ULL, 0x00010101017E0100ULL, 0x00020202027C0200ULL,
        0x00040404047A0400ULL, 0x0008080808760800ULL, 0x00101010106E1000ULL,
        0x00202020205E2000ULL, 0x00404040403E4000ULL, 0x00808080807E8000ULL,
        0x000101017E010100ULL, 0x000202027C020200ULL, 0x000404047A040400ULL,
        0x0008080876080800ULL, 0x001010106E101000ULL, 0x002020205E202000ULL,
        0x004040403E404000ULL, 0x008080807E808000ULL, 0x0001017E01010100ULL,
        0x0002027C02020200ULL, 0x0004047A04040400ULL, 0x0008087608080800ULL,
        0x0010106E10101000ULL, 0x0020205E20202000ULL, 0x0040403E40404000ULL,
        0x0080807E80808000ULL, 0x00017E0101010100ULL, 0x00027C0202020200ULL,
        0x00047A0404040400ULL, 0x0008760808080800ULL, 0x00106E1010101000ULL,
        0x00205E2020202000ULL, 0x00403E4040404000ULL, 0x00807E8080808000ULL,
        0x007E010101010100ULL, 0x007C020202020200ULL, 0x007A040404040400ULL,
        0x0076080808080800ULL, 0x006E101010101000ULL, 0x005E202020202000ULL,
        0x003E404040404000ULL, 0x007E808080808000ULL, 0x7E01010101010100ULL,
        0x7C02020202020200ULL, 0x7A04040404040400ULL, 0x7608080808080800ULL,
        0x6E10101010101000ULL, 0x5E20202020202000ULL, 0x3E40404040404000ULL,
        0x7E80808080808000ULL
    };

    const unsigned int bishop_shift[64] =
    {
        58, 59, 59, 59, 59, 59, 59, 58,
        59, 59, 59, 59, 59, 59, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 59, 59, 59, 59, 59, 59,
        58, 59, 59, 59, 59, 59, 59, 58
    };

    const Bitboard bishop_magics[64] =
    {
        0x0002020202020200ULL, 0x0002020202020000ULL, 0x0004010202000000ULL,
        0x0004040080000000ULL, 0x0001104000000000ULL, 0x0000821040000000ULL,
        0x0000410410400000ULL, 0x0000104104104000ULL, 0x0000040404040400ULL,
        0x0000020202020200ULL, 0x0000040102020000ULL, 0x0000040400800000ULL,
        0x0000011040000000ULL, 0x0000008210400000ULL, 0x0000004104104000ULL,
        0x0000002082082000ULL, 0x0004000808080800ULL, 0x0002000404040400ULL,
        0x0001000202020200ULL, 0x0000800802004000ULL, 0x0000800400A00000ULL,
        0x0000200100884000ULL, 0x0000400082082000ULL, 0x0000200041041000ULL,
        0x0002080010101000ULL, 0x0001040008080800ULL, 0x0000208004010400ULL,
        0x0000404004010200ULL, 0x0000840000802000ULL, 0x0000404002011000ULL,
        0x0000808001041000ULL, 0x0000404000820800ULL, 0x0001041000202000ULL,
        0x0000820800101000ULL, 0x0000104400080800ULL, 0x0000020080080080ULL,
        0x0000404040040100ULL, 0x0000808100020100ULL, 0x0001010100020800ULL,
        0x0000808080010400ULL, 0x0000820820004000ULL, 0x0000410410002000ULL,
        0x0000082088001000ULL, 0x0000002011000800ULL, 0x0000080100400400ULL,
        0x0001010101000200ULL, 0x0002020202000400ULL, 0x0001010101000200ULL,
        0x0000410410400000ULL, 0x0000208208200000ULL, 0x0000002084100000ULL,
        0x0000000020880000ULL, 0x0000001002020000ULL, 0x0000040408020000ULL,
        0x0004040404040000ULL, 0x0002020202020000ULL, 0x0000104104104000ULL,
        0x0000002082082000ULL, 0x0000000020841000ULL, 0x0000000000208800ULL,
        0x0000000010020200ULL, 0x0000000404080200ULL, 0x0000040404040400ULL,
        0x0002020202020200ULL
    };


    const Bitboard bishop_mask[64] =
    {
        0x0040201008040200ULL, 0x0000402010080400ULL, 0x0000004020100A00ULL,
        0x0000000040221400ULL, 0x0000000002442800ULL, 0x0000000204085000ULL,
        0x0000020408102000ULL, 0x0002040810204000ULL, 0x0020100804020000ULL,
        0x0040201008040000ULL, 0x00004020100A0000ULL, 0x0000004022140000ULL,
        0x0000000244280000ULL, 0x0000020408500000ULL, 0x0002040810200000ULL,
        0x0004081020400000ULL, 0x0010080402000200ULL, 0x0020100804000400ULL,
        0x004020100A000A00ULL, 0x0000402214001400ULL, 0x0000024428002800ULL,
        0x0002040850005000ULL, 0x0004081020002000ULL, 0x0008102040004000ULL,
        0x0008040200020400ULL, 0x0010080400040800ULL, 0x0020100A000A1000ULL,
        0x0040221400142200ULL, 0x0002442800284400ULL, 0x0004085000500800ULL,
        0x0008102000201000ULL, 0x0010204000402000ULL, 0x0004020002040800ULL,
        0x0008040004081000ULL, 0x00100A000A102000ULL, 0x0022140014224000ULL,
        0x0044280028440200ULL, 0x0008500050080400ULL, 0x0010200020100800ULL,
        0x0020400040201000ULL, 0x0002000204081000ULL, 0x0004000408102000ULL,
        0x000A000A10204000ULL, 0x0014001422400000ULL, 0x0028002844020000ULL,
        0x0050005008040200ULL, 0x0020002010080400ULL, 0x0040004020100800ULL,
        0x0000020408102000ULL, 0x0000040810204000ULL, 0x00000A1020400000ULL,
        0x0000142240000000ULL, 0x0000284402000000ULL, 0x0000500804020000ULL,
        0x0000201008040200ULL, 0x0000402010080400ULL, 0x0002040810204000ULL,
        0x0004081020400000ULL, 0x000A102040000000ULL, 0x0014224000000000ULL,
        0x0028440200000000ULL, 0x0050080402000000ULL, 0x0020100804020000ULL,
        0x0040201008040200ULL
    };

    const int magic_database[64] =
    {
        63,  0, 58,  1, 59, 47, 53,  2,
        60, 39, 48, 27, 54, 33, 42,  3,
        61, 51, 37, 40, 49, 18, 28, 20,
        55, 30, 34, 11, 43, 14, 22,  4,
        62, 57, 46, 52, 38, 26, 32, 41,
        50, 36, 17, 19, 29, 10, 13, 21,
        56, 45, 25, 31, 35, 16,  9, 12,
        44, 24, 15,  8, 23,  7,  6,  5
    };

    static Bitboard init_occupancy(const int* squares, const int size,
                                   const Bitboard line_occupancy)
    {
        Bitboard ret = 0;

        for (int i = 0; i < size; i++)
        {
            Bitboard pos = 1ULL << i;
            if (line_occupancy & pos)
                ret |= 1ULL << squares[i];
        }

        return ret;
    }

    static Bitboard init_rook_moves(const int square, const Bitboard occ)
    {
        Bitboard ret = 0;

        Bitboard bit;
        Bitboard base = 0xFF;
        Bitboard rowbits = base << (8 * (square / 8));

        bit = 1ULL << square;

        do {
            bit <<= 8;
            ret |= bit;
        } while (bit && !(bit & occ));

        bit = 1ULL << square;
        do {
            bit >>= 8;
            ret |= bit;
        } while (bit && !(bit & occ));

        bit= 1ULL << square;

        do {
            bit <<= 1;
            if (bit & rowbits)
                ret |= bit;
            else
                break;
        } while(!(bit & occ));

        bit = 1ULL << square;

        do {
            bit >>= 1;
            if(bit&rowbits)
                ret |= bit;
            else
                break;
        } while(!(bit & occ));

        return ret;
    }

    static Bitboard init_bishop_moves(const int square, const Bitboard occ)
    {
        Bitboard ret = 0;
        Bitboard bit;
        Bitboard bit2;
        Bitboard base = 0xFF;

        Bitboard rowbits = base << (8 * (square / 8));

        bit = 1ULL <<square;
        bit2 = bit;
        do {
            bit <<= 8 - 1;
            bit2 >>= 1;
            if(bit2 & rowbits)
                ret |= bit;
            else
                break;
        } while (bit && !(bit & occ));

        bit= 1ULL << square;
        bit2 = bit;

        do {
            bit <<= 8 + 1;
            bit2 <<= 1;
            if(bit2 & rowbits)
                ret |= bit;
            else
                break;
        } while (bit && !(bit & occ));

        bit = 1ULL << square;
        bit2 = bit;

        do {
            bit >>= 8 - 1;
            bit2 <<= 1;

            if(bit2 & rowbits)
                ret |= bit;
            else
                break;
        } while (bit && !(bit & occ));

        bit= 1ULL <<square;
        bit2 = bit;

        do {
            bit >>= 8 + 1;
            bit2 >>= 1;
            if(bit2 & rowbits)
                ret |= bit;
            else
                break;
        } while (bit && !(bit & occ));

        return ret;
    }

    // static inline int get_bishop_index(int square, Bitboard occupancy)
    // {
        // int shift = bishop_shift[square];
        // int magic = bishop_magics[square];
        // int index = bishop_indices[square] + ((occupancy * magic) >> shift);
        // return index;
    // }
//
    // static inline int get_rook_index(int square, Bitboard occupancy)
    // {
        // int shift = rook_shift[square];
        // int magic = rook_magics[square];
        // int index = rook_indices[square] + ((occupancy * magic) >> shift);
        // return index;
    // }
#define BmagicNOMASK2(square, occupancy) *(bishop_indices_[square]+(((occupancy)*bishop_magics[square])>>bishop_shift[square]))
#define RmagicNOMASK2(square, occupancy) *(rook_indices_[square]+(((occupancy)*rook_magics[square])>>rook_shift[square]))

    Magic::Magic()
    {
        init();
    }

    Bitboard Magic::get_bishop_moves(Square square, Bitboard occupancy) const
    {
        return *(bishop_indices_[square] +
                (((occupancy & bishop_mask[square])
                  * bishop_magics[square])
                 >> bishop_shift[square]));
    }

    Bitboard Magic::get_rook_moves(Square square, Bitboard occupancy) const
    {
        return *(rook_indices_[square] +
                (((occupancy & rook_mask[square])
                  * rook_magics[square])
                 >> rook_shift[square]));
    }

    void Magic::init()
    {
        for(int i = 0; i < 64; i++)
        {
            int squares[64];
            int numsquares = 0;

            Bitboard temp = bishop_mask[i];

            while (temp)
            {
                Bitboard bit = temp & -temp;
                squares[numsquares++] =
                    magic_database[(bit * 0x07EDD5E59A4E28C2ULL) >> 58];
                temp ^= bit;
            }

            for (temp = 0; temp < ((Bitboard)(1) << numsquares); temp++)
            {
                Bitboard tempocc =
                    init_occupancy(squares, numsquares, temp);

                BmagicNOMASK2(i, tempocc) =
                    init_bishop_moves(i, tempocc);
            }
        }

        for (int i = 0; i < 64; i++)
        {
            int squares[64];
            int numsquares = 0;

            Bitboard temp = rook_mask[i];

            while (temp)
            {
                Bitboard bit = temp & -temp;
                squares[numsquares++] =
                    magic_database[(bit * 0x07EDD5E59A4E28C2ULL) >> 58];
                temp^=bit;
            }

            for (temp = 0; temp < ((Bitboard)(1) << numsquares); temp++)
            {
                Bitboard tempocc =
                    init_occupancy(squares, numsquares, temp);

                RmagicNOMASK2(i, tempocc) =
                    init_rook_moves(i, tempocc);
            }
        }
    }
} // namespace board

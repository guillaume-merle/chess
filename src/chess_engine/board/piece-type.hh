#pragma once

#include <array>
#include <optional>
#include <iostream>

namespace board
{
    /* PieceType is an enum representing every possible
     * piece type present on the board. The char associated
     * with each value is the ascii char representing the
     * piece on the board */
    enum PieceType
    {
        QUEEN = 0,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN,
        KING, // Last position allows better optimization (order-move)
        ALL,
    };

    using opt_piecetype_t = std::optional<PieceType>;

    inline PieceType char_to_piece(const char c)
    {
        switch (c)
        {
        case 'P':
            return PieceType::PAWN;
        case 'N':
            return PieceType::KNIGHT;
        case 'B':
            return PieceType::BISHOP;
        case 'R':
            return PieceType::ROOK;
        case 'Q':
            return PieceType::QUEEN;
        case 'K':
            return PieceType::KING;
        case 'A':
            return PieceType::ALL;
        default:
            throw std::invalid_argument("Unknown piece");
        }
    }

    inline PieceType char_to_black_piece(const char c)
    {
        switch (c)
        {
        case 'p':
            return PieceType::PAWN;
        case 'n':
            return PieceType::KNIGHT;
        case 'b':
            return PieceType::BISHOP;
        case 'r':
            return PieceType::ROOK;
        case 'q':
            return PieceType::QUEEN;
        case 'k':
            return PieceType::KING;
        case 'a':
            return PieceType::ALL;
        default:
            throw std::invalid_argument("Unknown piece");
        }
    }

} // namespace board

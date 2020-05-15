#pragma once

#include <string>
#include <vector>

#include "perft-object.hh"

namespace perft_parser
{
    board::PerftObject parse_perft(std::string input);

    board::FenObject parse_fen(std::string fen);
} // namespace perft_parser

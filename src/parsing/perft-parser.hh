#pragma once

#include <string>
#include <vector>

#include "pgn-move.hh"
#include "report-type.hh"

namespace perft_parser
{
    class PerftParser
    {
    public:
        // Constructor of the functor
        PerftParser() = default;

        PerfObject parse_perft(std::string input);

        FenObject parse_fen(std::vector<string> splited_input);
    };
} // namespace perft_parser

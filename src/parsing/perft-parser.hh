#pragma once

#include <string>
#include <vector>

#include "perft-object.hh"
#include "fen-object.hh"

namespace perft_parser
{
    class PerftParser
    {
    public:
        // Constructor of the functor
        PerftParser() = default;

        PerftObject parse_perft(std::string input);

        FenObject parse_fen(std::vector<std::string> splited_input);
    };
} // namespace perft_parser

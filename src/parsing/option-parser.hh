#pragma once

#include <optional>

#include "perft-parser.hh"
#include "pgn-parser.hh"

namespace option_parser
{
    struct Options
    {
        bool perft_;
        bool pgn_;
        std::vector<board::PgnMove> pgn_vect_;
        std::optional<board::PerftObject> perft_obj_;
    };

    Options parse_options(int argc, char** argv); //TODO
} // namespace option_parser

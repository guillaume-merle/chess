#include <fstream>
#include <iostream>

#include "perft-parser.hh"

namespace perft_parser
{
    board::PerftObject parse_perft(std::string input)
    {
        int depth = 0;
        std::vector<std::string> splited_input;

        std::ifstream file(input);
        if (!file.is_open())
        {
            std::cerr << "Failed to open" << std::endl;
            //TODO error
        }
        for(std::string line; getline(file, line);)
        {
            splited_input.push_back(line);
            depth++;
        }
        return board::PerftObject(parse_fen(splited_input), depth);
    }

    board::FenObject parse_fen(std::vector<std::string>)
    {
        return board::FenObject(); //TODO
    }
} // namespace perft_parser

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/program_options.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <iostream>

#include "pgn-parser.hh"
#include "option-parser.hh"

namespace option_parser
{
    namespace po = boost::program_options;

    void parse_options(int argc, char** argv)
    {
        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "show usage")
            ("pgn", po::value<std::string>(), "path to the PGN game file")
            ("listeners,l", po::value<std::vector<std::string>>(),
                "list of paths to listener plugins")
            ("perft", po::value<std::string>(), "path to a perft game file")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help") || vm.count("h"))
        {
            std::cout << desc << "\n";
        }

        if (vm.count("pgn"))
        {
            std::vector<board::PgnMove> pgn_vect = pgn_parser::parse_pgn(
                                                   vm["pgn"].as<std::string>());
        }

        if (vm.count("l") || vm.count("listeners"))
        {
            std::cout << "listeners path are " << std::endl;
            if (vm.count("l"))
            {
                for (size_t i = 0;
                    i < vm["l"].as<std::vector<std::string>>().size(); ++i)
                {
                    std::cout << vm["l"].as< std::vector<std::string> >()[i]
                    << ".\n";
                }
            }
            else
            {
                for (size_t i = 0;
                    i < vm["listeners"].as<std::vector<std::string>>().size(); ++i)
                {
                    std::cout
                    << vm["listeners"].as< std::vector<std::string> >()[i]
                    << ".\n";
                }
            }
        }

        if (vm.count("perft"))
        {
            std::cout << "perft path is "
                << vm["perft"].as<std::string>() << ".\n";
        }
    }
} // namespace option_parser

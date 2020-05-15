#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/program_options.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <iostream>

#include "perft-parser.hh"
#include "pgn-parser.hh"
#include "option-parser.hh"
#include "listener-manager.hh"

namespace option_parser
{
    namespace po = boost::program_options;

    Options parse_options(int argc, char** argv)
    {
        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "show usage")
            ("pgn", po::value<std::string>(), "path to the PGN game file")
            ("listeners,l", po::value<std::vector<std::string>>()->multitoken(),
             "list of paths to listener plugins")
            ("perft", po::value<std::string>(), "path to a perft game file")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help") || vm.count("h"))
        {
            std::cout << desc << "\n";
            //run help
        }

        if (vm.count("l") || vm.count("listeners"))
        {
            std::vector<std::string> listeners_paths;
            if (vm.count("l"))
            {
                listeners_paths = vm["l"].as<std::vector<std::string>>();
            }
            else
            {
                listeners_paths = vm["listeners"].as<std::vector<std::string>>();
            }

            //run listeners
            listener::listener_manager =
                listener::ListenerManager(listeners_paths);
        }

        Options options;

        if (vm.count("pgn"))
        {
            options.pgn_vect_ = pgn_parser::parse_pgn(
                    vm["pgn"].as<std::string>());
            options.pgn_ = true;
        }

        if (vm.count("perft"))
        {
            options.perft_obj_ = perft_parser::parse_perft(
                                    vm["perft"].as<std::string>());
            options.perft_ = true;
        }

        return options;
    }
} // namespace option_parser

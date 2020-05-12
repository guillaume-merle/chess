#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/program_options.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <iostream>

#include "listener-manager.hh"
#include "perft-parser.hh"
#include "pgn-parser.hh"
#include "option-parser.hh"

namespace option_parser
{
    /*board::Bitboard perft(int depth)
    {
        if (depth == 0)
            return 1;

        std::vector<board::Move> moves = board::Chessboard::generate_legal_moves();
        size_t n_moves = moves.size();
        board::Bitboard nodes = 0;
        
        for (size_t i = 0; i < n_moves; ++i)
        {
            board::Chessboard::do_move(moves.at(i));
            if (!board::Chessboard::is_check())
                nodes += perft(depth - 1);
            board::Chessboard::undo_move(moves.at(i));
        }
        return nodes;
    }*/


    namespace po = boost::program_options;

    void parse_options(int argc, char** argv)
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
            listener::ListenerManager listenerManager = listener::ListenerManager(listeners_paths);
            listenerManager.close_listeners();
        }

        if (vm.count("pgn"))
        {
            std::vector<board::PgnMove> pgn_vect = pgn_parser::parse_pgn(
                    vm["pgn"].as<std::string>());
            //run pgn
        }

        if (vm.count("perft"))
        {
            board::PerftObject perft_obj = perft_parser::parse_perft(
                    vm["perft"].as<std::string>());
            //run perft
        }

        //run ai
    }
} // namespace option_parser

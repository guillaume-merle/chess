#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/program_options.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <iostream>

#include "option-parser.hh"

namespace option_parser
{
    namespace po = boost::program_options;

    void parse_options(int argc, char** argv)
    {
        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<int>(), "set compression level")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
        }

        if (vm.count("compression")) {
            std::cout << "Compression level was set to "
                << vm["compression"].as<int>() << ".\n";
        } else {
            std::cout << "Compression level was not set.\n";
        }
    }
} // namespace option_parser

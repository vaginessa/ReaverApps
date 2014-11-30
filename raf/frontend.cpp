#include <iostream>

#include "frontend.h"

namespace
{
    const char * version_string = "Reaver Project Archive Format utility, v0.0.1\nCopyright © 2014 Reaver Project Team\n";
}

frontend::frontend(int argc, char** argv)
{
    boost::program_options::options_description general("General options");
    general.add_options()
        ("help,h", "print this message")
        ("version,v", "print version information");

    boost::program_options::options_description config("Configuration");
    config.add_options()
        ("output,o", boost::program_options::value<std::string>(), "specify output file")
        ("recursive,r", "let the create action be recursive")
        ("create,c", "create the output from inputs")
        ("unpack,u", "unpack the inputs into the output");

    boost::program_options::options_description hidden("Hidden");
    hidden.add_options()
        ("input", boost::program_options::value<std::vector<std::string>>()->composing(), "specify input file");

    boost::program_options::positional_options_description pod;
    pod.add("input", -1);

    boost::program_options::options_description options;
    options.add(general).add(config).add(hidden);

    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options).positional(pod)
        .style(boost::program_options::command_line_style::allow_short
            | boost::program_options::command_line_style::allow_long
            | boost::program_options::command_line_style::allow_sticky
            | boost::program_options::command_line_style::allow_dash_for_short
            | boost::program_options::command_line_style::long_allow_next
            | boost::program_options::command_line_style::short_allow_next
            | boost::program_options::command_line_style::allow_long_disguise).run(), _variables);

    if (_variables.count("help"))
    {
        std::cout << version_string << '\n';

        std::cout << "Usage:\n";
        std::cout << "  raf [options] inputs [options]\n\n";

        std::cout << general << std::endl << config << std::endl;

        std::exit(0);
    }

    if (_variables.count("version"))
    {
        std::cout << version_string;
        std::cout << "Distributed under modified zlib license.\n\n";

        std::cout << "RAF, or Reaver Archive Format utility, is part of the Reaver Project - http://reaver-project.org/.\n";

        std::exit(0);
    }

    if (_variables.count("output"))
    {
        _output = _variables["output"].as<std::string>();
    }

    if (_variables.count("input"))
    {
        _inputs = _variables["input"].as<std::vector<std::string>>();
    }

    if (_variables.count("recursive"))
    {
        _recursive = true;
    }

    if (_variables.count("create"))
    {
        _create = true;
    }

    if (_variables.count("unpack"))
    {
        _unpack = true;
    }
}

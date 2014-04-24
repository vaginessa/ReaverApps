#pragma once

#include <string>
#include <vector>

#include <boost/program_options.hpp>

class frontend
{
public:
    frontend(int argc, char ** argv);

    bool create() const
    {
        return _create;
    }

    bool unpack() const
    {
        return _unpack;
    }

    bool recursive() const
    {
        return _recursive;
    }

    const std::string & output() const
    {
        return _output;
    }

    const std::vector<std::string> & inputs() const
    {
        return _inputs;
    }

private:
    bool _create = false;
    bool _unpack = false;
    bool _recursive = false;

    std::string _output;
    std::vector<std::string> _inputs;

    boost::program_options::variables_map _variables;
};

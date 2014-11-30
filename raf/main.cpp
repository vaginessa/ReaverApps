#include <boost/program_options.hpp>

#include <reaver/format/archive.h>
#include <reaver/logger.h>

#include "frontend.h"

int main(int argc, char ** argv)
try
{
    frontend front{ argc, argv };

    if (front.create())
    {
        auto archive = reaver::format::archive::create(reaver::format::archive::format::raf, front.inputs(),
            front.recursive());

        if (!archive)
        {
            throw reaver::exception(reaver::logger::error) << "unable to create a RAF archive from given inputs.";
        }

        archive->save(front.output());
    }

    else if (front.unpack())
    {
        for (const auto & input : front.inputs())
        {
            auto archive = reaver::format::archive::read(input);
            archive->unpack(front.output());
        }
    }

    else
    {
        throw reaver::exception(reaver::logger::error) << "you must specify at least one action.";
    }
}

catch (reaver::exception & e)
{
    e.print(reaver::logger::default_logger());

    if (e.level() == reaver::logger::crash)
    {
        return 2;
    }

    return 1;
}

catch (std::exception & e)
{
    reaver::logger::dlog(reaver::logger::crash) << e.what();

    return 2;
}


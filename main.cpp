//! main.cpp

#include <tclap/CmdLine.h>
using namespace TCLAP;


#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include <i_pipe.h>
#include <listing.hpp>
#include <reg_pipe.h>
using namespace gipp;


int main(int argc, char** argv)
{
    CmdLine cmd("gtools set of 3D/Volume imaging utilities", ' ', "0.1");

    vector<string> allowed_selection;

    allowed_selection.emplace_back("list");

    for (auto& x: gipp::register_base::pipes)
    {
        allowed_selection.emplace_back(x.first);
    }

    ValuesConstraint<string> allowed_selection_vals( allowed_selection );

    UnlabeledValueArg<string> selection_arg("pipe","Selects a specific pipe or 'list' for full listing of available pipelines.",true,"list",&allowed_selection_vals);
    cmd.add( selection_arg );

    UnlabeledMultiArg<string> rest_args("rest","more args here...",false,"string");
    cmd.add( rest_args ); //multi args must be added last


    try
    {
        // throws
        cmd.parse( argc, argv );

        auto& selection = selection_arg.getValue();

        cout << selection << endl;

        if(selection == "list")
        {
            for (auto& x: gipp::register_base::pipes)
                std::cout << x.first << "@" << x.second.get() << std::endl;
        }

        (*gipp::register_base::pipes[selection])(--argc,++argv);

    }
    catch (ArgException& ex)
    {
        cerr << "Parse error : " << ex.error() << " for arg " << ex.argId() << endl;
    }

    return 1;

}

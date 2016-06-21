#include "threshold.h"

#include <tclap/CmdLine.h>

#include <generic_pipe.hpp>

#include <iostream>
#include <vector>

using namespace gipp;
using namespace itk;
using namespace std;
using namespace TCLAP;

namespace threshold
{
    template<typename ImageType>
    bool threshold_pipe_args<ImageType>::parse(int argc, char** argv)
    {

        CmdLine cmd("Threshold description...", ' ', "0.1");

        ValueArg<string> input_file_arg("i","input","Input file or cin",true,"ifile","string");
        cmd.add( input_file_arg );

        ValueArg<string> output_file_arg("o","output","Output file or cout",true,"ofile","string");
        cmd.add( output_file_arg );

        SwitchArg mode_below_arg("b","below","Threshold below given value", false);
        cmd.add( mode_below_arg );

        SwitchArg mode_above_arg("a","above","Threshold above given value", false);
        cmd.add( mode_above_arg );

        UnlabeledMultiArg<unsigned int> threshold_arg("threshold","Specify threhold value(s) [lower upper outside]",true,"unsigned int");
        cmd.add( threshold_arg ); //multi args must be added last

        // throws
        cmd.parse( argc, argv );

        if( threshold_arg.isSet() )
        {
            input_file = input_file_arg.getValue();
            output_file = output_file_arg.getValue();

            if( mode_below_arg.isSet() )
            {
                mode = 1;
            }

            if( mode_above_arg.isSet() )
            {
                mode = 2;
            }

            auto& vec_args = threshold_arg.getValue();

            switch (vec_args.size())
            {
                case 3: t3 = vec_args.at(2);
                case 2: t2 = vec_args.at(1);
                case 1: t3 = t1 = vec_args.at(0);
                default: break;
            }

            return true;
        }

        return false;
    }

    int pipe::operator()(int argc, char** argv)
    {

        typedef Image<float,3> ImageType;

        gpipe<ImageType,
        ScopedPointer< ImageFileReader<ImageType> >,
        ScopedPointer< ThresholdImageFilter< ImageType > >,
        ScopedPointer< ImageFileWriter<ImageType> >
        > pipe;

        threshold_pipe_args<ImageType> args;

        try
        {
            if( args.parse(argc,argv) )
            {
                pipe.Update(args);
            }

        }
        catch (ArgException& ex)
        {
            cerr << "Parse error : " << ex.error() << " for arg " << ex.argId() << endl;
        }
        catch( ExceptionObject& ex )
        {
            cerr << "ITK Exception thrown :" << endl;
            cerr << ex << endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;

    }

}//namespace

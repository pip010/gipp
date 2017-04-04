#include "testpipe.h"

#include <tclap/CmdLine.h>

#include <generic_pipe.hpp>

#include <iostream>

using namespace gipp;
using namespace itk;
using namespace std;
using namespace TCLAP;


template<typename ImageType>
bool test_pipe_args<ImageType>::parse(int argc, char** argv)
{

    CmdLine cmd("Dilate description...", ' ', "0.1");

    ValueArg<string> input_file_arg("i","input","Input file or cin",true,"ifile","string");
    cmd.add( input_file_arg );

    ValueArg<string> output_file_arg("o","output","Output file or cout",true,"ofile","string");
    cmd.add( output_file_arg );

    //UnlabeledValueArg<unsigned int> radius_arg("radius","The radius range of the dilate filter kernel",true,0,"unsigned char");
    //cmd.add( radius_arg ); //multi args must be added last

    // throws
    cmd.parse( argc, argv );

    if( input_file_arg.isSet() )
    {
        input_file = input_file_arg.getValue();
        output_file = output_file_arg.getValue();

        //radius = radius_arg.getValue();

        return true;
    }

    return false;
}

int main(int argc, char** argv)
{

    typedef Image<unsigned char,3> ImageType;

    gpipe<ImageType,
    ScopedPointer< ImageFileReader<ImageType> >,
    ScopedPointer< Euler3DTransform<double> >,
    ScopedPointer< ImageFileWriter<ImageType> >
    > pipe;

    test_pipe_args<ImageType> args;

    try
    {
        if( args.parse(argc,argv) )
        {
            pipe.Update(args);
        }
    }
    catch ( ArgException& ex )
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

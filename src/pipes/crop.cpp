#include "crop.h"

#include <tclap/CmdLine.h>

#include <generic_pipe.hpp>

#include <iostream>

using namespace gipp;
using namespace itk;
using namespace std;
using namespace TCLAP;

template<typename ImageType>
bool crop_pipe_args<ImageType>::parse(int argc, char** argv)
{

    CmdLine cmd("Crop description...", ' ', "0.1");

    ValueArg<string> input_file_arg("i","input","Input file or cin",true,"ifile","string");
    cmd.add( input_file_arg );

    ValueArg<string> output_file_arg("o","output","Output file or cout",true,"ofile","string");
    cmd.add( output_file_arg );

    //MultiArg<int> region("r","region","Region of interest ROI to extract",true,"int");

    UnlabeledMultiArg<int> region_arg("region","specify region to include (start size) for each dimension",true,"int");
    cmd.add( region_arg ); //multi args must be added last

    // throws
    cmd.parse( argc, argv );

    auto& roi_args = region_arg.getValue();

    if( region_arg.isSet() )
    {
        input_file = input_file_arg.getValue();
        output_file = output_file_arg.getValue();

        for(size_t i = 0; i < roi_args.size(); ++i)
        {
            roi_region_range[i] = roi_args[i];
        }

        return true;
    }

    return false;
}

int main(int argc, char** argv)
{

    typedef Image<float,3> ImageType;

    gpipe<ImageType,
    ScopedPointer< ImageFileReader<ImageType> >,
    ScopedPointer< RegionOfInterestImageFilter< ImageType, ImageType > >,
    ScopedPointer< ImageFileWriter<ImageType> >
    > pipe;

    crop_pipe_args<ImageType> args;

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

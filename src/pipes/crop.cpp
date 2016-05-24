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

    CmdLine cmd("Crop description...", ' ', "0.9");

    ValueArg<string> input_file_arg("i"," input","Input file or cin",true,"ifile","string");
    cmd.add( input_file_arg );

    ValueArg<string> output_file_arg("o"," output","Output file or cout",true,"ofile","string");
    cmd.add( output_file_arg );

    //SwitchArg reverseSwitch("r","reverse","Print name backwards", false);
    //cmd.add( reverseSwitch );

    MultiArg<int> region("r"," region","Region of interest ROI to extract",true,"int");

    cmd.parse( argc, argv );

    if( region.isSet() )
    {
        input_file = input_file_arg.getValue();
        output_file = output_file_arg.getValue();

        x1 = region.getValue().at(0);
        x2 = region.getValue().at(1);

        return true;
    }

    //bool reverseName = reverseSwitch.getValue();
    return false;
}

int main(int argc, char** argv)
{

    typedef itk::Image<float,3> ImageType;

    gpipe<ImageType,
    ScopedPointer< ImageFileReader<ImageType> >,
    ScopedPointer< RegionOfInterestImageFilter< ImageType, ImageType > >,
    ScopedPointer< ImageFileWriter<ImageType> >
    > crop_pipe;

    crop_pipe_args<ImageType> crop_args;

    crop_args.parse(argc,argv);

    try
    {
        if( crop_args.parse(argc,argv) )
        {
            crop_pipe.Update(crop_args);
        }

    }
    catch (ArgException& ex)
    {
        cerr << "Parse error : " << ex.error() << " for arg " << ex.argId() << endl;
    }
    catch( itk::ExceptionObject& ex )
    {
        cerr << "ITK Exception thrown :" << endl;
        cerr << ex << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

//! testpipe_main.cpp


#include <string>
#include <vector>
#include <iostream>
using namespace std;


#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkBinomialBlurImageFilter.h>
using namespace itk;

#include <generic_pipe.hpp>
using namespace gipp;


template<typename ImageType>
struct pipe_args
{
    void set (node_base& n)
    {
        std::cout << "base_args::set_args\n";
    }

    void get (node_base& n)
    {
        std::cout << "base_args::get_args\n";
    }

    void set (node<ImageFileReader<ImageType>>& arg)
    {
        std::cout << "args::set(ImageFileReader)\n";
        arg.GetPointer()->SetFileName("test_in.nii");
    }

    void set (node<ImageFileWriter<ImageType>>& arg)
    {
        std::cout << "args::set(ImageFileWriter)\n";
        arg.GetPointer()->SetFileName("test_out.nii");
    }


    void set(node< BinomialBlurImageFilter<ImageType,ImageType> >& arg)
    {
        std::cout << "args::set(BinomialBlurImageFilter)\n";
        arg.GetPointer()->SetRepetitions(5);
    }

    void set(node<BinomialBlurImageFilter<ImageType,ImageType>,1>& arg)
    {
        std::cout << "args::set(BinomialBlurImageFilter1)\n";
        arg.GetPointer()->SetRepetitions(15);
    }
};

int main(int argc, char** argv)
{
    typedef Image<unsigned char,3> ImageType;


    gpipe2<ImageType,
    node< ImageFileReader<ImageType> >,
    node< BinomialBlurImageFilter<ImageType,ImageType> >,
    node< BinomialBlurImageFilter<ImageType,ImageType>, 1>,
    node< ImageFileWriter<ImageType> >
    > pipe2;

    pipe_args<ImageType> args;

    try
    {
        pipe2.Update(args);

    }
    catch( ExceptionObject& ex )
    {
        cerr << "ITK Exception thrown :" << endl;
        cerr << ex << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

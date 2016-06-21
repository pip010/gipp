#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkImage.h>

#include <macros.hpp>

#include <i_pipe.h>

#include <reg_pipe.h>


namespace ops
{

    struct pipe : public gipp::i_pipe
    {
        int operator()(int argc, char** argv) override;
    };

    template<typename ImageType>
    struct args
    {
        BASE_ARGS(ImageType)

        //https://itk.org/Wiki/ITK/Examples/SimpleOperations/SetPixels
        // https://itk.org/Wiki/ITK/Examples/Developer/ImageFilterMultipleInputs

        //bool parse(int argc, char** argv);

    };

    static gipp::register_pipe<pipe> p("ops");

}

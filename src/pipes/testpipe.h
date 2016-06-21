#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkEuler3DTransform.h>

#include <macros.hpp>

template<typename ImageType>
struct pipe_args
{
    BASE_ARGS(ImageType)
    BASE_IO(ImageType)

    void set (size_t I, itk::Euler3DTransform< double >* arg)
    {
        itk::Euler3DTransform< double > t;
    }

    bool parse(int argc, char** argv);

};

#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkThresholdImageFilter.h>

#include <macros.hpp>

template<typename ImageType>
struct threshold_pipe_args
{
    BASE_ARGS(ImageType)
    BASE_IO(ImageType)

    unsigned int t1, t2, t3, mode;

    threshold_pipe_args():
        t1(0),
        t2(0),
        t3(0),
        mode(3)
    {
    }

    void set (size_t I, itk::ThresholdImageFilter< ImageType >* arg)
    {
        switch (mode)
        {
            case 1: arg->ThresholdBelow(t1); break;
            case 2: arg->ThresholdAbove(t1); break;
            case 3: arg->ThresholdOutside(t1,t2); break;
            default: break;
        }

        arg->SetOutsideValue(t3);
    }

    bool parse(int argc, char** argv);

};

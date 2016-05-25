#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkThresholdImageFilter.h>

#include <base_args.hpp>

template<typename ImageType>
struct threshold_pipe_args
{
    BASE_ARGS

    //typename ImageType::SizeType inSize;

    std::string input_file;
    std::string output_file;

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
        // typename ImageType::IndexType start;
        // start[0] = inSize[0]/x1;
        // start[1] = inSize[1]/x1;
        // start[2] = inSize[2]/x1;
        //
        // typename ImageType::SizeType size;
        // size[0] = inSize[0]/x2;
        // size[1] = inSize[1]/x2;
        // size[2] = inSize[2]/x2;
        //
        // typename ImageType::RegionType desiredRegion;
        // desiredRegion.SetSize(size);
        // desiredRegion.SetIndex(start);
        //


        switch (mode)
        {
            case 1: arg->ThresholdBelow(t1); break;
            case 2: arg->ThresholdAbove(t1); break;
            case 3: arg->ThresholdOutside(t1,t2); break;

            default: break;
        }

        arg->SetOutsideValue(t3);

    }

    void set (size_t I, itk::ImageFileReader<ImageType>* arg)
    {
        arg->SetFileName(input_file.c_str());
    }

    // void get (size_t I,itk::ImageFileReader<ImageType>* arg)
    // {
    //     inSize = arg->GetOutput()->GetLargestPossibleRegion().GetSize();
    // }

    void set (size_t I, itk::ImageFileWriter<ImageType>* arg)
    {
        arg->SetFileName(output_file.c_str());
    }

    bool parse(int argc, char** argv);

};

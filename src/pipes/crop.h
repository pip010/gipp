#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkRegionOfInterestImageFilter.h>

#include <macros.hpp>

template<typename ImageType>
struct crop_pipe_args
{
    BASE_ARGS(ImageType)
    BASE_IO(ImageType)

    SizeType inSize;

    int x1, x2;


    void set (size_t I,
    itk::RegionOfInterestImageFilter< ImageType, ImageType >* arg)
    {
        typename ImageType::IndexType start;
        start[0] = inSize[0]/x1;
        start[1] = inSize[1]/x1;
        start[2] = inSize[2]/x1;

        typename ImageType::SizeType size;
        size[0] = inSize[0]/x2;
        size[1] = inSize[1]/x2;
        size[2] = inSize[2]/x2;

        typename ImageType::RegionType desiredRegion;
        desiredRegion.SetSize(size);
        desiredRegion.SetIndex(start);

        arg->SetRegionOfInterest(desiredRegion);
    }

    void get (size_t I,itk::ImageFileReader<ImageType>* arg)
    {
        inSize = arg->GetOutput()->GetLargestPossibleRegion().GetSize();
    }

    bool parse(int argc, char** argv);

};

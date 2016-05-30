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

    int roi_region_range[6] = {0,0,0,0,0,0};


    void set (size_t I,
    itk::RegionOfInterestImageFilter< ImageType, ImageType >* arg)
    {
        typename ImageType::IndexType start;
        start[0] = roi_region_range[0];
        start[1] = roi_region_range[2];
        start[2] = roi_region_range[4];

        typename ImageType::SizeType size;
        size[0] = roi_region_range[1] == 0 ? inSize[0] : roi_region_range[1] ;
        size[1] = roi_region_range[3] == 0 ? inSize[1] : roi_region_range[3] ;
        size[2] = roi_region_range[5] == 0 ? inSize[2] : roi_region_range[5] ;

        typename ImageType::RegionType desiredRegion;
        desiredRegion.SetSize(size);
        desiredRegion.SetIndex(start);

        //DEBUG
        //std::cout << desiredRegion;

        arg->SetRegionOfInterest(desiredRegion);
    }

    void get (size_t I,itk::ImageFileReader<ImageType>* arg)
    {
        inSize = arg->GetOutput()->GetLargestPossibleRegion().GetSize();
    }

    bool parse(int argc, char** argv);

};

#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkBinaryDilateImageFilter.h>
#include <itkBinaryBallStructuringElement.h>

#include <macros.hpp>

template<typename ImageType>
struct dilate_pipe_args
{
    BASE_ARGS(ImageType)
    BASE_IO(ImageType)

    SizeType radius;

    typedef itk::BinaryBallStructuringElement<typename ImageType::PixelType,3> StructuringElementType;

    void set (size_t I, itk::BinaryDilateImageFilter< ImageType, ImageType, StructuringElementType>* arg)
    {

        StructuringElementType structuringElement;
        structuringElement.SetRadius(radius);
        structuringElement.CreateStructuringElement();

        arg->SetKernel(structuringElement);
    }

    bool parse(int argc, char** argv);

};

#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkBinaryDilateImageFilter.h>
#include <itkBinaryBallStructuringElement.h>

#include <macros.hpp>

//https://itk.org/Doxygen/html/classitk_1_1BinaryDilateImageFilter.html

template<typename ImageType>
struct dilate_pipe_args
{
    BASE_ARGS(ImageType)
    BASE_IO(ImageType)

    SizeValueType radius;
    PixelType dilate;

    typedef itk::BinaryBallStructuringElement<PixelType,3> StructuringElementType;

    void set (size_t I, itk::BinaryDilateImageFilter< ImageType, ImageType, StructuringElementType>* arg)
    {

        StructuringElementType structuringElement;
        structuringElement.SetRadius(radius);
        structuringElement.CreateStructuringElement();

        arg->SetKernel(structuringElement);

        arg->SetDilateValue(dilate);
    }

    bool parse(int argc, char** argv);

};

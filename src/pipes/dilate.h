#pragma once

#include <string>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkBinaryDilateImageFilter.h>
#include <itkBinaryBallStructuringElement.h>

#include <base_args.hpp>

template<typename ImageType>
struct dilate_pipe_args
{
    BASE_ARGS

    //typename ImageType::SizeType radius;]
    unsigned int radius;

    std::string input_file;
    std::string output_file;

    typedef itk::BinaryBallStructuringElement<typename ImageType::PixelType,3> StructuringElementType;

    void set (size_t I, itk::BinaryDilateImageFilter< ImageType, ImageType, StructuringElementType>* arg)
    {

        StructuringElementType structuringElement;
        structuringElement.SetRadius(radius);
        structuringElement.CreateStructuringElement();

        arg->SetKernel(structuringElement);
    }

    void set (size_t I, itk::ImageFileReader<ImageType>* arg)
    {
        arg->SetFileName(input_file.c_str());
    }

    void set (size_t I, itk::ImageFileWriter<ImageType>* arg)
    {
        arg->SetFileName(output_file.c_str());
    }

    bool parse(int argc, char** argv);

};

#pragma once

#include <itkProcessObject.h>

#define BASE_ARGS(IT) \
void set (size_t I, itk::ProcessObject*){} \
void get (size_t I, const itk::ProcessObject*){} \
typedef typename IT::SizeType SizeType; \
typedef typename IT::SizeType::SizeValueType SizeValueType; \
typedef typename IT::PixelType PixelType; \
typedef typename IT::RegionType RegionType; \
typedef typename IT::IndexType IndexType;

#define BASE_ARGS_WITH_LOG \
void set (size_t I, itk::ProcessObject*){std::cout << "base_args::set_args\n"} \
void get (size_t I, const itk::ProcessObject*){std::cout << "base_args::get_args\n"}

#define BASE_IO(IT) \
std::string input_file;\
std::string output_file;\
void set (size_t I, itk::ImageFileReader<IT>* arg){ arg->SetFileName(input_file.c_str()); }\
void set (size_t I, itk::ImageFileWriter<IT>* arg){ arg->SetFileName(output_file.c_str()); }

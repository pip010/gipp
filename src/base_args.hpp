#pragma once

#include <itkProcessObject.h>

#define BASE_ARGS \
void set (size_t I, itk::ProcessObject*){} \
void get (size_t I, const itk::ProcessObject*){}

#define BASE_ARGS_AND_LOG \
void set (size_t I, itk::ProcessObject*){std::cout << "base_args::set_args\n"} \
void get (size_t I, const itk::ProcessObject*){std::cout << "base_args::get_args\n"}

#pragma once

#include <itkSmartPointer.h>
#include <itkProcessObject.h>

namespace gipp
{
    //TODO interface like the rest of itk smart-pointers
    template< typename T>
    struct ScopedPointer
    {
        static_assert(std::is_base_of<itk::ProcessObject, T>::value, "must be inhereting from itk::ProcessObject");

        ScopedPointer()
        {
            sp = T::New();
        }

        void Update()
        {
            sp->Update();
        }

        void PrintSelf()
        {
            sp->Print(std::cout,itk::Indent(1));
        }

        T* 	GetPointer() const
        {
            return sp.GetPointer();
        }

    private:
        itk::SmartPointer<T> sp;
    };
}

#pragma once

#include <i_pipe.h>

#include <unordered_map>
#include <memory>
#include <iostream>

#ifndef _WIN32
    namespace std
    {
        template<typename T, typename... Args>
        std::unique_ptr<T> make_unique(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
    }
#endif

namespace gipp
{
    struct register_base
    {
        typedef std::unordered_map< std::string, std::unique_ptr<gipp::i_pipe> > ContainerType;
        static ContainerType pipes;
    };

    template<typename T>
    struct register_pipe : public register_base
    {

        register_pipe(std::string n)
        {
            pipes.reserve(1);// TODO BUG:https://gcc.gnu.org/bugzilla/show_bug.cgi?id=61143
            //std::cout << "C()" << std::endl;
            pipes.insert( std::make_pair(n, std::make_unique<T>()) );
            //std::cout << pipes.size() << std::endl;

        }

        ~register_pipe()
        {
            //std::cout << "~D()" << std::endl;
        }
    };

}

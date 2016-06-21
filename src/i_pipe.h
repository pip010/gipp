#pragma once

namespace gipp
{
    class i_pipe
    {
    public:
        virtual int operator()(int argc, char** argv) = 0;
    };

}//namespace

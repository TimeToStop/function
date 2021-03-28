#include <iostream>

#include "src/function/functionbuilder.h"
#include "src/exceptions/unexpectedsymbolexception.h"

int main(int argc, char* argv[])
{
    try
    {   
        if (argc != 2)
        {
            std::cerr << "Usage: { PROGRAM_NAME } { FUNCTION_SRC }" << std::endl;
            exit(-1);
        }

        const char* src = argv[1];
        Function f;
        FunctionBuilder b;
        b.build(&f, src);

        std::cout << "f(x) = " << src << std::endl;

        for (double x = -10.0; x < 10.01; x += 0.1)
        {
            std::cout << "f(" << x << ") = " << f.calculate(x) << std::endl;
        }

        return 0;
    }
    catch (Exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}


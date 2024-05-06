
#include <iostream>
#include <iomanip>
#include "Expression.h";

using namespace Nequeo::Math;

int main(int argc, char* argv[])
{
    Expression exp;

    // if arguments exist.
    if (argc > 1) 
    {    
        double result_compute = 0.0;
        bool isvalid = exp.Compute(argv[1], &result_compute);
        std::cout << std::setprecision(30);
        std::cout << result_compute;
    }
    else
    {
        std::cout << "Add arguments";
    }
}


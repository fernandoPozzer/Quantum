
#ifndef ___QUBIT_H___
#define ___QUBIT_H___

#include <string>
#include <sstream>

#include "Complex.h"

class Qubit
{
public:
    Complex state[2];

    Qubit()
    {
        state[0] = Complex::Zero();
        state[1] = Complex::Zero();
    }

    Qubit(Complex zero, Complex one)
    {
        state[0] = zero;
        state[1] = one;
    }

    float GetProbZero()
    {
        return state[0].GetNormSquared();
    }

    float GetProbOne()
    {
        return state[1].GetNormSquared();
    }

    std::string ToString()
    {
        std::stringstream s;
        s << state[0].ToString() << " |0> + ";
        s << state[1].ToString() << " |1>";

        return s.str();
    }
};

#endif

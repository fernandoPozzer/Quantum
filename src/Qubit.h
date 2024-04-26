
#ifndef ___QUBIT_H___
#define ___QUBIT_H___

#include <string>
#include <sstream>

using namespace std;

#include "Complex.h"

class Qubit
{
public:
    Complex state[2];

    Qubit(Complex zero, Complex one)
    {
        state[0] = zero;
        state[1] = one;
    }

    Complex GetZero()
    {
        return state[0];
    }

    Complex GetOne()
    {
        return state[1];
    }

    static Qubit Make(Complex zero, Complex one)
    {
        Qubit aux(zero, one);
        return aux;
    }

    string ToString()
    {
        stringstream s;
        s << state[0].ToString() << "| 0> + ";
        s << state[1].ToString() << "| 1>";

        return s.str();
    }
};

#endif

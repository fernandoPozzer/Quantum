
#ifndef ___OPERATION_H___
#define ___OPERATION_H___

#include "Complex.h"
#include "Qubit.h"

class Operation
{
public:

    Complex matrix[2][2];

    Qubit operator *(Qubit q)
    {
        Complex aux[2];

        for(int i = 0; i < 2; i++)
        {
            aux[i] = Complex::Make(0, 0);

            for(int j = 0; j < 2; j++)
            {
                aux[i] += matrix[i][j] * q.state[j];
            }
        }

        return Qubit::Make(aux[0], aux[1]);
    }

    Operation(Complex matrix[2][2])
    {
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                this->matrix[i][j] = matrix[i][j];
            }
        }
    }

    static Operation Not()
    {
        Complex m[2][2] = {{Complex::Zero(), Complex::One()},
                       {Complex::One(), Complex::Zero()}};

        Operation aux(m);
        return aux;
    }

    static Operation Hadamard()
    {
        // FAZER
    }
};

#endif

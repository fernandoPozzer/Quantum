
#ifndef ___OPERATION_H___
#define ___OPERATION_H___

#include <cassert>

#include "Complex.h"
#include "Qubit.h"

class Operation
{
private:

    Complex* ApplyOperation(Complex* states, int numberOfStates)
    {
        Complex* aux = new Complex[numberOfStates];

        for(int i = 0; i < numberOfStates; i++)
        {
            for(int j = 0; j < numberOfStates; j++)
            {
                aux[i] += matrix[i][j] * states[j];
            }
        }

        return aux;
    }
public:

    Complex **matrix;
    int dim;

    Qubit operator *(Qubit q)
    {
        assert(dim == 2);

        Complex *aux = ApplyOperation(q.state, 2);
        return Qubit(aux[0], aux[1]);
    }

    Operation(Complex m00, Complex m01, Complex m10, Complex m11)
    {
        dim = 2;

        matrix = new Complex*[dim];

        for(int i = 0; i < dim; i++)
        {
            matrix[i] = new Complex[dim];
        }

        matrix[0][0] = m00;
        matrix[0][1] = m01;
        matrix[1][0] = m10;
        matrix[1][1] = m11;
    }

    static Operation Not()
    {
        return Operation(Complex::Zero(), Complex::One(),
                       Complex::One(), Complex::Zero());
    }

    static Operation Hadamard()
    {
        // FAZER
    }
};

#endif

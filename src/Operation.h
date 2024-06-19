
#ifndef ___OPERATION_H___
#define ___OPERATION_H___

#include <cassert>

#include "Complex.h"
#include "Qubit.h"
#include "QuantumSystem.h"

#include "Utils.h"

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

    Complex** matrix;
    int dim;

    Operation()
    {
        matrix = Identity().matrix;
        dim = 2;
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

    Qubit operator *(Qubit q)
    {
        Assert(dim == 2, "Operacao com qubit demanda um operador de dimensao 2");

        Complex *aux = ApplyOperation(q.state, 2);
        return Qubit(aux[0], aux[1]);
    }

    QuantumSystem operator *(QuantumSystem qs)
    {
        Assert(dim == qs.numStates, "Operacao com sistema demanda um operador com a mesma dimensao do sistema");

        qs.states = ApplyOperation(qs.states, qs.numStates);
        return qs;
    }

    void AddOperation(Operation op)
    {
        matrix = Utils::MatrixTensorProduct(matrix, dim, op.matrix, op.dim);
        dim *= op.dim;
    }

    static Operation Not()
    {
        return Operation(Complex::Zero(), Complex::One(),
                       Complex::One(), Complex::Zero());
    }

    static Operation Identity()
    {
        return Operation(Complex::One(), Complex::Zero(),
                       Complex::Zero(), Complex::One());
    }

    static Operation Hadamard()
    {
        /// 1 / sqrt(2)
        Complex aux(0.707, 0);

        return Operation(aux, aux, aux, aux * (-1));
    }
};

#endif

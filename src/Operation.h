
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

    Operation(Complex m00, Complex m01, Complex m02, Complex m03,
              Complex m10, Complex m11, Complex m12, Complex m13,
              Complex m20, Complex m21, Complex m22, Complex m23,
              Complex m30, Complex m31, Complex m32, Complex m33)
    {
        dim = 4;
        matrix = new Complex*[dim];

        for(int i = 0; i < dim; i++)
        {
            matrix[i] = new Complex[dim];
        }

        matrix[0][0] = m00;
        matrix[0][1] = m01;
        matrix[0][2] = m02;
        matrix[0][3] = m03;

        matrix[1][0] = m10;
        matrix[1][1] = m11;
        matrix[1][2] = m12;
        matrix[1][3] = m13;

        matrix[2][0] = m20;
        matrix[2][1] = m21;
        matrix[2][2] = m22;
        matrix[2][3] = m23;

        matrix[3][0] = m30;
        matrix[3][1] = m31;
        matrix[3][2] = m32;
        matrix[3][3] = m33;
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

    static Operation X()
    {
        return Not();
    }

    static Operation Z()
    {
        return Operation(Complex::One(), Complex::Zero(),
                         Complex::Zero(), Complex::One() * (-1));
    }

    static Operation ControlledNot()
    {
        Complex one = Complex::One();
        Complex zero = Complex::Zero();

        return Operation(one, zero, zero, zero,
                         zero, one, zero, zero,
                         zero, zero, zero, one,
                         zero, zero, one, zero);
    }
};

#endif

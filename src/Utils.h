
#ifndef ___UTILS_H___
#define ___UTILS_H___

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

class Utils
{
public:

    static Complex* TensorProduct(Complex* a, int sizeA, Complex* b, int sizeB)
    {
        Complex* aux = new Complex[sizeA * sizeB];

        for(int i = 0; i < sizeA; i++)
        {
            for(int j = 0; j < sizeB; j++)
            {
                aux[i * sizeB + j] = a[i] * b[j];
            }
        }

        return aux;
    }

    static Complex** MatrixTensorProduct(Complex** a, int dimA, Complex** b, int dimB)
    {
        Complex** aux = new Complex*[dimA * dimB];

        for(int i = 0; i < dimA * dimB; i++)
        {
            aux[i] = new Complex[dimA * dimB];
        }
        int column=0,row=0;
        for(int l = 0; l < dimA; l++)
        {
            column=0;
            for(int c=0;c<dimA;c++)
            {
                for(int lB=0;lB<dimB;lB++)
                {
                    for(int cB=0;cB<dimB;cB++)
                    {
                        assert(column+cB>=0 && column+cB<dimA*dimB);
                        assert(row+lB>=0 && row+lB<dimA*dimB);

                        aux[row+lB][column+cB]=a[l][c]*b[lB][cB];
                    }
                }
                column+=dimB;
            }
            row+=dimB;
        }


        return aux;
    }

    static void PrintMatrix(Complex** a, int dim)
    {
        for(int i = 0; i < dim; i++)
        {
            for(int j = 0; j < dim; j++)
            {
                std::cout << a[i][j].ToString() << " ";
            }

            std::cout << std::endl;
        }
    }

    static Complex* CopyArray(Complex* v, int sizeV)
    {
        Complex* aux = new Complex[sizeV];

        for(int i = 0; i < sizeV; i++)
        {
            aux[i] = v[i];
        }

        return aux;
    }

    /**
        Extracao de bit da esquerda para a direita
    */
    static int ExtractBit(int number, int bit, int totalBits)
    {
        int shift = totalBits - 1 - bit;

        if(shift < 0)
        {
            return 0;
        }

        return (number & (1 << shift)) != 0;
    }

    static std::string NumberToBinaryString(int number, int numberOfBits)
    {
        std::stringstream s;

        for(int i = 0; i < numberOfBits; i++)
        {
            s << ExtractBit(number, i, numberOfBits);
        }

        return s.str();
    }

    static int BinaryStringToNumber(std::string s)
    {
        int resp = 0;

        for(int i = 0; i < s.size(); i++)
        {
            if(s[s.size() - i - 1] == '1')
            {
                resp += (1 << i);
            }
        }

        return resp;
    }

    static float Truncate(float number, int numberOfDecimals)
    {
        int aux = number * pow(10, numberOfDecimals);
        return (float) aux / pow(10, numberOfDecimals);
    }
};

#endif

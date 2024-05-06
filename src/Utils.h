
#ifndef ___UTILS_H___
#define ___UTILS_H___

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

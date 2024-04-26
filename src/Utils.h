
#ifndef ___UTILS_H___
#define ___UTILS_H___

class Utils
{
public:

    static Complex *TensorProduct(Complex *a, int sizeA, Complex *b, int sizeB)
    {
        Complex *aux = new Complex[sizeA * sizeB];

        for(int i = 0; i < sizeA; i++)
        {
            for(int j = 0; j < sizeB; j++)
            {
                aux[i * sizeA + j] = a[i] * b[j];
            }
        }

        return aux;
    }
};

#endif

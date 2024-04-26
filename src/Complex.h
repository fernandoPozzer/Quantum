
#ifndef ___COMPLEX_H___
#define ___COMPLEX_H___

#include <string>
#include <sstream>

using namespace std;

class Complex
{
public:

    float real, imaginary;

    Complex(float real, float imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }

    Complex()
    {
        real = 0;
        imaginary = 0;
    }

    Complex operator * (Complex c)
    {
        float _real = real * c.real - imaginary * c.imaginary;
        float _imaginary = real * c.imaginary + imaginary * c.real;

        return Complex::Make(_real, _imaginary);
    }

    void operator += (Complex c)
    {
        real += c.real;
        imaginary += c.imaginary;
    }

    static Complex Make(float real, float imaginary)
    {
        Complex aux(real, imaginary);
        return aux;
    }

    static Complex One()
    {
        Complex aux(1, 0);
        return aux;
    }

    static Complex Zero()
    {
        Complex aux(0, 0);
        return aux;
    }

    string ToString()
    {
        stringstream s;

        if(real != 0)
        {
            s << real;
        }

        if(imaginary != 0)
        {
            if(real != 0)
            {
                s << " + ";
            }

            s << imaginary << "i";
        }

        return s.str();
    }
};

#endif

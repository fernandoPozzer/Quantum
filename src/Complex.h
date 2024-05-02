
#ifndef ___COMPLEX_H___
#define ___COMPLEX_H___

#include <string>
#include <sstream>

class Complex
{
public:

    float real, imaginary;

    Complex()
    {
        real = 0;
        imaginary = 0;
    }

    Complex(float real, float imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }

    float GetNormSquared()
    {
        return real * real + imaginary * imaginary;
    }

    Complex operator * (Complex c)
    {
        float r = real * c.real - imaginary * c.imaginary;
        float i = real * c.imaginary + imaginary * c.real;

        return Complex(r, i);
    }

    void operator += (Complex c)
    {
        real += c.real;
        imaginary += c.imaginary;
    }

    static Complex One()
    {
        return Complex(1, 0);;
    }

    static Complex Zero()
    {
        return Complex(0, 0);;
    }

    std::string ToString()
    {
        std::stringstream s;

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

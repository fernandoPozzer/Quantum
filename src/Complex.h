
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

    string ToString()
    {
        stringstream s;
        s << real << " " << imaginary << "i";

        return s.str();
    }
};

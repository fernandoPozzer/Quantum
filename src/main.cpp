#include <iostream>

#include "Complex.h"
#include "Qubit.h"
#include "Operation.h"
#include "Utils.h"
#include "QuantumSystem.h"
#include "Utils.h"

using namespace std;

int main()
{
    Qubit q(Complex(0.25, 0), Complex(0.75, 0));
    Qubit q2(Complex(0.6, 0), Complex(0.4, 0));
    Qubit q3(Complex(0.33, 0.67), Complex(0.47, 2));

    QuantumSystem s;

    s.AddQubit(q);
    s.AddQubit(q2);
    s.AddQubit(q3);

    Complex** a;
    a=new Complex*[2];
    for(int i=0;i<2;i++)
    {
        a[i]=new Complex[2];
    }
     Complex x[2][2]= {{Complex::Zero(), Complex::One()},
                       {Complex::One(), Complex::Zero()}};
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) a[i][j]=x[i][j];

    Complex** b;
    b=new Complex*[2];
    for(int i=0;i<2;i++)
    {
        b[i]=new Complex[2];
    }

    Complex Y[2][2] = {{Complex::One(), Complex::Zero()},
                       {Complex::Zero(), Complex::One()}};
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) b[i][j]=Y[i][j];

    auto aaaa = Utils::MatrixTensorProduct(a, 2, b, 2);
    Utils::PrintMatrix(aaaa, 4);
    cout << endl;
    Utils::PrintMatrix(Utils::MatrixTensorProduct(aaaa, 4, b, 2), 8);


    return 0;
}

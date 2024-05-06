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


    cout << s.ToColumnString() << endl;

    cout << s.GetProb("111") << endl;

    cout << s.ProbabilityToColumnString() << endl;

    return 0;
}

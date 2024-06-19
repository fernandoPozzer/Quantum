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

    QuantumSystem qs;
    qs.AddQubit(q);

    cout << qs.ToColumnString() << endl;

    qs.AddQuantumSystem(QuantumSystem::PhiPlus());

    cout << qs.ToColumnString() << endl;

    return 0;
}

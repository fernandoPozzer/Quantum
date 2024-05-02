#include <iostream>

#include "Complex.h"
#include "Qubit.h"
#include "Operation.h"
#include "Utils.h"

using namespace std;

int main()
{
    Qubit q(Complex(0.33, 0.67), Complex(-0.67, 0));
    cout << q.ToString() << endl << endl;
    cout << q.GetProbZero() << " " << q.GetProbOne() << endl;

    return 0;
}

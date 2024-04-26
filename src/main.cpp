#include <iostream>

#include "Complex.h"
#include "Qubit.h"
#include "Operation.h"

using namespace std;

int main()
{
    Qubit q(Complex::Make(0.5, 2), Complex::Make(0, 1));
    cout << "qubit: " << q.ToString() << endl;

    Qubit newQ = Operation::Not() * q;
    cout << "not qubit: " << newQ.ToString() << endl;

    return 0;
}

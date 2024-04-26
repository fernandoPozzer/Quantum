#include <iostream>

#include "Complex.h"
#include "Qubit.h"
#include "Operation.h"
#include "Utils.h"

using namespace std;

int main()
{
    Qubit q(Complex::Make(0.5, 2), Complex::Make(0, 1));
    cout << "qubit: " << q.ToString() << endl;

    Qubit newQ = Operation::Not() * q;
    cout << "not qubit: " << newQ.ToString() << endl;

    Complex *temp = Utils::TensorProduct(q.state, 2, newQ.state, 2);

    for(int i = 0; i < 4; i++)
    {
        cout << temp[i].ToString() << endl;
    }

    return 0;
}

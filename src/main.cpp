#include <iostream>

#include "Complex.h"
#include "Utils.h"

#include "Qubit.h"
#include "Operation.h"

#include "QuantumSystem.h"
#include "Circuit.h"

using namespace std;

void DemonstrateTeleportation(Qubit psi)
{
    cout << "PSI: " << psi.ToString() << endl;

    QuantumSystem qs;

    qs.AddQubit(psi);
    qs.AddQuantumSystem(QuantumSystem::PhiPlus());

    cout << endl << "ESTADO INICIAL: " << endl << endl;
    cout << qs.ToColumnString() << endl;

    Circuit c(qs);

    cout << "------------------------------" << endl;
    cout << "NOT CONTROLADO:" << endl;

    c.StartOperation(0, Operation::ControlledNot());
    c.FinishOperation();

    cout << "------------------------------" << endl;
    cout << "HADAMARD:" << endl;

    c.StartOperation(0, Operation::Hadamard());
    c.FinishOperation();

    cout << "------------------------------" << endl;
    cout << "MEDIDAS:" << endl << endl;

    cout << "Medida do qubit 0: " << c.Measure(0) << endl;
    cout << "Medida do qubit 1: " << c.Measure(1) << endl << endl;

    cout << "------------------------------" << endl;
    cout << "X (se qubit(0) = 1):" << endl << endl;

    c.StartConditionalOperation(2, Operation::X(), 1, 1);
    c.FinishOperation();

    cout << "------------------------------" << endl;
    cout << "Z (se qubit(1) = 1):" << endl << endl;

    c.StartConditionalOperation(2, Operation::Z(), 0, 1);
    c.FinishOperation();
}

int main()
{
    Qubit q(Complex(0.25, 0), Complex(0.75, 0));
    DemonstrateTeleportation(q);


    return 0;
}

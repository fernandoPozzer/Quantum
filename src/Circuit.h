
#ifndef ___CIRCUIT_H___
#define ___CIRCUIT_H___

#include "Operation.h"
#include "QuantumSystem.h"

#define MAX_QUBITS 10

class Circuit
{
private:

    PrintInfo(Operation currentOperation, QuantumSystem currentSystem)
    {
        std::cout << std::endl;

        Utils::PrintMatrix(currentOperation.matrix, currentOperation.dim);

        std::cout << std::endl << "SISTEMA APOS A OPERACAO:" << std::endl << std::endl;
        std::cout << currentSystem.ToColumnString() << std::endl;
    }

public:

    int numQubits;
    QuantumSystem qs;

    Operation currentOperations[MAX_QUBITS];
    int qubitsValues[MAX_QUBITS];

    Circuit(QuantumSystem qs)
    {
        this->qs = qs;
        numQubits = qs.numberOfBits;

        for(int i = 0; i < numQubits; i++)
        {
            qubitsValues[i] = -1;
        }
    }

    void StartOperation(int qubit, Operation op)
    {
        for(int i = 0; i < numQubits; i++)
        {
            currentOperations[qubit] = Operation::Identity();
        }

        currentOperations[qubit] = op;
    }

    void AddOperation(int qubit, Operation op)
    {
        currentOperations[qubit] = op;
    }

    void FinishOperation()
    {
        Operation aux = currentOperations[0];
        int i = 1;

        if(aux.dim == 4)
        {
            i++;
        }

        for(; i < numQubits; i++)
        {
            if(currentOperations[i].dim == 4)
            {
                aux.AddOperation(currentOperations[i]);
                i++;

                continue;
            }

            aux.AddOperation(currentOperations[i]);
        }

        qs = aux * qs;
        PrintInfo(aux, qs);
    }

    int Measure(int qubit)
    {
        Assert(qubit >= 0 && qubit < numQubits, "Nao pode medir qubit no indice");

        int value = qs.Measure(qubit);
        qubitsValues[qubit] = value;

        return value;
    }

    void StartConditionalOperation(int qubit, Operation op, int condQubit, int condQubitValue)
    {
        Assert(qubitsValues[condQubit] != -1, "O qubit condicional nao foi medido");

        if(qubitsValues[condQubit] != condQubitValue)
        {
            std::cout << "  - A OPERACAO NAO VAI ACONTECER!!!" << std::endl;
            return;
        }

        for(int i = 0; i < numQubits; i++)
        {
            currentOperations[qubit] = Operation::Identity();
        }

        currentOperations[qubit] = op;
    }

    void AddConditionalOperation(int qubit, Operation op, int condQubit, int condQubitValue)
    {
        if(qubitsValues[condQubit] != condQubitValue)
        {
            return;
        }

        currentOperations[qubit] = op;
    }
};

#endif

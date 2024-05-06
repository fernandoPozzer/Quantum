
#ifndef ___QUANTUM_SYSTEM_H___
#define ___QUANTUM_SYSTEM_H___

#include <string>
#include <sstream>
#include <math.h>

#include "Utils.h"
#include "Qubit.h"

class QuantumSystem
{
private:

    Complex* states = NULL;
    int numStates = 0;
    int numberOfBits = 0;

    /**
        Normaliza os estados para a soma de suas
        probabilidades ser 1
    */
    void NormalizeStates()
    {
        float norm = 0;

        for(int i = 0; i < numStates; i++)
        {
            norm += states[i].GetNormSquared();
        }

        norm = sqrt(norm);

        for(int i = 0; i < numStates; i++)
        {
            states[i] /= norm;
        }
    }

public:

    void AddQubit(Qubit q)
    {
        if(states == NULL)
        {
            states = Utils::CopyArray(q.state, 2);
            numStates = 2;
            numberOfBits = 1;

            return;
        }

        Complex* aux = Utils::TensorProduct(states, numStates, q.state, 2);

        delete[] states;
        states = aux;

        numStates *= 2;
        numberOfBits++;
        NormalizeStates();
    }

    /**
        Probabilidade do sistema estar no estado.

        Passar a string representando os valores de cada estado.
        Ex: 101 (primeiro qubit = 1, segundo = 0 e terceiro = 1)
    */
    float GetProb(std::string state)
    {
        if(state.size() !=  numberOfBits)
        {
            return 0;
        }

        int index = Utils::BinaryStringToNumber(state);

        if(index >= numStates)
        {
            return 0;
        }

        return states[index].GetNormSquared();
    }

    /**
        Representacao oficial
    */
    std::string ToString()
    {
        std::stringstream s;

        for(int i = 0; i < numStates; i++)
        {
            if(i != 0)
            {
                s << " + ";
            }

            s << states[i].ToString() << " |" << Utils::NumberToBinaryString(i, numberOfBits) << ">";
        }

        return s.str();
    }

    /**
        Representacao mais facil de entender
    */
    std::string ToColumnString()
    {
        std::stringstream s;

        for(int i = 0; i < numStates; i++)
        {
            s << "|" << Utils::NumberToBinaryString(i, numberOfBits) << "> = ";
            s << states[i].ToString() << std::endl;
        }

        return s.str();
    }

    /**
        Probabilidade de cada estado ocorrer
    */
    std::string ProbabilityToColumnString()
    {
        std::stringstream s;
        float prob;

        for(int i = 0; i < numStates; i++)
        {
            s << "|" << Utils::NumberToBinaryString(i, numberOfBits) << "> = ";

            prob = Utils::Truncate(states[i].GetNormSquared() * 100, 2);
            s << prob << "%" << std::endl;
        }

        return s.str();
    }
};

#endif

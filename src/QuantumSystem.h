
#ifndef ___QUANTUM_SYSTEM_H___
#define ___QUANTUM_SYSTEM_H___

#include <string>
#include <sstream>
#include <math.h>
#include <cassert>

#include "Utils.h"
#include "Qubit.h"

class QuantumSystem
{
private:

    /**
        Normaliza os estados para a soma de suas
        probabilidades ser 1
    */
    void NormalizeStates()
    {
        /*float norm = 0;

        for(int i = 0; i < numStates; i++)
        {
            norm += states[i].GetNormSquared();
        }

        norm = sqrt(norm);*/

        float norm = Utils::GetNorm(states, numStates);

        for(int i = 0; i < numStates; i++)
        {
            states[i] /= norm;
        }
    }

public:

    Complex* states = NULL;
    int numStates = 0;
    int numberOfBits = 0;

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

    void AddQuantumSystem(QuantumSystem qs)
    {
        if(states == NULL)
        {
            states = Utils::CopyArray(qs.states, qs.numStates);
            numStates = qs.numStates;
            numberOfBits = qs.numberOfBits;

            return;
        }

        Complex* aux = Utils::TensorProduct(states, numStates, qs.states, qs.numStates);

        delete[] states;
        states = aux;

        numStates *= qs.numStates;
        numberOfBits += qs.numberOfBits;
        NormalizeStates();
    }

    void StartManualEditing(int numberOfQubits)
    {
        numberOfBits = numberOfQubits;
        numStates = pow(2, numberOfQubits);

        states = new Complex[numStates];
    }

    void DefineStateProbability(std::string bits, Complex prob)
    {
        Assert(bits.size() == numberOfBits, "O numero de bits esta errado para definir o estado");

        int aux = Utils::BinaryStringToNumber(bits);
        states[aux] = prob;
    }

    void FinishManualEditing()
    {
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
        Passa o qubit que se quer obter o valor.
        Comeca em 0 (msb) e termina em numero de bits - 1
        (lsb).
    */
    int Measure(int qubit)
    {
        assert(qubit >= 0 && qubit < numberOfBits);

        int aux;
        int measuredBit;

        float probOfZero;

        for(int i = 0; i < numStates; i++)
        {
            aux = Utils::ExtractBit(i, qubit, numberOfBits);

            if(aux == 0)
            {
                probOfZero += states[i].GetNormSquared();
            }
        }

        if(probOfZero > 0.5)
        {
            measuredBit = 0;
        }
        else
        {
            measuredBit = 1;
        }

        for(int i = 0; i < numStates; i++)
        {
            aux = Utils::ExtractBit(i, qubit, numberOfBits);

            if(aux == measuredBit)
            {
                continue;
            }

            states[i] = Complex(0, 0);
        }

        NormalizeStates();
        return measuredBit;
    }

    static QuantumSystem PhiPlus()
    {
        QuantumSystem qs;

        qs.StartManualEditing(2);
        qs.DefineStateProbability("00", Complex::One());
        qs.DefineStateProbability("11", Complex::One());
        qs.FinishManualEditing();

        return qs;
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

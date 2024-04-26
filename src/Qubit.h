
class Qubit
{
public:
    Complex state[2];

    Qubit(Complex zero, Complex one)
    {
        state[0] = zero;
        state[1] = one;
    }

    Complex GetZero()
    {
        return state[0];
    }

    Complex GetOne()
    {
        return state[1];
    }
};

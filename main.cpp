#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

unsigned int grnFib3(unsigned int f1, unsigned int f2, unsigned int f3, unsigned int r, unsigned int minX)
{
    SYSTEMTIME st;
    GetLocalTime(&st);

    int Ts = st.wMilliseconds + st.wSecond + st.wMinute + st.wHour + st.wDay + st.wYear;

    int x = f1 + f2 + f3 + Ts;
    x %= r;
    x += minX;

    return x;
}

void randomDelayTime(int range, int mn)
{
    SYSTEMTIME st;
    GetLocalTime(&st);

    Sleep(float(int(st.wSecond + st.wMinute + st.wHour) % range + mn + st.wMilliseconds / 1000));
}

unsigned int massivController(unsigned int number, unsigned int mn, vector<bool> &massiv, int &massivCapasity)
{
    int share = 75;

    if(massivCapasity >= massiv.size() * share / 100){
        massivCapasity = 0;

        for(int i = 0; i < massiv.size(); i++){
            massiv[i] = false;
        }
    }
    while(massiv[number - mn] == true){
        number += 1;
        if(number == massiv.size() + mn){
            number = mn;
        }
    }

    massiv[number - mn] = true;
    massivCapasity += 1;

    return number;
}

int main()
{
    unsigned int amount, range, mn, mx;
    cout << "amount number: ";
    cin >> amount;
    cout << "max number: ";
    cin >> mx;
    cout << "min number: ";
    cin >> mn;
    mx += 1;

    if (mn >= mx){
        cout << "error";
        return 0;
    } else {
        range = mx - mn;
    }

    int rangeDelay = 3, mnDelay = 3;

    vector<bool> massiv(range, 0);
    int massivCapasity = 0;

    unsigned int f1 = grnFib3(0, 0, 0, range, mn);
    unsigned int f2 = grnFib3(f1, 0, 0, range, mn);
    unsigned int f3 = grnFib3(f1, f2, 0,range, mn);
    unsigned int variableNumber = grnFib3(f1, f2, f3, range, mn);

    for(int i = 0; i < amount; i++){
        unsigned int x = massivController(variableNumber, mn, massiv, massivCapasity);
        cout << i + 1 << " - " << x << endl;
        f1 = f2;
        f2 = f3;
        f3 = variableNumber;
        variableNumber = grnFib3(f1, f2, f3, range, mn);
        randomDelayTime(rangeDelay, mnDelay);
    }

    return 0;
}

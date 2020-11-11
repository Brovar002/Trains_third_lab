#include <string>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <iostream>

using namespace std;

class Locomotive {
public:
    int speed;
    int Mas;
    int Moshc;
};

class Wagon {
public:
    string TypeV;
    int Gruz;
};

class Station {
public:
    string Name;
    string TypeS;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Map A;
    int kolStan, kolWays, kolTrains, f;
    cout << "выберите способ ввода карты:" << "1-ручками 2-из файла" << endl;
    cin >> f;
    switch (f)
    {
    case 1: {
        cout << "введите количество станций" << endl;
        cin >> kolStan;
        A.SetStations(kolStan);
        cout << "введите количество путей" << endl;
        cin >> kolWays;
        A.SetWays(kolWays);
        cout << "введите количество поездов" << endl;
        cin >> kolTrains;
        A.SetTrains(kolTrains);
    }break;
    case 2: {
        A.FileInStruct();
    }break;
    }
    A.Simulation();
    return 0;
}
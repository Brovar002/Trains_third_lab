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

class Way :public Station {
public:
    Station Start;
    Station End;
    int dWay;
};

class Train :public Locomotive, public Wagon, public Way {
public:
    Way* WayP;
    Wagon* AllV;
    int speedp;
    int Strong;
    int AllWay;
    int kolWs;
    int ostWay;
    int kolWagonov;
    int VesIn;

    void Sostav(int n, int g, Way* A, Station* B, int kolS, int kolV) {
        Strong = 0;
        int vb;
        int dw;
        string v;
        cout << "введите макс. скорость локомотива" << endl;
        cin >> speed;
        cout << "введите срок эксплуатации" << endl;
        cin >> Moshc;
        cout << "введите макс. тяговую силу локомотива" << endl;
        cin >> Mas;
        AllWay = 0;
        WayP = new Way[n];
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                cout << "выберите имя начальной точки из возможных" << endl;
                for (int f = 0; f < kolS; f++) {
                    cout << B[f].Name << " ";
                }
                cout << endl;
                cin >> v;
                WayP[i].Start.Name = v;
                for (int f = 0; f < kolS; f++) {
                    if (B[f].Name == v) {
                        WayP[i].Start.TypeS = B[f].TypeS;
                    }
                }
            }
            else {
                WayP[i].Start = WayP[i - 1].End;
            }
            cout << "выберите имя следующей станции из возможных" << endl;
            for (int f = 0; f < kolV; f++) {
                if (A[f].Start.Name == WayP[i].Start.Name) {
                    cout << A[f].End.Name << " ";
                }
            }
            cout << endl;
            cin >> v;
            WayP[i].End.Name = v;
            for (int f = 0; f < kolS; f++) {
                if (B[f].Name == v) {
                    WayP[i].End.TypeS = B[f].TypeS;
                }
            }
            for (int f = 0; f < kolV; f++) {
                if (A[f].Start.Name == WayP[i].Start.Name) {
                    if (A[f].End.Name == WayP[i].End.Name) {
                        WayP[i].dWay = A[f].dWay;
                    }
                }
            }
            AllWay = AllWay + WayP[i].dWay;
        }
        kolWs = n;
        AllV = new Wagon[g];
        for (int i = 0; i < g; i++) {
            cout << "выберите тип вагона:" << " 1-товарный" << " 2-пассажирский" << endl;
            cin >> vb;
            if (vb == 1) {
                AllV[i].TypeV = "tov";
                Strong++;
            }
            else {
                AllV[i].TypeV = "pas";
                Strong++;
            }
            if (Strong == Mas) {
                i = g;
                cout << "досигнуто максимальное число вагонов" << endl;
            }
            AllV[i].Gruz = 0;
        }
        kolWagonov = g;
        ostWay = 0;
        VesIn = 0;
        speedp = speed - g;
    }
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
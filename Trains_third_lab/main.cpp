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

class Map {
public:
	Station* AllStations;
	Train* Trains;
	int kolS;
	Way* AllWays;
	int kolV;
	int kolTp;

	void SetStations(int kol) {
		int h;
		AllStations = new Station[kol];
		for (int i = 0; i < kol; i++) {
			cout << "введите название станции:" << endl;
			cin >> AllStations[i].Name;
			cout << "выберите тип станции" << "\n1-пассажирская" << "\n2-товарная" << "\n3-пассажирско-товарная" << endl;
			cin >> h;
			switch (h)
			{
			case 1: {
				AllStations[i].TypeS = "Pas";
			}
				  break;
			case 2: {
				AllStations[i].TypeS = "Tov";
			}
				  break;
			case 3: {
				AllStations[i].TypeS = "PasTov";
			}
				  break;
			}
		}
		kolS = kol;
	}
	void SetWays(int kol) {
		AllWays = new Way[kol];
		for (int i = 0; i < kol; i++) {
			cout << "выберите начальную станцию" << endl;
			for (int j = 0; j < kolS; j++) {
				cout << AllStations[j].Name << ", ";
			}
			cin >> AllWays[i].Start.Name;
			cout << endl << "выберите конечную станцию" << endl;
			for (int j = 0; j < kolS; j++) {
				cout << AllStations[j].Name << ", ";
			}
			cin >> AllWays[i].End.Name;
			cout << endl << "введите длину пути" << endl;
			cin >> AllWays[i].dWay;
		}
		kolV = kol;
	}
	void SetTrains(int kolT) {
		kolTp = kolT;
		int n, g;
		Trains = new Train[kolT];
		for (int i = 0; i < kolT; i++) {
			cout << "введите количество путей" << endl;
			cin >> n;
			cout << endl << "введите количество вагонов" << endl;
			cin >> g;
			Trains[i].Sostav(n, g, AllWays, AllStations, kolS, kolV);
		}
	}
	void Simulation() {
		int z, v, typ, kpd;
		int* kpp;
		kpp = new int[kolTp];
		for (int i = 0; i < kolTp; i++) {
			kpp[i] = 0;
		}
		int time = 0;
		while (true) {
			Sleep(1000);
			time++;
			kpd = 0;
			cout << "ход " << time << ": " << endl;
			for (int i = 0; i < kolTp; i++) {
				if (Trains[i].ostWay <= 0) {
					if (kpp[i] >= Trains[i].kolWs) {
						kpp[i]--;
						cout << i + 1 << " поезд: ";
						if (Trains[i].WayP[kpp[i]].End.TypeS == "Pas") {
							z = 0;
							for (int j = 0; j < Trains[i].kolWagonov; j++) {
								if (Trains[i].AllV[j].TypeV == "pas") {
									typ = 1;
									if (Trains[i].AllV[j].Gruz == 0) {
										Trains[i].AllV[j].Gruz = 0;
									}
									else {
										Trains[i].AllV[j].Gruz = 0;
										Trains[i].speed++;
										z++;
									}
								}
							}
						}
						if (Trains[i].WayP[kpp[i]].End.TypeS == "Tov") {
							z = 0;
							for (int j = 0; j < Trains[i].kolWagonov; j++) {
								if (Trains[i].AllV[j].TypeV == "tov") {
									typ = 2;
									if (Trains[i].AllV[j].Gruz == 0) {
										Trains[i].AllV[j].Gruz = 0;
									}
									else {
										Trains[i].AllV[j].Gruz = 0;
										z++;
										Trains[i].speed++;
									}
								}
							}
						}
						if (Trains[i].WayP[kpp[i]].End.TypeS == "PasTov") {
							z = 0;
							for (int j = 0; j < Trains[i].kolWagonov; j++) {
								typ = 3;
								if (Trains[i].AllV[j].Gruz == 0) {
									Trains[i].AllV[j].Gruz = 0;
								}
								else {
									Trains[i].AllV[j].Gruz = 0;
									z++;
									Trains[i].speed++;
								}
							}
						}
						Trains[i].ostWay = 0;
						cout << "konстанция " << Trains[i].WayP[kpp[i]].End.Name << endl;
						cout << " выгрузка ";
						if (typ == 1) {
							cout << "людей " << endl;
						}
						if (typ == 2) {
							cout << "товара " << endl;
						}
						if (typ == 3) {
							cout << "людей и товара " << endl;
						}
						kpp[i] = 0;
					}
					else {
						cout << i + 1 << " поезд: ";
						Trains[i].ostWay = Trains[i].WayP[kpp[i]].dWay;
						if (Trains[i].WayP[kpp[i]].Start.TypeS == "Pas") {
							z = 0;
							for (int j = 0; j < Trains[i].kolWagonov; j++) {
								if (Trains[i].AllV[j].TypeV == "pas") {
									typ = 1;
									if (Trains[i].AllV[j].Gruz == 0) {
										Trains[i].AllV[j].Gruz = 1;
										Trains[i].speed--;
									}
									else {
										Trains[i].AllV[j].Gruz = 0;
										Trains[i].speed++;
										z++;
									}
								}
							}
						}
						if (Trains[i].WayP[kpp[i]].Start.TypeS == "Tov") {
							z = 0;
							for (int j = 0; j < Trains[i].kolWagonov; j++) {
								if (Trains[i].AllV[j].TypeV == "tov") {
									typ = 2;
									if (Trains[i].AllV[j].Gruz == 0) {
										Trains[i].AllV[j].Gruz = 1;
										Trains[i].speed--;
									}
									else {
										Trains[i].AllV[j].Gruz = 0;
										z++;
										Trains[i].speed++;
									}
								}
							}
						}
						if (Trains[i].WayP[kpp[i]].Start.TypeS == "PasTov") {
							z = 0;
							for (int j = 0; j < Trains[i].kolWagonov; j++) {
								typ = 3;
								if (Trains[i].AllV[j].Gruz == 0) {
									Trains[i].AllV[j].Gruz = 1;
									Trains[i].speed--;
								}
								else {
									Trains[i].AllV[j].Gruz = 0;
									z++;
									Trains[i].speed++;
								}
							}
						}
						cout << "станция " << Trains[i].WayP[kpp[i]].Start.Name << endl;
						if (z != 0) {
							cout << " выгрузка ";
							Trains[i].ostWay = 0;
						}
						else {
							cout << " загрузка ";
							kpp[i]++;
						}
						if (typ == 1) {
							cout << "людей " << endl;
						}
						if (typ == 2) {
							cout << "товара " << endl;
						}
						if (typ == 3) {
							cout << "людей и товара " << endl;
						}
					}
					kpd++;
				}
				else {
					Trains[i].ostWay = Trains[i].ostWay - Trains[i].speedp;
				}
			}
			if (kpd == 0) {
				cout << " чух-чух " << endl;
			}
		}
	}
	void FileInStruct() {
		string fileName;
		cout << "введите путь к файлу" << endl;
		cin >> fileName;
		ifstream fin(fileName);
		fin >> kolS;
		cout << kolS << endl;
		AllStations = new Station[kolS];
		for (int i = 0; i < kolS; i++) {
			fin >> AllStations[i].Name;
			cout << AllStations[i].Name << " ";
			fin >> AllStations[i].TypeS;
			cout << AllStations[i].TypeS << endl;
		}
		fin >> kolV;
		cout << kolV << endl;
		AllWays = new Way[kolV];
		for (int i = 0; i < kolV; i++) {
			fin >> AllWays[i].Start.Name;
			cout << AllWays[i].Start.Name << " ";
			fin >> AllWays[i].End.Name;
			cout << AllWays[i].End.Name << " ";
			fin >> AllWays[i].dWay;
			cout << AllWays[i].dWay << endl;
		}
		fin >> kolTp;
		cout << kolTp << endl;
		Trains = new Train[kolTp];
		for (int i = 0; i < kolTp; i++) {
			Trains[i].AllWay;
			fin >> Trains[i].kolWs;
			cout << Trains[i].kolWs << endl;
			fin >> Trains[i].Mas;
			cout << Trains[i].Mas << endl;
			fin >> Trains[i].kolWagonov;
			cout << Trains[i].kolWagonov << endl;
			Trains[i].AllV = new Wagon[Trains[i].kolWagonov];
			for (int j = 0; j < Trains[i].kolWagonov; j++) {
				fin >> Trains[i].AllV[j].TypeV;
				Trains[i].AllV[j].Gruz = 0;
				Trains[i].Strong++;
			}
			fin >> Trains[i].speed;
			cout << Trains[i].speed << endl;
			Trains[i].speedp = Trains[i].speed - Trains[i].kolWagonov;
			fin >> Trains[i].Moshc;
			cout << Trains[i].Moshc << endl;
			Trains[i].WayP = new Way[Trains[i].kolWs];
			for (int j = 0; j < Trains[i].kolWs; j++) {
				fin >> Trains[i].WayP[j].Start.Name;
				cout << Trains[i].WayP[j].Start.Name << " ";
				for (int k = 0; k < kolS; k++) {
					if (Trains[i].WayP[j].Start.Name == AllStations[k].Name) {
						Trains[i].WayP[j].Start.TypeS = AllStations[k].TypeS;
						cout << Trains[i].WayP[j].Start.TypeS << endl;
					}
				}
				fin >> Trains[i].WayP[j].End.Name;
				cout << Trains[i].WayP[j].End.Name << endl;
				for (int k = 0; k < kolS; k++) {
					if (Trains[i].WayP[j].End.Name == AllStations[k].Name) {
						Trains[i].WayP[j].End.TypeS = AllStations[k].TypeS;
						cout << Trains[i].WayP[j].End.TypeS << endl;
					}
				}
				for (int f = 0; f < kolV; f++) {
					if (AllWays[f].Start.Name == Trains[i].WayP[j].Start.Name) {
						if (AllWays[f].End.Name == Trains[i].WayP[j].End.Name) {
							Trains[i].WayP[j].dWay = AllWays[f].dWay;
						}
					}
				}
				Trains[i].AllWay = Trains[i].AllWay + Trains[i].WayP[j].dWay;
			}
			Trains[i].ostWay = 0;
			Trains[i].VesIn = 0;

		}
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
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;
// filmo duomenys
struct Filmas {
    int id;
    string pavadinimas;
    string zanras;
    int metai;
    double ivertinimas;
};

// funkcijos
void nuskaitytiFaila(vector<Filmas>& filmai);
void issaugotiFaila(vector<Filmas>& filmai);
void rodytiFilmus(vector<Filmas>& filmai);
void pridetiFilma(vector<Filmas>& filmai);
void redaguotiFilma(vector<Filmas>& filmai);
void salintiFilma(vector<Filmas>& filmai);
void ieskotiPagalZanra(vector<Filmas>& filmai);
void rikiuotiPagalIvertinima(vector<Filmas>& filmai);
void skaiciuotiVidurki(vector<Filmas>& filmai);

int main()
{
    vector<Filmas> filmai; // visi filmai

    nuskaitytiFaila(filmai); // nuskaityti is failo

    int pasirinkimas;

    do {
        cout << "\n===== FILMU KATALOGAS =====\n";
        cout << "1. Rodyti filmus\n";
        cout << "2. Prideti filma\n";
        cout << "3. Redaguoti filma\n";
        cout << "4. Salinti filma\n";
        cout << "5. Paieska pagal zanra\n";
        cout << "6. Rikiuoti pagal ivertinima\n";
        cout << "7. Vidurkis\n";
        cout << "8. Issaugoti ir iseiti\n";

        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;

        switch (pasirinkimas)
        {
        case 1: rodytiFilmus(filmai); break;
        case 2: pridetiFilma(filmai); break;
        case 3: redaguotiFilma(filmai); break;
        case 4: salintiFilma(filmai); break;
        case 5: ieskotiPagalZanra(filmai); break;
        case 6: rikiuotiPagalIvertinima(filmai); break;
        case 7: skaiciuotiVidurki(filmai); break;
        case 8:
            issaugotiFaila(filmai); // issaugom i nauja faila
            cout << "Issaugota i filmai_atnaujinti.txt\n";
            break;
        default:
            cout << "Blogas pasirinkimas!\n";
        }

    } while (pasirinkimas != 8);

    return 0;
}

// nuskaitymas is failo
void nuskaitytiFaila(vector<Filmas>& filmai)
{
    ifstream failas("filmai.txt");

    if (!failas)
    {
        cout << "Nepavyko atidaryti failo!\n";
        return;
    }

    string eilute;

    while (getline(failas, eilute))
    {
        stringstream ss(eilute);
        Filmas f;

        string id, metai, ivertinimas;

        getline(ss, id, ';');
        getline(ss, f.pavadinimas, ';');
        getline(ss, f.zanras, ';');
        getline(ss, metai, ';');
        getline(ss, ivertinimas, ';');

        f.id = stoi(id);
        f.metai = stoi(metai);
        f.ivertinimas = stod(ivertinimas);

        filmai.push_back(f);
    }

    failas.close();

    cout << "Nuskaityta filmu: " << filmai.size() << endl;
}

// issaugo i nauja faila
void issaugotiFaila(vector<Filmas>& filmai)
{
    ofstream failas("filmai_atnaujinti.txt");

    for (int i = 0; i < filmai.size(); i++)
    {
        failas << filmai[i].id << ";"
            << filmai[i].pavadinimas << ";"
            << filmai[i].zanras << ";"
            << filmai[i].metai << ";"
            << filmai[i].ivertinimas;

        if (i != filmai.size() - 1)
            failas << endl;
    }

    failas.close();
}

// rodo visus filmus
void rodytiFilmus(vector<Filmas>& filmai)
{
    for (auto& f : filmai)
    {
        cout << f.id << " | "
            << f.pavadinimas << " | "
            << f.zanras << " | "
            << f.metai << " | "
            << f.ivertinimas << endl;
    }
}

// prideda nauja filma
void pridetiFilma(vector<Filmas>& filmai)
{
    Filmas f;

    cout << "ID: ";
    cin >> f.id;

    for (auto& x : filmai)
    {
        if (x.id == f.id)
        {
            cout << "Toks ID jau yra!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Pavadinimas: ";
    getline(cin, f.pavadinimas);

    cout << "Zanras: ";
    getline(cin, f.zanras);

    cout << "Metai: ";
    cin >> f.metai;

    cout << "Ivertinimas: ";
    cin >> f.ivertinimas;

    filmai.push_back(f);
}

// redaguoja filma
void redaguotiFilma(vector<Filmas>& filmai)
{
    int id;
    cout << "ID: ";
    cin >> id;

    for (auto& f : filmai)
    {
        if (f.id == id)
        {
            cin.ignore();

            cout << "Pavadinimas: ";
            getline(cin, f.pavadinimas);

            cout << "Zanras: ";
            getline(cin, f.zanras);

            cout << "Metai: ";
            cin >> f.metai;

            cout << "Ivertinimas: ";
            cin >> f.ivertinimas;

            return;
        }
    }

    cout << "Nerasta!\n";
}

// pasalina filma
void salintiFilma(vector<Filmas>& filmai)
{
    int id;
    cout << "ID: ";
    cin >> id;

    for (int i = 0; i < filmai.size(); i++)
    {
        if (filmai[i].id == id)
        {
            filmai.erase(filmai.begin() + i);
            cout << "Pasalinta!\n";
            return;
        }
    }

    cout << "Nerasta!\n";
}

// paieska pagal zanra
void ieskotiPagalZanra(vector<Filmas>& filmai)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string z;

    cout << "Zanras: ";
    getline(cin, z);

    for (auto& f : filmai)
    {
        if (f.zanras == z)
            cout << f.pavadinimas << endl;
    }
}

// rikiavimas pagal ivertinima
void rikiuotiPagalIvertinima(vector<Filmas>& filmai)
{
    sort(filmai.begin(), filmai.end(),
        [](Filmas a, Filmas b)
        {
            return a.ivertinimas > b.ivertinimas;
        });

    cout << "Surikiuota!\n";
}

// vidurkis
void skaiciuotiVidurki(vector<Filmas>& filmai)
{
    double suma = 0;

    for (auto& f : filmai)
        suma += f.ivertinimas;

    cout << "Vidurkis: " << suma / filmai.size() << endl;
}
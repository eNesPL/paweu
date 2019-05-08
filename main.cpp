#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "Pasazer.h"
using namespace std;
const string sciezka_do_pliku = "D:\\baza.txt";

void wypisz(vector<Pasazer>Baza){
    int g =Baza.size();
    for(int i=0;i<g;i++){
        cout << "-------------"<<endl;
        cout << "NR:"+to_string(i+1)<<endl;
        cout << "Imie "+ Baza[i].imie<<endl;
        cout << "Nazwisko "+ Baza[i].nazwisko<<endl;
        cout << "Lot "+ to_string(Baza[i].lot)<<endl;
        cout << "-------------"<<endl;
    }
}
void szukaj(const string &str,vector<Pasazer>Baza){
    vector<Pasazer>temp;
    int g=Baza.size();
    for(int i=0;i<g;i++){
            if(Baza[i].imie==str || Baza[i].nazwisko ==str){
                temp.push_back(Baza[i]);
            }
    }
    wypisz(temp);
}
void szukaj(int nr,vector<Pasazer>Baza){
    vector<Pasazer>temp;
    int g=Baza.size();
    for(int i=0;i<g;i++){
        if(Baza[i].lot==nr){
            temp.push_back(Baza[i]);
        }
    }
    wypisz(temp);
}
vector<Pasazer> usun(vector<Pasazer> Baza,int nr){
    Baza.erase(Baza.begin()+nr-1);
    cout << "Usunieto"<<endl;
    return Baza;
}
vector<Pasazer> wczytaj(vector<Pasazer>Baza){
    fstream plik;
    string linia;
    Pasazer temp;
    plik.open(sciezka_do_pliku, ios::in);
    if(plik.good())
    {
        if (plik.peek() == std::ifstream::traits_type::eof() )
        {
            return Baza;

        }
        while(!plik.eof())
        {
            getline(plik, linia);
            if(linia.empty()){
                return Baza;
            }
            temp.imie=linia;
            getline(plik, linia);
            temp.nazwisko=linia;
            getline(plik, linia);
            temp.lot = stoi(linia);
            Baza.push_back(temp);
        }
        plik.close();
    }
    return Baza;
}
void zapisz(vector<Pasazer>Baza){
    fstream plik;
    plik.open(sciezka_do_pliku,ios::out | ios::trunc);
    int g=Baza.size();
    for(int n=0;n<g;n++){
        plik << Baza[n].imie <<endl;
        plik << Baza[n].nazwisko <<endl;
        plik << Baza[n].lot <<endl;
    }
    plik.close();
}
vector<Pasazer> dodaj(vector<Pasazer>Baza){
    Pasazer temp;
    cout << "Dodawanie nowego pasazera" <<endl;
    cout <<"Podaj imie: "<<endl;
    cin >> temp.imie;
    cout << "Podaj nazwisko: "<<endl;
    cin >>temp.nazwisko;
    cout << "Podaj lot: "<<endl;
    cin >>temp.lot;
    Baza.push_back(temp);
    return Baza;
}

int main() {

    vector<Pasazer> Baza;
    Baza = wczytaj(Baza);
    int odp;
    bool mango = true;
    string stro;
    while(mango){
        odp=0;
        cout << "Wybierz opcje: " <<endl;
        cout << "1.Wyswietl" <<endl;
        cout << "2.Dodaj" <<endl;
        cout << "3.Usun" <<endl;
        cout << "4.Szukaj"<<endl;
        cout << "Inne = wyscie z programu"<<endl;
        cin >> odp;
        switch(odp){
            case 1:
                wypisz(Baza);
                break;
            case 2:
                Baza = dodaj(Baza);
                break;
            case 3:
                wypisz(Baza);
                cout << "Wpisz nr do usuniecia: ";
                cin >> odp;
                Baza = usun(Baza,odp);
                break;
            case 4:
                cout << "Wybierz tryb szukania: "<<endl;
                cout << "1. Po Imieniu lub Nazwisku"<<endl;
                cout << "2. Po nr lotu"<<endl;
                cout << "inne = Powrot"<<endl;
                cin >> odp;
                switch(odp){
                    case 1:
                        cout << " Podaj Imie lub Nazwisko: ";
                        cin >> stro;
                        szukaj(stro,Baza);
                        break;
                    case 2:
                        cout << " Podaj nr lotu: ";
                        cin >> odp;
                        szukaj(odp,Baza);
                        break;
                    default:
                        cout << "Powrot do menu"<<endl;
                        break;
                }
                break;
            default:
                mango = false;
                break;
        }
        zapisz(Baza);
    }

return 0;
}

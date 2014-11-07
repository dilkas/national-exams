#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 21

using namespace std;

map<int, vector<string> > duomenys;
ofstream rezultatai;

void skaityk() {
  ifstream uzduotis(IVESTIS);
  int n;
  uzduotis >> n;
  for (int skaiciuoklis = 0; skaiciuoklis < n; skaiciuoklis++) {
    char pavadinimas_c[ILGIS];
    uzduotis.read(pavadinimas_c, ILGIS);
    char be_naujos_eilutes[ILGIS - 1];
    memcpy(be_naujos_eilutes, &pavadinimas_c[1], ILGIS - 1);
    string pavadinimas(be_naujos_eilutes);
    int marsrutu_skaicius;
    uzduotis >> marsrutu_skaicius;
    for (int antras_skaiciuoklis = 0; antras_skaiciuoklis < marsrutu_skaicius;
  antras_skaiciuoklis++) {
      int marsruto_numeris;
      uzduotis >> marsruto_numeris;
      if (duomenys.find(marsruto_numeris) == duomenys.end()) {
        vector<string> stoteles;
        stoteles.push_back(pavadinimas);
        duomenys[marsruto_numeris] = stoteles;
      } else {
        duomenys[marsruto_numeris].push_back(pavadinimas);
      }
    }
  }
  uzduotis.close();
}

int rask() {
  int rastas = -1;
  for (map<int, vector<string> >::iterator rodykle = duomenys.begin();
       rodykle != duomenys.end(); rodykle++) {
    if (rastas == -1 || (rodykle->second).size() > duomenys[rastas].size())
      rastas = rodykle->first;
  }
  return rastas;
}

void spausdink(int marsrutas) {
  for (vector<string>::iterator rodykle = duomenys[marsrutas].begin();
       rodykle != duomenys[marsrutas].end(); rodykle++) {
    rezultatai << *rodykle << endl;
  }
}

int main() {
  skaityk();
  int didziausias = rask();
  rezultatai.open(ISVESTIS);
  rezultatai << didziausias << endl;
  spausdink(didziausias);
  rezultatai.close();
  return 0;
}

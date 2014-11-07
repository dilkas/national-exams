#include <fstream>
#include <iomanip>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define MAKSIMALUS_N 100
#define VARDO_ILGIS 15
#define SKAICIU_ILGIS 5

using namespace std;

struct grybautojas {
  string vardas;
  int baravykai, raudonikiai, lepsiai;
};

int n;
grybautojas duomenys[MAKSIMALUS_N];

void skaityk() {
  ifstream uzduotis(IVESTIS);
  uzduotis >> n;
  for (int indeksas = 0; indeksas < n; indeksas++) {
    grybautojas dzonas;
    dzonas.baravykai = 0;
    dzonas.raudonikiai = 0;
    dzonas.lepsiai = 0;
    int d;
    uzduotis >> dzonas.vardas >> d;
    int reikia_tarpu = VARDO_ILGIS - dzonas.vardas.length();
    for (int tarpai = 0; tarpai < reikia_tarpu; tarpai++) dzonas.vardas += ' ';
    for (int skaiciuoklis = 0; skaiciuoklis < d; skaiciuoklis++) {
      int baravykai, raudonikiai, lepsiai;
      uzduotis >> baravykai >> raudonikiai >> lepsiai;
      dzonas.baravykai += baravykai;
      dzonas.raudonikiai += raudonikiai;
      dzonas.lepsiai += lepsiai;
    }
    duomenys[indeksas] = dzonas;
  }
  uzduotis.close();
}

void rasyk() {
  ofstream rezultatai(ISVESTIS);
  for (int indeksas = 0; indeksas < n; indeksas++) {
    rezultatai << duomenys[indeksas].vardas
               << setw(SKAICIU_ILGIS) << duomenys[indeksas].baravykai
               << setw(SKAICIU_ILGIS)<< duomenys[indeksas].raudonikiai
               << setw(SKAICIU_ILGIS) << duomenys[indeksas].lepsiai << endl;
  }
  rezultatai.close();
}

int rask() {
  int didziausias_indeksas = 0;
  int didziausia_suma = 0;
  for (int indeksas = 0; indeksas < n; indeksas++) {
    int suma = duomenys[indeksas].baravykai + duomenys[indeksas].raudonikiai + duomenys[indeksas].lepsiai;
    if (suma > didziausia_suma) {
      didziausias_indeksas = indeksas;
      didziausia_suma = suma;
    }
  }
  return didziausias_indeksas;
}

int main() {
  skaityk();
  rasyk();
  ofstream rezultatai(ISVESTIS, ios::app);
  int geriausias = rask();
  rezultatai << duomenys[geriausias].vardas << duomenys[geriausias].baravykai
    + duomenys[geriausias].raudonikiai + duomenys[geriausias].lepsiai << endl;
  rezultatai.close();
  return 0;
}

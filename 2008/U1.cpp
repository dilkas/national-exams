#include <fstream>
#include <iomanip>
#include <iostream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"
#define MAKSIMALUS_M 100
#define PLOTIS 6

using namespace std;

int ilipo[MAKSIMALUS_M];
int islipo[MAKSIMALUS_M];
ofstream rezultatai;

void skaityk() {
  ifstream uzduotis(IVESTIS);
  int n;
  uzduotis >> n;
  for (int skaiciuoklis = 0; skaiciuoklis < n; skaiciuoklis++) {
    int m, lipo;
    uzduotis >> m >> lipo;
    if (lipo > 0) ilipo[m - 1] += lipo;
    else islipo[m - 1] += lipo;
  }
  uzduotis.close();
}

void bendras_spausdinimas(int (*ka_isvesti)(int), bool nauja_eilute = true) {
  for (int m = 0; m < MAKSIMALUS_M; m++) {
    if (ilipo[m] || islipo[m]) rezultatai << setw(PLOTIS) << (*ka_isvesti)(m);
  }
  if (nauja_eilute) rezultatai << endl;
}

int marsruto_numeris(int m) {
  return m + 1;
}

int ilipusiu_skaicius(int m) {
  return ilipo[m];
}

int islipusiu_skaicius(int m) {
  return islipo[m];
}

void spausdink() {
  bendras_spausdinimas(marsruto_numeris, false);
}

int rask() {
  int rastas = 0;
  for (int m = 0; m < MAKSIMALUS_M; m++) {
    if (ilipo[m] > ilipo[rastas]) rastas = m;
  }
  return rastas + 1;
}



int main() {
  for (int m = 0; m < MAKSIMALUS_M; m++) {
    ilipo[m] = 0;
    islipo[m] = 0;
  }
  skaityk();
  rezultatai.open(ISVESTIS);
  spausdink();
  rezultatai << endl;
  bendras_spausdinimas(ilipusiu_skaicius);
  bendras_spausdinimas(islipusiu_skaicius);
  rezultatai << setw(PLOTIS) << rask() << endl;
  return 0;
}

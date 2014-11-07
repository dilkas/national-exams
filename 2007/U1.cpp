#include <fstream>
#include <iostream>

#define DIENU_SKAICIUS 31
#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"

using namespace std;

int rasti(int baravykai[], int raudonikiai[], int lepsiai[]) {
  int didziausias_d = 0;
  int didziausia_suma = 0;
  for (int d = 0; d < DIENU_SKAICIUS; d++) {
    int suma = baravykai[d] + raudonikiai[d] + lepsiai[d];
    if (suma > didziausia_suma) {
      didziausias_d = d;
      didziausia_suma = suma;
    }
  }
  return didziausias_d + 1;
}

void spausdinti(int baravykai[], int raudonikiai[], int lepsiai[]) {
  ofstream rezultatai(ISVESTIS);
  for (int d = 0; d < DIENU_SKAICIUS; d++) {
    if (baravykai[d] || raudonikiai[d] || lepsiai[d]) {
      rezultatai << d + 1 << ' ' << baravykai[d] << ' ' << raudonikiai[d]
                 << ' ' << lepsiai[d] << endl;
    }
  }
  int d = rasti(baravykai, raudonikiai, lepsiai);
  rezultatai << d << ' ' << baravykai[d - 1] + raudonikiai[d - 1] + lepsiai[d - 1] << endl;
  rezultatai.close();
}

int main() {
  ifstream uzduotis(IVESTIS);
  int n;
  uzduotis >> n;
  int baravykai[DIENU_SKAICIUS];
  int raudonikiai[DIENU_SKAICIUS];
  int lepsiai[DIENU_SKAICIUS];
  for (int d = 0; d < DIENU_SKAICIUS; d++) {
    baravykai[d] = 0;
    raudonikiai[d] = 0;
    lepsiai[d] = 0;
  }
  for (int indeksas = 0; indeksas < n; indeksas++) {
    int d, baravyku_skaicius, raudonikiu_skaicius, lepsiu_skaicius;
    uzduotis >> d >> baravyku_skaicius >> raudonikiu_skaicius >> lepsiu_skaicius;
    baravykai[d - 1] += baravyku_skaicius;
    raudonikiai[d - 1] += raudonikiu_skaicius;
    lepsiai[d - 1] += lepsiu_skaicius;
  }
  uzduotis.close();
  spausdinti(baravykai, raudonikiai, lepsiai);
  return 0;
}

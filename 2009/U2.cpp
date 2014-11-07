#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 20
#define MAX_N 50

using namespace std;

struct begikas {
  int min, s, grupe;
  string vardas;
  bool operator<(begikas kitas) const {
    if (min != kitas.min) return min > kitas.min;
    return s > kitas.s;
  }
};

void swap(begikas masyvas[], int a, int b) {
  begikas temp = masyvas[a];
  masyvas[a] = masyvas[b];
  masyvas[b] = temp;
}

int particija(begikas masyvas[], int kairysis, int desinysis, int pivoto_i) {
  begikas pivotas = masyvas[pivoto_i];
  swap(masyvas, pivoto_i, desinysis);
  int indeksas = kairysis;
  for (int i = kairysis; i < desinysis; i++) {
    if (pivotas < masyvas[i]) swap(masyvas, i, indeksas++);
  }
  swap(masyvas, indeksas, desinysis);
  return indeksas;
}

void quicksort(begikas masyvas[], int kairysis, int desinysis) {
  if (kairysis < desinysis) {
    int pivoto_i = (kairysis + desinysis) / 2;
    int pivoto_naujas_i = particija(masyvas, kairysis, desinysis, pivoto_i);
    quicksort(masyvas, kairysis, pivoto_naujas_i - 1);
    quicksort(masyvas, pivoto_naujas_i + 1, desinysis);
  }
}

void spausdink(begikas duomenys[], int n, int grupiu_dydziai[]) {
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < n; i++) {
    if (grupiu_dydziai[duomenys[i].grupe] > 0) {
      grupiu_dydziai[duomenys[i].grupe]--;
      rezultatai << duomenys[i].vardas << duomenys[i].min << ' '
                 << duomenys[i].s << endl;
    }
  }
  rezultatai.close();
}

int main() {
  ifstream uzduotis(IVESTIS);
  int k;
  uzduotis >> k;
  begikas duomenys[MAX_N];
  int n = 0;
  int grupiu_dydziai[k];
  for (int grupe = 0; grupe < k; grupe++) {
    int skaicius;
    uzduotis >> skaicius;
    grupiu_dydziai[grupe] = 0;
    for (int skaiciuoklis = 0; skaiciuoklis < skaicius; skaiciuoklis++) {
      begikas naujas;
      char c[ILGIS + 1];
      uzduotis.read(c, ILGIS + 1);
      char be_newline[ILGIS + 1];
      memcpy(be_newline, &c[1], ILGIS);
      be_newline[ILGIS] = '\0';
      string vardas(be_newline);
      naujas.vardas = vardas;
      uzduotis >> naujas.min >> naujas.s;
      naujas.grupe = grupe;
      duomenys[n++] = naujas;
      grupiu_dydziai[grupe]++;
    }
  }
  uzduotis.close();
  for (int i = 0; i < k; i++) grupiu_dydziai[i] /= 2;
  quicksort(duomenys, 0, n - 1);
  spausdink(duomenys, n, grupiu_dydziai);
  return 0;
}

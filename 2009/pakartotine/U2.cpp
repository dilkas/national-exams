#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define MAX_N 50
#define ILGIS 20
#define KIEK 5

using namespace std;

struct plaukikas {
  string vardas;
  int min, s;
  bool operator<(plaukikas kitas) const {
    if (min != kitas.min) return min > kitas.min;
    return s > kitas.s;
  }
};

void swap(plaukikas sportininkai[], int a, int b) {
  plaukikas temp = sportininkai[a];
  sportininkai[a] = sportininkai[b];
  sportininkai[b] = temp;
}

void bubble(plaukikas sportininkai[], int n) {
  bool buvo_swapas;
  do {
    buvo_swapas = false;
    for (int i = 1; i < n; i++) {
      if (sportininkai[i - 1] < sportininkai[i]) {
        swap(sportininkai, i - 1, i);
        buvo_swapas = true;
      }
    }
  } while (buvo_swapas);
}

void spausdink(plaukikas sportininkai[]) {
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < KIEK; i++) {
    rezultatai << sportininkai[i].vardas << sportininkai[i].min << ' '
               << sportininkai[i].s << endl;
  }
  rezultatai.close();
}

int main() {
  ifstream uzduotis(IVESTIS);
  int k;
  uzduotis >> k;
  plaukikas sportininkai[MAX_N];
  int n = 0;
  for (int i = 0; i < k; i++) {
    int skaicius;
    uzduotis >> skaicius;
    for (int j = 0; j < skaicius; j++) {
      char c[ILGIS + 1];
      uzduotis.read(c, ILGIS + 1);
      char apdorotas[ILGIS + 1];
      memcpy(apdorotas, &c[1], ILGIS);
      apdorotas[ILGIS] = '\0';
      string vardas(apdorotas);
      plaukikas naujas;
      naujas.vardas = vardas;
      uzduotis >> naujas.min >> naujas.s;
      sportininkai[n++] = naujas;
    }
  }
  uzduotis.close();
  bubble(sportininkai, n);
  spausdink(sportininkai);
  return 0;
}

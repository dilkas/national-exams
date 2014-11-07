#include <fstream>
#include <string.h>

#define VALSTYBES_PAVADINIMO_ILGIS 15
#define MOKYKLOS_PAVADINIMO_ILGIS 30
#define IVESTIS "P2.txt"
#define ISVESTIS "P2rez.txt"

using namespace std;

struct mokykla {
  string valstybe, pavadinimas;
  int reitingas;
  bool operator<(mokykla kita) const {
    return reitingas > kita.reitingas;
  }
};

string skaityk(ifstream &uzduotis, int ilgis) {
  char c[ilgis + 1];
  uzduotis.read(c, ilgis + 1);
  char apdorotas[ilgis + 1];
  memcpy(apdorotas, &c[1], ilgis);
  apdorotas[ilgis] = '\0';
  string cpp(apdorotas);
  return cpp;
}

void swap(mokykla mokyklos[], int a, int b) {
  mokykla temp = mokyklos[a];
  mokyklos[a] = mokyklos[b];
  mokyklos[b] = temp;
}

void bubble(mokykla mokyklos[], int N) {
  bool buvo_swapas;
  do {
    buvo_swapas = false;
    for (int i = 1; i < N; i++) {
      if (mokyklos[i] < mokyklos[i - 1]) {
        swap(mokyklos, i - 1, i);
        buvo_swapas = true;
      }
    }
  } while (buvo_swapas);
}

int main() {
  ifstream uzduotis(IVESTIS);
  int N;
  uzduotis >> N;
  mokykla mokyklos[N];
  for (int i = 0; i < N; i++) {
    string valstybe = skaityk(uzduotis, VALSTYBES_PAVADINIMO_ILGIS);
    int skaicius;
    uzduotis >> skaicius;
    mokykla valstybes_mokyklos[skaicius];
    int max_j = 0;
    for (int j = 0; j < skaicius; j++) {
      mokykla nauja;
      nauja.valstybe = valstybe;
      nauja.pavadinimas = skaityk(uzduotis, MOKYKLOS_PAVADINIMO_ILGIS);
      uzduotis >> nauja.reitingas;
      valstybes_mokyklos[j] = nauja;
      if (nauja.reitingas > valstybes_mokyklos[max_j].reitingas) max_j = j;
    }
    mokyklos[i] = valstybes_mokyklos[max_j];
  }
  uzduotis.close();
  bubble(mokyklos, N);
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < N; i++) {
    rezultatai << mokyklos[i].valstybe << ' ' << mokyklos[i].pavadinimas
               << ' ' << mokyklos[i].reitingas << endl;
  }
  rezultatai.close();
  return 0;
}

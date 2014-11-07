#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define MAX_N 10
#define ILGIS 15

using namespace std;

struct patiekalas {
  string pavadinimas;
  int kiekiai[MAX_N];
};

int patiekalo_kaina(patiekalas p, int kainos[], int N) {
  int suma = 0;
  for (int i = 0; i < N; i++) suma += p.kiekiai[i] * kainos[i];
  return suma;
}

int pietu_kaina(patiekalas patiekalai[], int P, int kainos[], int N) {
  int suma = 0;
  for (int i = 0; i < P; i++)
    suma += patiekalo_kaina(patiekalai[i], kainos, N);
  return suma;
}

int main() {
  ifstream uzduotis(IVESTIS);
  int N, P;
  uzduotis >> N >> P;
  int kainos[N];
  patiekalas patiekalai[P];
  for (int i = 0; i < N; i++) uzduotis >> kainos[i];
  for (int i = 0; i < P; i++) {
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apdorotas[ILGIS + 1];
    memcpy(apdorotas, &c[1], ILGIS);
    apdorotas[ILGIS] = '\0';
    string pavadinimas(apdorotas);
    patiekalas naujas;
    naujas.pavadinimas = pavadinimas;
    for (int j = 0; j < N; j++) uzduotis >> naujas.kiekiai[j];
    patiekalai[i] = naujas;
  }
  uzduotis.close();
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < P; i++) {
    rezultatai << patiekalai[i].pavadinimas << ' '
               << patiekalo_kaina(patiekalai[i], kainos, N) << endl;
  }
  int suma = pietu_kaina(patiekalai, P, kainos, N);
  rezultatai << suma / 100 << ' ' << suma % 100 << endl;
  rezultatai.close();
  return 0;
}

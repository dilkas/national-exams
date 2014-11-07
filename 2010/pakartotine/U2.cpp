#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 15
#define MAX_P 30

using namespace std;

struct zmogus {
  string vardas;
  int kiekiai[MAX_P];
};

int vieno_kaina(zmogus dzonas, int kainos[], int P) {
  int suma = 0;
  for (int i = 0; i < P; i++) suma += dzonas.kiekiai[i] * kainos[i];
  return suma;
}

int is_viso(zmogus zmones[], int N, int kainos[], int P) {
  int suma = 0;
  for (int i = 0; i < N; i++) suma += vieno_kaina(zmones[i], kainos, P);
  return suma;
}

int main() {
  ifstream uzduotis(IVESTIS);
  int P, N;
  uzduotis >> P;
  int kainos[P];
  for (int i = 0; i < P; i++) uzduotis >> kainos[i];
  uzduotis >> N;
  zmogus zmones[N];
  for (int i = 0; i < N; i++) {
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apdorotas[ILGIS + 1];
    memcpy(apdorotas, &c[1], ILGIS);
    apdorotas[ILGIS] = '\0';
    string vardas(apdorotas);
    zmogus naujas;
    naujas.vardas = vardas;
    for (int j = 0; j < P; j++) uzduotis >> naujas.kiekiai[j];
    zmones[i] = naujas;
  }
  uzduotis.close();
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < N; i++)
    rezultatai << zmones[i].vardas << ' ' << vieno_kaina(zmones[i], kainos, P)
               << endl;
  int suma = is_viso(zmones, N, kainos, P);
  rezultatai << suma / 100 << ' '<< suma % 100 << endl;
  rezultatai.close();
  return 0;
}

#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"

using namespace std;

int suma(int nominalai[], int monetos[], int skaicius) {
  int suma = 0;
  for (int i = 0; i < skaicius; i++)
    suma += nominalai[i] * monetos[i];
  return suma;
}

int knapsack(int suma, int nominalai[], int dydis, int kiekiai[]) {
  int minimumas[suma + 1];
  minimumas[0] = 0;
  int zingsniai[suma];
  for (int i = 1; i <= suma; i++) {
    minimumas[i] = -1;
    for (int j = 0; j < dydis; j++) {
      if (nominalai[j] > i) break;
      int verte = 1 + minimumas[i - nominalai[j]];
      if (verte > 0 && (minimumas[i] == -1 || verte < minimumas[i])) {
        minimumas[i] = verte;
        zingsniai[i - 1] = j;
      }
    }
  }
  int indeksas = suma - 1;
  while (indeksas > -1) {
    kiekiai[zingsniai[indeksas]]++;
    indeksas -= nominalai[zingsniai[indeksas]];
  }
  return minimumas[suma];
}

void dry(int suma, int nominalai[], int skaicius,
         ofstream &rezultatai) {
  int kiekiai[skaicius];
  for (int i = 0; i < skaicius; i++) kiekiai[i] = 0;
  int atsakymas = knapsack(suma, nominalai, skaicius, kiekiai);
  for (int i = 0; i < skaicius; i++)
    rezultatai << nominalai[i] << ' ' << kiekiai[i] << endl;
  rezultatai << atsakymas << endl;
}

int main() {
  ifstream uzduotis(IVESTIS);
  int gilijos_skaicius;
  uzduotis >> gilijos_skaicius;
  int gilijos_nominalai[gilijos_skaicius];
  for (int i = 0; i < gilijos_skaicius; i++)
    uzduotis >> gilijos_nominalai[i];
  int gilijos_monetos[gilijos_skaicius];
  for (int i = 0; i < gilijos_skaicius; i++)
    uzduotis >> gilijos_monetos[i];

  int eglijos_skaicius;
  uzduotis >> eglijos_skaicius;
  int eglijos_nominalai[eglijos_skaicius];
  for (int i = 0; i < eglijos_skaicius; i++)
    uzduotis >> eglijos_nominalai[i];
  int eglijos_monetos[eglijos_skaicius];
  for (int i = 0; i < eglijos_skaicius; i++)
    uzduotis >> eglijos_monetos[i];
  uzduotis.close();
  ofstream rezultatai(ISVESTIS);
  dry(suma(gilijos_nominalai, gilijos_monetos, gilijos_skaicius),
      eglijos_nominalai, eglijos_skaicius, rezultatai);
  dry(suma(eglijos_nominalai, eglijos_monetos, eglijos_skaicius),
      gilijos_nominalai, gilijos_skaicius, rezultatai);
  rezultatai.close();
  return 0;
}

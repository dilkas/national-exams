#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2Rez.txt"
#define MAX_N 50
#define ILGIS 10

using namespace std;

struct dievas {
  string vardas;
  int taskai, kiek_lyginiu;
  bool operator>(dievas kitas) const {
    if (taskai != kitas.taskai) return taskai > kitas.taskai;
    return kiek_lyginiu > kitas.kiek_lyginiu;
  }
};

void skaityk(dievas dievai[], int &n) {
  ifstream uzduotis(IVESTIS);
  int k;
  uzduotis >> n >> k;
  for (int i = 0; i < n; i++) {
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apdorota[ILGIS + 1];
    memcpy(apdorota, &c[1], ILGIS);
    apdorota[ILGIS] = '\0';
    string vardas(apdorota);
    dievas naujas;
    naujas.vardas = vardas;
    naujas.taskai = 0;
    naujas.kiek_lyginiu = 0;
    for (int j = 0; j < k; j++) {
      int kauliukas;
      uzduotis >> kauliukas;
      if (kauliukas % 2 == 0) {
        naujas.taskai += kauliukas;
        naujas.kiek_lyginiu++;
      }
      else naujas.taskai -= kauliukas;
    }
    dievai[i] = naujas;
  }
  uzduotis.close();
}

int rask(dievas dievai[], int n) {
  int max = 0;
  for (int i = 0; i < n; i++) {
    if (dievai[i] > dievai[max]) max = i;
  }
  return max;
}

int main() {
  dievas dievai[MAX_N];
  int n;
  skaityk(dievai, n);
  int i = rask(dievai, n);
  ofstream rezultatai(ISVESTIS);
  rezultatai << dievai[i].vardas << ' ' << dievai[i].taskai << endl;
  rezultatai.close();
  return 0;
}

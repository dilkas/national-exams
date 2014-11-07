#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 20
#define MAX_N 100

using namespace std;

struct pora {
  string vardai;
  int balai;
  bool operator<(pora kita) const {
    return balai < kita.balai;
  }
};

int skaiciuok(int balai[], int dydis) {
  int min = balai[0];
  int max = balai[0];
  int suma = 0;
  for (int i = 0; i < dydis; i++) {
    if (balai[i] < min) min = balai[i];
    if (balai[i] > max) max = balai[i];
    suma += balai[i];
  }
  return suma - min - max;
}

void skaityk(pora poros[], int &n) {
  ifstream uzduotis(IVESTIS);
  int k, m;
  uzduotis >> n >> k >> m;
  for (int i = 0; i < n; i++) {
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apdorotas[ILGIS + 1];
    memcpy(apdorotas, &c[1], ILGIS);
    apdorotas[ILGIS] = '\0';
    string vardai(apdorotas);
    pora sokejai;
    sokejai.vardai = vardai;
    int technika[k];
    for (int j = 0; j < k; j++) uzduotis >> technika[j];
    int artistiskumas[m];
    for (int j = 0; j < m; j++) uzduotis >> artistiskumas[j];
    sokejai.balai = skaiciuok(technika, k) + skaiciuok(artistiskumas, m);
    poros[i] = sokejai;
  }
  uzduotis.close();
}

void swap(pora poros[], int a, int b) {
  pora temp = poros[a];
  poros[a] = poros[b];
  poros[b] = temp;
}

void bubble(pora poros[], int n) {
  bool buvo_swapas;
  do {
    buvo_swapas = false;
    for (int i = 1; i < n; i++) {
      if (poros[i - 1] < poros[i]) {
        swap(poros, i, i - 1);
        buvo_swapas = true;
      }
    }
  } while (buvo_swapas);
}

int main() {
  pora poros[MAX_N];
  int n;
  skaityk(poros, n);
  bubble(poros, n);
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < n; i++) rezultatai << poros[i].vardai << ' '
                                         << poros[i].balai << endl;
  rezultatai.close();
  return 0;
}

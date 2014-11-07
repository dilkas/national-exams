#include <fstream>
#include <string.h>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 20
#define MAX_N 100

using namespace std;

struct sokejai {
  string vardai;
  int balai;
  bool operator<(sokejai kiti) const {
    return balai > kiti.balai;
  }
};

void swap(sokejai poros[], int a, int b) {
  sokejai pora = poros[a];
  poros[a] = poros[b];
  poros[b] = pora;
}

void bubble(sokejai poros[], int dydis) {
  bool buvo_swapas;
  do {
    buvo_swapas = false;
    for (int i = 1; i < dydis; i++) {
      if (poros[i] < poros[i - 1]) {
        swap(poros, i - 1, i);
        buvo_swapas = true;
      }
    }
  } while(buvo_swapas);
}

int skaiciuok(int balai[], int dydis) {
  int suma = 0;
  int min_i = 0;
  int max_i = 0;
  for (int i = 0; i < dydis; i++) {
    suma += balai[i];
    if (balai[i] < balai[min_i]) min_i = i;
    if (balai[i] > balai[max_i]) max_i = i;
  }
  return suma - balai[min_i] - balai[max_i];
}

void skaityk(sokejai poros[], int &n) {
  ifstream uzduotis(IVESTIS);
  int k;
  uzduotis >> n >> k;
  for (int i = 0; i < n; i++) {
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apdorotas[ILGIS + 1];
    memcpy(apdorotas, &c[1], ILGIS);
    apdorotas[ILGIS] = '\0';
    string vardai(apdorotas);
    sokejai pora;
    pora.vardai = vardai;
    int technika[k];
    for (int j = 0; j < k; j++) uzduotis >> technika[j];
    int artistiskumas[k];
    for (int j = 0; j < k; j++) uzduotis >> artistiskumas[j];
    pora.balai = skaiciuok(technika, k) + skaiciuok(artistiskumas, k);
    poros[i] = pora;
  }
  uzduotis.close();
}

int main() {
  sokejai poros[MAX_N];
  int n;
  skaityk(poros, n);
  bubble(poros, n);
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < n; i++) rezultatai << poros[i].vardai << ' '
                                         << poros[i].balai << endl;
  rezultatai.close();
  return 0;
}

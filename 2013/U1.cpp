#include <fstream>
#include <string.h>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"
#define ILGIS 10
#define MAX_N 50

using namespace std;

struct imone {
  string pavadinimas;
  int x, y;
};

void skaityk(imone siuntos[], int &n, int &m) {
  ifstream uzduotis(IVESTIS);
  uzduotis >> n >> m;
  for (int i = 0; i < n; i++) {
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apdorotas[ILGIS + 1];
    memcpy(apdorotas, &c[1], ILGIS);
    apdorotas[ILGIS] = '\0';
    string pavadinimas(apdorotas);
    imone nauja;
    nauja.pavadinimas = pavadinimas;
    uzduotis >> nauja.x >> nauja.y;
    siuntos[i] = nauja;
  }
  uzduotis.close();
}

int abs(int x) {
  if (x < 0) return -x;
  return x;
}

int atstumas(imone siunta) {
  return 2 * (abs(siunta.x) + abs(siunta.y));
}

void isvesk(int imones, int km, string pavadinimas) {
  ofstream rezultatai(ISVESTIS);
  rezultatai << imones << ' ' << km << ' ' << pavadinimas << endl;
  rezultatai.close();
}

int main() {
  imone siuntos[MAX_N];
  int n, m;
  skaityk(siuntos, n, m);
  int imones = 0;
  int km = 0;
  string pavadinimas;
  for (int i = 0; i < n; i++) {
    int papildomi_km = atstumas(siuntos[i]);
    if (km + papildomi_km > m) break;
    imones++;
    km += papildomi_km;
    pavadinimas = siuntos[i].pavadinimas;
  }
  isvesk(imones, km, pavadinimas);
  return 0;
}

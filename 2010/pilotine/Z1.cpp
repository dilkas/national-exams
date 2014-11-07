#include <fstream>

#define IVESTIS "Z1.txt"
#define ISVESTIS "Z1rez.txt"

using namespace std;

int min(int a, int b) {
  if (a < b) return a;
  return b;
}

// Skaiciuojam sudetingiau, kad veiktu atvejui 1, 1, 1,..
void skaiciuok(int pirkejai[], int &N1, int &N2, int N, int &kiek_pirkeju,
               int &kiek_kg) {
  kiek_pirkeju = 0;
  for (int i = 0; i < N; i++) {
    int kiek_po_2 = min(pirkejai[i] / 2, N2);
    int kiek_po_1 = min(pirkejai[i] - kiek_po_2 * 2, N1);
    N2 -= kiek_po_2;
    N1 -= kiek_po_1;
    int kiek_kg_naujas = kiek_po_1 + 2 * kiek_po_2;
    if (kiek_kg_naujas != 0) {
      kiek_pirkeju++;
      kiek_kg = kiek_kg_naujas;
    }
    if (N2 == 0 && N1 == 0) break;
  }
}

int main() {
  int N1, N2, N;
  ifstream uzduotis(IVESTIS);
  uzduotis >> N1 >> N2 >> N;
  int pirkejai[N];
  for (int i = 0; i < N; i++) uzduotis >> pirkejai[i];
  uzduotis.close();
  int kiek_pirkeju, kiek_kg;
  int like_N1 = N1;
  int like_N2 = N2;
  skaiciuok(pirkejai, like_N1, like_N2, N, kiek_pirkeju, kiek_kg);
  ofstream rezultatai(ISVESTIS);
  rezultatai << N1 - like_N1 << ' '<< N2 - like_N2 << endl << kiek_pirkeju
             << endl << kiek_kg << endl;
  rezultatai.close();
  return 0;
}

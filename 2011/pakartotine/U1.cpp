#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"
#define MAX_DYDIS 50

using namespace std;

void skaityk(int duomenys[2][2][MAX_DYDIS]) {
  ifstream uzduotis(IVESTIS);
  int n;
  uzduotis >> n;
  for (int i = 0; i < n; i++) {
    int lytis, puse, dydis;
    uzduotis >> lytis >> puse >> dydis;
    duomenys[lytis - 3][puse - 1][dydis - 1]++;
  }
  uzduotis.close();
}

void skaiciuok(int duomenys[2][2][MAX_DYDIS], int kiekiai[MAX_DYDIS][2]) {
  for (int i = 0; i < MAX_DYDIS; i++) {
    for (int j = 0; j < 2; j++)
      kiekiai[i][j] = min(duomenys[j][0][i], duomenys[j][1][i]);
  }
}

int main() {
  int duomenys[2][2][MAX_DYDIS];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < MAX_DYDIS; k++) duomenys[i][j][k] = 0;
    }
  }
  skaityk(duomenys);
  int kiekiai[MAX_DYDIS][2];
  skaiciuok(duomenys, kiekiai);
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < MAX_DYDIS; i++) {
    if (kiekiai[i][0] > 0 || kiekiai[i][1] > 0)
      rezultatai << i + 1 << ' ' << kiekiai[i][1] << ' ' << kiekiai[i][0] << endl;
  }
  rezultatai.close();
  return 0;
}

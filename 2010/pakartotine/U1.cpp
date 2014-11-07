#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"
#define FIGURU_RUSIU_SKAICIUS 6

using namespace std;

const int komplektas[] = {8, 2, 2, 2, 1, 1};

bool galima(int figuros[]) {
  for (int i = 0; i < FIGURU_RUSIU_SKAICIUS; i++) {
    if (figuros[i] < komplektas[i]) return false;
  }
  return true;
}

int kiek(int figuros[]) {
  int kiek = 0;
  while (galima(figuros)) {
    kiek++;
    for (int i = 0; i < FIGURU_RUSIU_SKAICIUS; i++)
      figuros[i] -= komplektas[i];
  }
  return kiek;
}

int main() {
  ifstream uzduotis(IVESTIS);
  int N;
  uzduotis >> N;
  int figuros[FIGURU_RUSIU_SKAICIUS];
  for (int i = 0; i < FIGURU_RUSIU_SKAICIUS; i++) figuros[i] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < FIGURU_RUSIU_SKAICIUS; j++) {
      int truksta;
      uzduotis >> truksta;
      figuros[j] +=komplektas[j] - truksta;
    }
  }
  uzduotis.close();
  ofstream rezultatai(ISVESTIS);
  rezultatai << kiek(figuros) << endl;
  rezultatai.close();
  return 0;
}

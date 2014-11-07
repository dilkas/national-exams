#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"

using namespace std;

const int komplektas[6] = {8, 2, 2, 2, 1, 1};

bool galim(int turim[]) {
  for (int i = 0; i < 6; i++) {
    if (turim[i] < komplektas[i]) return false;
  }
  return true;
}

int kiek(int turim[]) {
  int ats = 0;
  while (galim(turim)) {
    for (int i = 0; i < 6; i++) turim[i] -= komplektas[i];
    ats++;
  }
  return ats;
}

int main() {
  int turim[6];
  for (int i = 0; i < 6; i++) turim[i] = 0;
  ifstream uzduotis(IVESTIS);
  int N;
  uzduotis >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 6; j++) {
      int figuros;
      uzduotis >> figuros;
      turim[j] += figuros;
    }
  }
  uzduotis.close();
  ofstream rezultatai(ISVESTIS);
  rezultatai << kiek(turim) << endl;
  rezultatai.close();
  return 0;
}

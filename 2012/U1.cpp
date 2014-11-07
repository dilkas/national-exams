#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1Rez.txt"
#define MAX_K 99
#define MIN_K 4
#define KIEK_K MAX_K - MIN_K + 1

using namespace std;

void skaityk(int aikstele[], int suolelis[], bool startinis[]) {
  ifstream uzduotis(IVESTIS);
  int n;
  uzduotis >> n;
  for (int i = 0; i < n; i++) {
    int k, t;
    uzduotis >> k >> t;
    k -= MIN_K;
    for (int j = 0; j < t; j++) {
      int minutes;
      uzduotis >> minutes;
      if (minutes > 0) {
        aikstele[k] += minutes;
        if (j == 0) startinis[k] = true;
      }
      else suolelis[k] -= minutes;
    }
  }
  uzduotis.close();
}

int max(int minutes[]) {
  int max = 0;
  for (int k = 0; k < KIEK_K; k++) {
    if (minutes[k] > minutes[max]) max = k;
  }
  return max;
}

int main() {
  int aikstele[KIEK_K];
  int suolelis[KIEK_K];
  bool startinis[KIEK_K];
  for (int k = 0; k < KIEK_K; k++) {
    aikstele[k] = 0;
    suolelis[k] = 0;
    startinis[k] = false;
  }
  skaityk(aikstele, suolelis, startinis);
  ofstream rezultatai(ISVESTIS);
  for (int k = 0; k < KIEK_K; k++) {
    if (startinis[k]) rezultatai << k + MIN_K << ' ';
  }
  int max_aikstele = max(aikstele);
  int max_suolelis = max(suolelis);
  rezultatai << endl << max_aikstele + MIN_K << ' ' << aikstele[max_aikstele]
             << endl << max_suolelis + MIN_K << ' ' << suolelis[max_suolelis]
             << endl;
  rezultatai.close();
  return 0;
}

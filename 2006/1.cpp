#include <fstream>
#include <math.h>

using namespace std;

int main () {
  ifstream fin("Duom1.txt");
  ofstream fout("Rez1.txt");
  int n;
  fin >> n;
  float total = 0;
  for (int i = 0; i < n; i++) {
    int k;
    fin >> k;
    float sum = 0;
    for (int j = 0; j < k; j++) {
      int t;
      fin >> t;
      sum += 1. / t;
    }
    total += 1. / sum;
  }
  fout << round(100 * total)/100 << endl;
  fin.close();
  fout.close();
  return 0;
}

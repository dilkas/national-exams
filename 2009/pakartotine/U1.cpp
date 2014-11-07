#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"

using namespace std;

int viso(int pinigai[], int k) {
  int suma = 0;
  for (int i = 0; i < k; i++) suma += pinigai[i];
  return suma;
}

int main() {
  ifstream uzduotis(IVESTIS);
  int k, n;
  uzduotis >> k;
  int pinigai[k];
  for (int i = 0; i < k; i++) uzduotis >> pinigai[i];
  uzduotis >> n;
  int nominalai[n];
  for (int i = 0; i < n; i++) uzduotis >> nominalai[i];
  uzduotis.close();

  ofstream rezultatai(ISVESTIS);
  int suma = viso(pinigai, k);
  rezultatai << suma << endl;
  int monetu_skaicius = 0;
  for (int i = 0; i < n; i++) {
    int kiek = suma / nominalai[i];
    suma -= kiek * nominalai[i];
    rezultatai << nominalai[i] << ' ' << kiek << endl;
    monetu_skaicius += kiek;
  }
  rezultatai << monetu_skaicius << endl << suma << endl;
  rezultatai.close();
  return 0;
}

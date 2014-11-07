#include <fstream>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"
#define VYRISKA 3
#define MOTERISKA 4
#define KAIRE 1
#define DESINE 2
#define MAX_N 100

using namespace std;

void paskirk(int puse, int dydis, int kaire[], int desine[], int &ik, int &id) {
  if (puse == KAIRE) kaire[ik++] = dydis;
  else desine[id++] = dydis;
}

void skaityk(int vyriska_kaire[], int vyriska_desine[], int moteriska_kaire[],
             int moteriska_desine[], int &ivk, int &ivd, int &imk, int &imd) {
  ifstream uzduotis(IVESTIS);
  int n;
  uzduotis >> n;
  for (int i = 0; i < n; i++) {
    int lytis, puse, dydis;
    uzduotis >> lytis >> puse >> dydis;
    if (lytis == VYRISKA)
      paskirk(puse, dydis, vyriska_kaire, vyriska_desine, ivk, ivd);
    else
      paskirk(puse, dydis, moteriska_kaire, moteriska_desine, imk, imd);
  }
  uzduotis.close();
}

void swap(int masyvas[], int a, int b) {
  int temp = masyvas[a];
  masyvas[a] = masyvas[b];
  masyvas[b] = temp;
}

int dalink(int masyvas[], int kairysis, int desinysis, int pivoto_indeksas) {
  int pivoto_reiksme = masyvas[pivoto_indeksas];
  swap(masyvas, pivoto_indeksas, desinysis);
  int indeksas = kairysis;
  for (int i = kairysis; i < desinysis; i++) {
    if (masyvas[i] <= pivoto_reiksme) swap(masyvas, i, indeksas++);
  }
  swap(masyvas, indeksas, desinysis);
  return indeksas;
}

void quicksort(int masyvas[], int kairysis, int desinysis) {
  if (kairysis < desinysis) {
    int pivoto_indeksas = (kairysis + desinysis) / 2;
    int pivoto_naujas_indeksas = dalink(masyvas, kairysis, desinysis,
                                        pivoto_indeksas);
    quicksort(masyvas, kairysis, pivoto_naujas_indeksas - 1);
    quicksort(masyvas, pivoto_naujas_indeksas + 1, desinysis);
  }
}

int kiek_poru(int kaire[], int desine[], int ik, int id) {
  int j = 0;
  int kiek = 0;
  for (int i = 0; i < ik; i++) {
    while (kaire[i] > desine[j]) j++;
    if (kaire[i] == desine[j]) {
      kiek++;
      kaire[i] = 0;
      desine[j] = 0;
      if (++j == id) break;
    }
  }
  return kiek;
}

int kiek(int pirstines[], int dydis) {
  int kiek = 0;
  for (int i = 0; i < dydis; i++) {
    if (pirstines[i] != 0) kiek++;
  }
  return kiek;
}

int kiek_atliekamu(int kaire[], int desine[], int ik, int id) {
  return kiek(kaire, ik) + kiek(desine, id);
}

int main() {
  int vyriska_kaire[MAX_N];
  int vyriska_desine[MAX_N];
  int moteriska_kaire[MAX_N];
  int moteriska_desine[MAX_N];
  int ivk = 0;
  int ivd = 0;
  int imk = 0;
  int imd = 0;
  skaityk(vyriska_kaire, vyriska_desine, moteriska_kaire, moteriska_desine,
          ivk, ivd, imk, imd);
  quicksort(vyriska_kaire, 0, ivk - 1);
  quicksort(vyriska_desine, 0, ivd - 1);
  quicksort(moteriska_kaire, 0, imk - 1);
  quicksort(moteriska_desine, 0, imd - 1);
  ofstream rezultatai(ISVESTIS);
  rezultatai << kiek_poru(moteriska_kaire, moteriska_desine, imk, imd) << endl
             << kiek_poru(vyriska_kaire, vyriska_desine, ivk, ivd) << endl;
  rezultatai << kiek_atliekamu(moteriska_kaire, moteriska_desine, imk, imd)
             << endl
             << kiek_atliekamu(vyriska_kaire, vyriska_desine, ivk, ivd)
             << endl;
  rezultatai.close();
  return 0;
}

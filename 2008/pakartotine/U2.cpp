#include <fstream>
#include <string.h>

#define MAKSIMALUS_N 100
#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 25
#define DIENU_SKAICIUS_METUOSE 365
#define MENESIU_SKAICIUS_METUOSE 12

using namespace std;

struct asmuo {
  string vardas;
  int gimimo_metai, gimimo_menuo, gimimo_diena,
    mirties_metai, mirties_menuo, mirties_diena;
};

void skaityk(int &N, asmuo zmones[]) {
  ifstream uzduotis(IVESTIS);
  uzduotis >> N;
  for (int i = 0; i < N; i++) {
    asmuo zmogus;
    char c[ILGIS + 1];
    uzduotis.read(c, ILGIS + 1);
    char apkarpytas[ILGIS + 1];
    memcpy(apkarpytas, &c[1], ILGIS);
    apkarpytas[ILGIS] = '\0';
    string vardas(apkarpytas);
    zmogus.vardas = vardas;
    uzduotis >> zmogus.gimimo_metai >> zmogus.gimimo_menuo
             >>zmogus.gimimo_diena >> zmogus.mirties_metai
             >> zmogus.mirties_menuo >> zmogus.mirties_diena;
    zmones[i] = zmogus;
  }
  uzduotis.close();
}

int skaiciuok(asmuo zmogus) {
  int dienu_skaicius[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int metai = zmogus.gimimo_metai;
  int menuo = zmogus.gimimo_menuo;
  int diena = zmogus.gimimo_diena;
  int skaicius = 0;

  // Prasukam metus
  if (menuo < zmogus.mirties_menuo || (menuo == zmogus.mirties_menuo &&
                                       diena <= zmogus.mirties_diena)) {
    skaicius += (zmogus.mirties_metai - metai) * DIENU_SKAICIUS_METUOSE;
    metai = zmogus.mirties_metai;
  } else {
    skaicius += (zmogus.mirties_metai - metai - 1) * DIENU_SKAICIUS_METUOSE;
    metai = zmogus.mirties_metai - 1;
  }

  // Einam i pirma diena, kad galetume saugiai prasukinet menesius
  if (menuo < zmogus.mirties_menuo || metai < zmogus.mirties_metai) {
    skaicius += dienu_skaicius[menuo++ - 1] - diena + 1;
    diena = 1;
  }

  // Prasukam menesius
  while (menuo < zmogus.mirties_menuo || metai < zmogus.mirties_metai) {
    skaicius += dienu_skaicius[menuo - 1];
    if (++menuo > MENESIU_SKAICIUS_METUOSE) {
      metai++;
      menuo = 1;
    }
  }

  // Prasukam dienas
  skaicius += zmogus.mirties_diena - diena;
  return skaicius;
}

void spausdink(int N, asmuo zmones[]) {
  ofstream rezultatai(ISVESTIS);
  for (int i = 0; i < N; i++) {
    rezultatai << zmones[i].vardas << zmones[i].gimimo_metai << ' '
               << zmones[i].gimimo_menuo << ' ' << zmones[i].gimimo_diena
               << ' ' << zmones[i].mirties_metai << ' '
               << zmones[i].mirties_menuo << ' ' << zmones[i].mirties_diena
               << ' ' << skaiciuok(zmones[i]) << endl;
  }
  rezultatai.close();
}

int main() {
  int N;
  asmuo zmones[MAKSIMALUS_N];
  skaityk(N, zmones);
  spausdink(N, zmones);
  return 0;
}

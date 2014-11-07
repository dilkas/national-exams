#include <fstream>

#define IVESTIS "U2.txt"
#define ISVESTIS "U2rez.txt"
#define ILGIS 13

using namespace std;

struct miestas {
  string apskritis;
  int gyventojai;
};

struct apskritis {
  string pavadinimas;
  int maziausias, visas;
  bool operator<(apskritis kita) const {
    if (maziausias != kita.maziausias) return maziausias > kita.maziausias;
    return pavadinimas > kita.pavadinimas;
  }
};

int main() {
  ifstream uzduotis(IVESTIS);
  int k;
  uzduotis >> k;
  miestas miestai[k];
  apskritis apskritys[k];
  int apskriciu_kiekis = 0;
  for (int i = 0; i < k; i++) {
    miestas naujas;
    string pavadinimas;
    uzduotis >> pavadinimas >> naujas.apskritis >> naujas.gyventojai;
    miestai[i] = naujas;
  }
  uzduotis.close();
  for (int i = 0; i < k; i++) {
    bool radom = false;
    for (int j = 0; j < apskriciu_kiekis; j++) {
      if (miestai[i].apskritis == apskritys[j].pavadinimas) {
        apskritys[j].visas += miestai[i].gyventojai;
        if (miestai[i].gyventojai < apskritys[j].maziausias)
          apskritys[j].maziausias = miestai[i].gyventojai;
        radom = true;
        break;
      }
    }
    if (!radom) {
      apskritis nauja;
      nauja.pavadinimas = miestai[i].apskritis;
      nauja.maziausias = miestai[i].gyventojai;
      nauja.visas = miestai[i].gyventojai;
      apskritys[apskriciu_kiekis++] = nauja;
    }
  }
  bool buvo_swapas;
  do {
    buvo_swapas = false;
    for (int i = 1; i < apskriciu_kiekis; i++) {
      if (apskritys[i - 1] < apskritys[i]) {
        apskritis temp = apskritys[i - 1];
        apskritys[i - 1] = apskritys[i];
        apskritys[i] = temp;
        buvo_swapas = true;
      }
    }
  } while(buvo_swapas);
  ofstream rezultatai(ISVESTIS);
  rezultatai << apskriciu_kiekis << endl;
  for (int i = 0; i < apskriciu_kiekis; i++) {
    rezultatai << apskritys[i].pavadinimas;
    for (int j = 0; j <= ILGIS - apskritys[i].pavadinimas.length(); j++)
      rezultatai << ' ';
    rezultatai << apskritys[i].maziausias << ' ' << apskritys[i].visas
               << endl;
  }
  rezultatai.close();
  return 0;
}

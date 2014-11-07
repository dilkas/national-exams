#include <fstream>
#include <iomanip>

#define IVESTIS "U1.txt"
#define ISVESTIS "U1rez.txt"
#define MAKSIMALUS_N 100
#define ILGIS 6

using namespace std;

bool egzistuoja[MAKSIMALUS_N];
int suma[MAKSIMALUS_N];
int iejusiu_suma;

ofstream rezultatai;

void skaityk() {
  ifstream uzduotis(IVESTIS);
  int m;
  uzduotis >> m;
  for (int skaiciuoklis = 0; skaiciuoklis < m; skaiciuoklis++) {
    int stotis, diena, ieje, iseje;
    uzduotis >> stotis >> diena >> ieje >> iseje;
    egzistuoja[stotis - 1] = true;
    suma[stotis - 1] += ieje + iseje;
    iejusiu_suma += ieje;
  }
  uzduotis.close();
}

void isvesti(int (*ka_isvesti)(int)) {
  for (int stotis = 0; stotis < MAKSIMALUS_N; stotis++) {
    if (egzistuoja[stotis]) {
      rezultatai << setw(ILGIS) << ka_isvesti(stotis);
    }
  }
  rezultatai << endl;
}

int pirmas_padejejas(int stotis) {
  return stotis + 1;
}

int antras_padejejas(int stotis) {
  return suma[stotis];
}

void pirma() {
  isvesti(pirmas_padejejas);
}

void antra() {
  isvesti(antras_padejejas);
}

int rask() {
  int maksimalus_indeksas = 0;
  for (int indeksas = 0; indeksas < MAKSIMALUS_N; indeksas++) {
    if (suma[indeksas] > suma[maksimalus_indeksas])
      maksimalus_indeksas = indeksas;
  }
  return maksimalus_indeksas + 1;
}

int main() {
  for (int indeksas = 0; indeksas < MAKSIMALUS_N; indeksas++) {
    egzistuoja[indeksas] = false;
    suma[indeksas] = 0;
  }
  iejusiu_suma = 0;
  skaityk();
  rezultatai.open(ISVESTIS);
  pirma();
  antra();
  rezultatai << setw(ILGIS) << rask() << endl << setw(ILGIS) << iejusiu_suma << endl;
  rezultatai.close();
  return 0;
}

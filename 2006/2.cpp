#include <fstream>
#include <math.h>

#define MAKSIMALUS_STOTELIU_SKAICIUS 100
#define MINUCIU_VALANDOJE 60
#define PAVADINIMO_ILGIS 15

using namespace std;

struct stotele {
  string pavadinimas;
  float atstumas;
};

struct stotele_su_laiku {
  string pavadinimas;
  int valanda, minute;
};

int marsruto_stoteliu_skaicius, isvykimo_is_Vilniaus_valanda,
  isvykimo_is_Vilniaus_minute;
float vidutinis_greitis;
stotele duomenys[MAKSIMALUS_STOTELIU_SKAICIUS];
stotele_su_laiku rezultatai[MAKSIMALUS_STOTELIU_SKAICIUS];

int Laikas(float atstumas, float greitis) {
  return round(atstumas / greitis * 60);
}

void skaityk() {
  ifstream duomenu_failas("Duom2.txt");
  duomenu_failas >> marsruto_stoteliu_skaicius >> vidutinis_greitis >>
    isvykimo_is_Vilniaus_valanda >> isvykimo_is_Vilniaus_minute;
  for (int indeksas = 0; indeksas < marsruto_stoteliu_skaicius; indeksas++) {
    stotele konkreti_stotele;
    duomenu_failas >> konkreti_stotele.pavadinimas >> konkreti_stotele.atstumas;
    duomenys[indeksas] = konkreti_stotele;
  }
  duomenu_failas.close();
}

void skaiciuok() {
  for (int indeksas = 0; indeksas < marsruto_stoteliu_skaicius; indeksas++) {
    stotele_su_laiku konkreti_stotele;
    konkreti_stotele.pavadinimas = duomenys[indeksas].pavadinimas;
    if (indeksas == 0) {
      konkreti_stotele.valanda = isvykimo_is_Vilniaus_valanda;
      konkreti_stotele.minute = isvykimo_is_Vilniaus_minute;
    } else {
      konkreti_stotele.valanda = rezultatai[indeksas - 1].valanda;
      konkreti_stotele.minute = rezultatai[indeksas - 1].minute;
    }
    konkreti_stotele.minute += Laikas(duomenys[indeksas].atstumas, vidutinis_greitis);
    while (konkreti_stotele.minute >= MINUCIU_VALANDOJE) {
      konkreti_stotele.valanda++;
      konkreti_stotele.minute -= 60;
    }
    rezultatai[indeksas] = konkreti_stotele;
  }
}

void irasyk_i_faila() {
  ofstream rezultatu_failas("Rez2.txt");
  for (int indeksas = 0; indeksas < marsruto_stoteliu_skaicius; indeksas++) {
    rezultatu_failas << rezultatai[indeksas].pavadinimas;
    for (int tarpas = 0; tarpas < PAVADINIMO_ILGIS -
  rezultatai[indeksas].pavadinimas.length(); tarpas ++)
      rezultatu_failas << ' ';
    rezultatu_failas << rezultatai[indeksas].valanda << " val. "
                     << rezultatai[indeksas].minute << " min." << endl;
  }
  rezultatu_failas.close();
}

int main() {
  skaityk();
  skaiciuok();
  irasyk_i_faila();
  return 0;
}

#include <string.h>
#include "GazDeviGezegen.h"

Gezegen GazDeviGezegen_Olustur(const char* ad, int gunSaat, Zaman tarih) {
    Gezegen g;
    strcpy(g.ad, ad);
    g.tur = 1;
    g.gunSaat = gunSaat;
    g.tarih = tarih;
    g.yaslanmaCarpani = 0.1;
    g.kisiSayisi = 0;
    return g;
}

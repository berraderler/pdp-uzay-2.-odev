#include <string.h>
#include "CuceGezegen.h"

Gezegen CuceGezegen_Olustur(const char* ad, int gunSaat, Zaman tarih) {
    Gezegen g;
    strcpy(g.ad, ad);
    g.tur = 3;
    g.gunSaat = gunSaat;
    g.tarih = tarih;
    g.yaslanmaCarpani = 0.01;
    g.kisiSayisi = 0;
    return g;
}

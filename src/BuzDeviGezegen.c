#include <string.h>
#include "BuzDeviGezegen.h"

Gezegen BuzDeviGezegen_Olustur(const char* ad, int gunSaat, Zaman tarih) {
    Gezegen g;
    strcpy(g.ad, ad);
    g.tur = 2;
    g.gunSaat = gunSaat;
    g.tarih = tarih;
    g.yaslanmaCarpani = 0.5;
    g.kisiSayisi = 0;
    return g;
}

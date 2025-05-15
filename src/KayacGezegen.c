#include <string.h>
#include "KayacGezegen.h"

Gezegen KayacGezegen_Olustur(const char* ad, int gunSaat, Zaman tarih) {
    Gezegen g;
    strcpy(g.ad, ad);
    g.tur = 0;
    g.gunSaat = gunSaat;
    g.tarih = tarih;
    g.yaslanmaCarpani = 1.0;
    g.kisiSayisi = 0;
    return g;
}

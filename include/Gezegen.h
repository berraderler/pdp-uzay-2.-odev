#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "Zaman.h"
#include <time.h>

typedef struct Gezegen {
    char ad[10];
    int tur;
    int gunSaat;
    Zaman tarih;
    double yaslanmaCarpani;
    int kisiSayisi;
    int gununKacSaatOldugu;
    char isim[50];
    int nufus;
    
} Gezegen;

// Fonksiyon prototipleri:
Gezegen* Gezegen_olustur(char* isim, int gununKacSaatOldugu, char* baslangicTarihi);
void saatIlerle(Gezegen* g);
void nufusArtir(Gezegen* g, int artis);
void nufusAzalt(Gezegen* g, int azalis);
char* getTarihStr(Gezegen* g);
char* tahminiVarisTarihi(Gezegen* cikis, struct tm cikisTarihi, int kalanSaat, Gezegen* varis);

#endif

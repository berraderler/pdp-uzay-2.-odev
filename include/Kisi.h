#ifndef KISI_H
#define KISI_H

#include <stdbool.h>

typedef struct {
    char isim[50];
    int yas;
    double kalanOmur;
    char uzayAraci[10];
    int yasiyor;
} Kisi;

// Fonksiyon prototipleri:
Kisi kisiOlustur(const char* isim, int yas, int kalanOmur, const char* uzayAraciAdi);
const char* getIsim(Kisi* k);
int getKalanOmur(Kisi* k);
const char* getUzayAraciAdi(Kisi* k);
bool isHayatta(Kisi* k);
void saatGecir_Kisi(Kisi* k);

#endif

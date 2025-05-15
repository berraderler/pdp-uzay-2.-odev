/*
*
* @ Müberra AKPINAR 
* @B231210086 
* @24.04.2025
*
*  Bu yapı, bir kişinin ismini, kalan ömrünü, uzay aracı adını ve hayatta olup olmadığını tutar.
*  Ayrıca, zaman geçtikçe kişinin ömrünü azaltır ve hayatta olup olmadığını günceller.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char isim[50];
    int kalanOmur;
    char uzayAraciAdi[50];
    bool hayatta;
} Kisi;

// Kisi oluşturucu (Constructor karşılığı)
Kisi kisiOlustur(const char* isim, int yas, int kalanOmur, const char* uzayAraciAdi) {
    Kisi k;
    strncpy(k.isim, isim, sizeof(k.isim));
    k.kalanOmur = kalanOmur;
    strncpy(k.uzayAraciAdi, uzayAraciAdi, sizeof(k.uzayAraciAdi));
    k.hayatta = kalanOmur > 0 ? true : false;
    return k;
}

// Getter benzerleri
const char* getIsim(Kisi* k) {
    return k->isim;
}

int getKalanOmur(Kisi* k) {
    return k->kalanOmur;
}

const char* getUzayAraciAdi(Kisi* k) {
    return k->uzayAraciAdi;
}

bool isHayatta(Kisi* k) {
    return k->hayatta;
}

// Bir saat geçir (kalan ömrü azaltır)
void saatGecir_Kisi(Kisi* k) {
    if (k->kalanOmur > 0) {
        k->kalanOmur--;
        if (k->kalanOmur == 0) {
            k->hayatta = false;
        }
    }
}

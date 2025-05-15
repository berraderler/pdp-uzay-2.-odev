#ifndef UZAY_ARACI_H
#define UZAY_ARACI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gezegen.h"
#include "Kisi.h"
#include "Zaman.h"

typedef struct {
    char adi[50];
    char cikis[50];
    char varis[50];
    int kalanSaat;
    int orijinalMesafeSaat;
    int imha;
    int vardi;
    int hareketEtti;
    Kisi** yolcular;
    int yolcuSayisi;

    Gezegen* cikisGezegeni;
    Gezegen* varisGezegeni;

    Zaman cikisTarihi;
    Zaman hedefeVarisTarihi;
    int hedefTarihHesaplandi;
} UzayAraci;

// Fonksiyon prototipleri
UzayAraci* UzayAraci_olustur(char* adi, char* cikis, char* varis, int mesafeSaat, Gezegen** gezegenler, int gezegenSayisi);
void kisiEkle(UzayAraci* u, Kisi* kisi);
void aracKalkti(UzayAraci* u);
void saatGecir(UzayAraci* u, int saat);
char* getDurum(UzayAraci* u);
void setCikisTarihi(UzayAraci* u, char* tarihStr);
void hesaplaHedefeVarisTarihi(UzayAraci* u);
char* getHedefeVarisTarihi(UzayAraci* u);

#endif

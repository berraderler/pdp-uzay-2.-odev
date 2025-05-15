#ifndef ZAMAN_H
#define ZAMAN_H
#include <time.h>

typedef struct {
    int gun;
    int ay;
    int yil;
    int saat;
    
} Zaman;

void zamaniBirSaatArtir(Zaman* z, int gunSaatSayisi);
int tarihKarsilastir(Zaman a, Zaman b);
Zaman tarihKopyala(Zaman z);
void zamaniYazdir(Zaman z);
int ayniTarihMi(Zaman a, Zaman b);


#endif

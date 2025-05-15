#ifndef GEZEGEN_H
#define GEZEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char isim[50];
    int nufus;
    struct tm tarih;
    int gununKacSaatOldugu;
    int saat;
} Gezegen;

Gezegen* Gezegen_olustur(char* isim, int gununKacSaatOldugu, char* baslangicTarihi) {
    Gezegen* g = (Gezegen*)malloc(sizeof(Gezegen));
    strcpy(g->isim, isim);
    g->nufus = 0;
    g->saat = 0;
    g->gununKacSaatOldugu = gununKacSaatOldugu;

    int gun, ay, yil;
    sscanf(baslangicTarihi, "%d.%d.%d", &gun, &ay, &yil);

    g->tarih.tm_mday = gun;
    g->tarih.tm_mon = ay - 1;
    g->tarih.tm_year = yil - 1900;
    g->tarih.tm_hour = 0;
    g->tarih.tm_min = 0;
    g->tarih.tm_sec = 0;
    mktime(&(g->tarih));

    return g;
}

void saatIlerle(Gezegen* g) {
    g->saat++;
    if (g->saat >= g->gununKacSaatOldugu) {
        g->saat = 0;
        g->tarih.tm_mday++;
        mktime(&(g->tarih));
    }
}

void nufusArtir(Gezegen* g, int artis) {
    g->nufus += artis;
}

void nufusAzalt(Gezegen* g, int azalis) {
    g->nufus -= azalis;
    if (g->nufus < 0)
        g->nufus = 0;
}

char* getTarihStr(Gezegen* g) {
    static char buf[11];
    strftime(buf, sizeof(buf), "%d.%m.%Y", &(g->tarih));
    return buf;
}

char* tahminiVarisTarihi(Gezegen* cikis, struct tm cikisTarihi, int kalanSaat, Gezegen* varis) {
    int gunlukSaatCikis = cikis->gununKacSaatOldugu;
    int gunlukSaatVaris = varis->gununKacSaatOldugu;

    int kacGun = kalanSaat / gunlukSaatCikis;
    if (kalanSaat % gunlukSaatCikis != 0) kacGun++;

    int toplamSaat = kacGun * gunlukSaatCikis;
    int kacGunVaris = toplamSaat / gunlukSaatVaris;
    if (toplamSaat % gunlukSaatVaris != 0) kacGunVaris++;

    cikisTarihi.tm_mday += kacGunVaris;
    mktime(&cikisTarihi);

    static char buf[11];
    strftime(buf, sizeof(buf), "%d.%m.%Y", &cikisTarihi);
    return buf;
}

#endif  
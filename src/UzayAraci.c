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

void hesaplaHedefeVarisTarihi(UzayAraci* u);

UzayAraci* UzayAraci_olustur(char* adi, char* cikis, char* varis, int mesafeSaat, Gezegen** gezegenler, int gezegenSayisi) {
    UzayAraci* u = (UzayAraci*)malloc(sizeof(UzayAraci));
    strcpy(u->adi, adi);
    strcpy(u->cikis, cikis);
    strcpy(u->varis, varis);
    u->kalanSaat = mesafeSaat;
   u->kalanSaat = u->orijinalMesafeSaat = mesafeSaat;
    u->imha = 0;
    u->vardi = 0;
    u->hareketEtti = 0;
    u->yolcular = NULL;
    u->yolcuSayisi = 0;
    u->hedefTarihHesaplandi = 0;
    u->cikisGezegeni = NULL;
    u->varisGezegeni = NULL;

    for (int i = 0; i < gezegenSayisi; i++) {
        if (strcmp(gezegenler[i]->isim, cikis) == 0)
            u->cikisGezegeni = gezegenler[i];
        if (strcmp(gezegenler[i]->isim, varis) == 0)
            u->varisGezegeni = gezegenler[i];
    }

    if (u->cikisGezegeni != NULL) {
        nufusArtir(u->cikisGezegeni, u->yolcuSayisi);
    }

    if (u->cikisGezegeni != NULL && u->varisGezegeni != NULL) {
        hesaplaHedefeVarisTarihi(u);
    }

    return u;
}

void kisiEkle(UzayAraci* u, Kisi* kisi) {
    u->yolcular = (Kisi**)realloc(u->yolcular, sizeof(Kisi*) * (u->yolcuSayisi + 1));
    u->yolcular[u->yolcuSayisi] = kisi;
    u->yolcuSayisi++;

    if (u->cikisGezegeni != NULL) {
        nufusArtir(u->cikisGezegeni, 1);
    }
}

void aracKalkti(UzayAraci* u) {
    if (u->hareketEtti == 0 && u->cikisGezegeni != NULL) {
        u->cikisGezegeni->nufus = 0;
        u->hareketEtti = 1;

        if (!u->hedefTarihHesaplandi && u->varisGezegeni != NULL) {
            hesaplaHedefeVarisTarihi(u);
        }
    }
}

void saatGecir(UzayAraci* u, int saat) {
    if (!u->imha && !u->vardi && u->hareketEtti) {
        u->kalanSaat -= saat;

        if (u->kalanSaat <= 0) {
            u->kalanSaat = 0;
            u->vardi = 1;

            int canliYolcuSayisi = 0;
            for (int i = 0; i < u->yolcuSayisi; i++) {
                if (isHayatta(u->yolcular[i]))
                    canliYolcuSayisi++;
            }

            if (u->varisGezegeni != NULL)
                nufusArtir(u->varisGezegeni, canliYolcuSayisi);
        }
    }
}

char* getDurum(UzayAraci* u) {
    if (!u->hareketEtti) return "BEKLIYOR";
    if (u->imha) return "IMHA";
    if (u->vardi) return "VARIS";
    return "YOLDA";
}

void setCikisTarihi(UzayAraci* u, char* tarihStr) {
    sscanf(tarihStr, "%d.%d.%d", &u->cikisTarihi.gun, &u->cikisTarihi.ay, &u->cikisTarihi.yil);
    u->cikisTarihi.saat = 0;
}

void hesaplaHedefeVarisTarihi(UzayAraci* u) {
    if (u->hedefTarihHesaplandi || u->varisGezegeni == NULL)
        return;

    int toplamSaat = u->orijinalMesafeSaat;
    int gunlukSaat = u->varisGezegeni->gununKacSaatOldugu;
    Zaman varis = tarihKopyala(u->cikisTarihi);

    for (int i = 0; i < toplamSaat; i++) {
        zamaniBirSaatArtir(&varis, gunlukSaat);
    }

    u->hedefeVarisTarihi = varis;
    u->hedefTarihHesaplandi = 1;
}

char* getHedefeVarisTarihi(UzayAraci* u) {
    if (u->imha) return "--";
    if (!u->hedefTarihHesaplandi) return "Hesaplaniyor";

    static char buf[11];
    snprintf(buf, sizeof(buf), "%02d.%02d.%04d",
             u->hedefeVarisTarihi.gun,
             u->hedefeVarisTarihi.ay,
             u->hedefeVarisTarihi.yil);
    return buf;
}

#endif
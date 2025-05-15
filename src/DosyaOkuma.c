#include <stdio.h>
#include <string.h>
#include "DosyaOkuma.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"
#include "UzayAraci.h"
#include "Zaman.h"
#include "Kisi.h"

// Kişi verilerini oku
int kisileriOku(const char* dosya, Kisi* kisiler) {
    FILE* f = fopen(dosya, "r");
    if (!f) return 0;

    int i = 0;
    while (fscanf(f, "%49[^#]#%d#%lf#%9s\n", 
                  kisiler[i].isim, &kisiler[i].yas, &kisiler[i].kalanOmur, kisiler[i].uzayAraci) == 4) {
        kisiler[i].yasiyor = 1;
        i++;
    }
    fclose(f);
    return i;
}

// Uzay araçlarını oku
int araclariOku(const char* dosya, UzayAraci* araclar) {
    FILE* f = fopen(dosya, "r");
    if (!f) return 0;

    int i = 0;
    int gun, ay, yil;

    while (fscanf(f, "%9[^#]#%9[^#]#%9[^#]#%d.%d.%d#%d\n",
                  araclar[i].adi, araclar[i].cikis, araclar[i].varis,
                  &gun, &ay, &yil, &araclar[i].orijinalMesafeSaat) == 7) {
        
        // Tarihi ata
        araclar[i].cikisTarihi.gun = gun;
        araclar[i].cikisTarihi.ay = ay;
        araclar[i].cikisTarihi.yil = yil;
        araclar[i].cikisTarihi.saat = 0;

        araclar[i].kalanSaat = araclar[i].orijinalMesafeSaat;
        araclar[i].imha = 0;
        i++;
    }
    fclose(f);
    return i;
}

// Gezegen verilerini oku
int gezegenleriOku(const char* dosya, Gezegen* gezegenler) {
    FILE* f = fopen(dosya, "r");
    if (!f) return 0;

    int i = 0;
    char ad[10];
    int tur, saat;
    Zaman tarih;

    while (fscanf(f, "%9[^#]#%d#%d#%d.%d.%d\n",
                  ad, &tur, &saat, &tarih.gun, &tarih.ay, &tarih.yil) == 6) {
        tarih.saat = 0;

        switch (tur) {
            case 0: gezegenler[i] = KayacGezegen_Olustur(ad, saat, tarih); break;
            case 1: gezegenler[i] = GazDeviGezegen_Olustur(ad, saat, tarih); break;
            case 2: gezegenler[i] = BuzDeviGezegen_Olustur(ad, saat, tarih); break;
            case 3: gezegenler[i] = CuceGezegen_Olustur(ad, saat, tarih); break;
            default: break; // Geçersiz tür varsa atla
        }
        i++;
    }
    fclose(f);
    return i;
}

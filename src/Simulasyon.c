 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "Simulasyon.h"
#include "Zaman.h"
#include "UzayAraci.h"

void ekraniTemizle() {
    system("cls");
}

Gezegen* gezegenBul(Gezegen* gezegenler, int sayi, const char* ad) {
    for (int i = 0; i < sayi; i++) {
        if (strcmp(gezegenler[i].ad, ad) == 0)
            return &gezegenler[i];
    }
    return NULL;
}

void simulasyonuBaslat(Kisi* kisiler, int kisiSayisi, UzayAraci* araclar, int aracSayisi, Gezegen* gezegenler, int gezegenSayisi) {
    int tumAraclarBitti = 0;

    while (!tumAraclarBitti) {
        ekraniTemizle();

        // 1. Her gezegenin tarihini 1 saat artır
        for (int i = 0; i < gezegenSayisi; i++) {
            zamaniBirSaatArtir(&gezegenler[i].tarih, gezegenler[i].gunSaat);
        }

        // 2. Her araç için kontrol et
        tumAraclarBitti = 1;
        for (int i = 0; i < aracSayisi; i++) {
            if (araclar[i].imha) continue;

            Gezegen* cikisG = gezegenBul(gezegenler, gezegenSayisi, araclar[i].cikis);
            if (ayniTarihMi(cikisG->tarih, araclar[i].cikisTarihi) && araclar[i].kalanSaat > 0) {
                araclar[i].kalanSaat--;
                if (araclar[i].kalanSaat == 0) {
                    // Varış zamanı geldi
                }
            }

            int yasayanVar = 0;
            for (int k = 0; k < kisiSayisi; k++) {
                if (strcmp(kisiler[k].uzayAraci, araclar[i].adi) == 0 && kisiler[k].yasiyor) {
                    yasayanVar = 1;
                    break;
                }
            }

            if (!yasayanVar) {
                araclar[i].imha = 1;
            } else if (araclar[i].kalanSaat > 0) {
                tumAraclarBitti = 0;
            }
        }

        // 3. Her kişi için yaşlanma uygula
        for (int i = 0; i < kisiSayisi; i++) {
            if (!kisiler[i].yasiyor) continue;

            for (int j = 0; j < gezegenSayisi; j++) {
                if (strcmp(kisiler[i].uzayAraci, "") != 0) {
                    for (int a = 0; a < aracSayisi; a++) {
                        if (strcmp(kisiler[i].uzayAraci, araclar[a].adi) == 0 && araclar[a].kalanSaat > 0) {
                            kisiler[i].kalanOmur -= 1;
                            break;
                        } else if (
                            strcmp(gezegenler[j].ad, araclar[a].varis) == 0 &&
                            araclar[a].kalanSaat == 0 &&
                            strcmp(kisiler[i].uzayAraci, araclar[a].adi) == 0
                        ) {
                            kisiler[i].kalanOmur -= (1.0 / gezegenler[j].yaslanmaCarpani);
                            break;
                        }
                    }
                }
            }

            if (kisiler[i].kalanOmur <= 0) {
                kisiler[i].yasiyor = 0;
            }
        }

        // 4. Ekrana yazdır
        printf("Gezegenler:\n\n");

        // Gezegen isimleri ve aralarına boşluk bırak
        for (int i = 0; i < gezegenSayisi; i++) {
            printf("--- %10s ---   ", gezegenler[i].ad);
        }
        printf("\n");

        // Tarihleri sadece gün.ay.yıl olarak yazdır (saat hariç)
        for (int i = 0; i < gezegenSayisi; i++) {
            printf("Tarih: %02d.%02d.%04d   ", 
                gezegenler[i].tarih.gun, 
                gezegenler[i].tarih.ay, 
                gezegenler[i].tarih.yil);
        }
        printf("\n");

        // Nüfus bilgisi
        for (int i = 0; i < gezegenSayisi; i++) {
            int nufus = 0;
            for (int k = 0; k < kisiSayisi; k++) {
                for (int a = 0; a < aracSayisi; a++) {
                    if (!kisiler[k].yasiyor) continue;
                    if (
                        strcmp(kisiler[k].uzayAraci, araclar[a].adi) == 0 &&
                        araclar[a].kalanSaat == 0 &&
                        strcmp(araclar[a].varis, gezegenler[i].ad) == 0
                    ) {
                        nufus++;
                    }
                }
            }
            printf("Nufus: %d        ", nufus);
        }
        printf("\n\n");

        printf("Uzay Araclari:\n\n");
        printf("%-10s %-10s %-10s %-10s %-20s %-20s\n", "Arac Adi", "Durum", "Cikis", "Varis", "Hedefe Kalan Saat", "Hedefe Varacagi Tarih");

        for (int i = 0; i < aracSayisi; i++) {
            char durum[10];
            char varisTarih[25];

            if (araclar[i].imha) {
                strcpy(durum, "IMHA");
                strcpy(varisTarih, "--");
            } else if (araclar[i].kalanSaat == 0) {
                strcpy(durum, "Vardi");
            } else if (
                strcmp(araclar[i].cikis, araclar[i].varis) == 0 ||
                araclar[i].kalanSaat == araclar[i].orijinalMesafeSaat
            ) {
                strcpy(durum, "Bekliyor");
            } else {
                strcpy(durum, "Yolda");
            }

            if (strcmp(durum, "Vardi") != 0) {
                strcpy(varisTarih, "--");
            } else {
                Gezegen* varisGezegen = gezegenBul(gezegenler, gezegenSayisi, araclar[i].varis);
                Zaman tahmini = tarihKopyala(varisGezegen->tarih);
                for (int h = 0; h < araclar[i].kalanSaat; h++) {
                    zamaniBirSaatArtir(&tahmini, varisGezegen->gunSaat);
                }
                sprintf(varisTarih, "%02d.%02d.%04d", tahmini.gun, tahmini.ay, tahmini.yil);
            }

            printf("%-10s %-10s %-10s %-10s %-20d %-20s\n",
                   araclar[i].adi, durum, araclar[i].cikis, araclar[i].varis,
                   araclar[i].imha ? 0 : araclar[i].kalanSaat,
                   araclar[i].imha ? "--" : varisTarih);
        }
    }
}
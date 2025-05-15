#include <stdio.h>
#include "Zaman.h"
#include <time.h>

// Her ayın gün sayısı
int ayGunleri[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// Zaman yapısındaki saati 1 artırır, gün-saat sınırlarını kontrol eder
void zamaniBirSaatArtir(Zaman* z, int gunSaatSayisi) {
    z->saat++;
    if (z->saat >= gunSaatSayisi) {
        z->saat = 0;
        z->gun++;
        int maxGun = ayGunleri[z->ay - 1];

        // Artık yıl kontrolü (sadeleştirilmiş)
        if (z->ay == 2 && z->yil % 4 == 0) {
            maxGun = 29;
        }

        if (z->gun > maxGun) {
            z->gun = 1;
            z->ay++;
            if (z->ay > 12) {
                z->ay = 1;
                z->yil++;
            }
        }
    }
}

// İki Zaman yapısını yıl, ay, gün olarak karşılaştırır
int tarihKarsilastir(Zaman a, Zaman b) {
    if (a.yil != b.yil) return a.yil - b.yil;
    if (a.ay != b.ay) return a.ay - b.ay;
    return a.gun - b.gun;
}

// İki tarih aynı mı diye kontrol eder
int ayniTarihMi(Zaman a, Zaman b) {
    return (a.yil == b.yil && a.ay == b.ay && a.gun == b.gun);
}

// Zaman yapısını kopyalar
Zaman tarihKopyala(Zaman z) {
    return z;
}

// Zaman yapısını ekrana gün.ay.yıl formatında yazdırır
void zamaniYazdir(Zaman z) {
    printf("%02d.%02d.%04d", z.gun, z.ay, z.yil);
}



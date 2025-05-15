#include <stdio.h>
#include "DosyaOkuma.h"
#include "Simulasyon.h"
#include "UzayAraci.h"


#define MAX_KISI 100
#define MAX_ARAC 20
#define MAX_GEZEGEN 10

int main() {
    Kisi kisiler[MAX_KISI];
    UzayAraci araclar[MAX_ARAC];
    Gezegen gezegenler[MAX_GEZEGEN];

    int kisiSayisi = kisileriOku("data/Kisiler.txt", kisiler);
    int aracSayisi = araclariOku("data/Araclar.txt", araclar);
    int gezegenSayisi = gezegenleriOku("data/Gezegenler.txt", gezegenler);

    simulasyonuBaslat(kisiler, kisiSayisi, araclar, aracSayisi, gezegenler, gezegenSayisi);

    return 0;
}

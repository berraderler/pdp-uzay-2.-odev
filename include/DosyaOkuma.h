#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H

#include "Kisi.h"
#include "UzayAraci.h"
#include "Gezegen.h"

int kisileriOku(const char* dosya, Kisi* kisiler);
int araclariOku(const char* dosya, UzayAraci* araclar);
int gezegenleriOku(const char* dosya, Gezegen* gezegenler);

#endif

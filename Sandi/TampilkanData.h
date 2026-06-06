#ifndef SANDI_TAMPILKANDATA_H
#define SANDI_TAMPILKANDATA_H

#include <string>

// Struct untuk data Bengkel (Maksimal 100 data di Array)
struct Bengkel {
    int id;
    std::string namaBengkel;
    std::string daerah;
};

// Deklarasi Global Array untuk data Bengkel agar bisa diakses bareng-bareng
extern Bengkel databaseBengkel[100];
extern int jumlahBengkel;

// Prototipe Fungsi Utama Sandi (Menu 3)
void tampilkanSemuaData();
void bubbleSortBengkel();

#endif
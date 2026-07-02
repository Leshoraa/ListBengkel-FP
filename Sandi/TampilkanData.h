#ifndef SANDI_TAMPILKANDATA_H
#define SANDI_TAMPILKANDATA_H

#include <string>
// TAMBAHKAN BARIS INI untuk meminjam struct dari file Rafly
#include "../Rafly/ManajemenBengkel.h" 

// --- HAPUS / BLOK struct Bengkel { ... }; YANG ADA DI SINI SEBELUMNYA ---
// (Jangan ada lagi tulisan struct Bengkel { ... } di file ini)

// Deklarasi Global Array untuk data Bengkel agar bisa diakses bareng-bareng
// Pastikan namanya dataBengkel ya, bukan databaseBengkel
extern Bengkel dataBengkel[100]; // atau [MAX_DATA] jika 100 error
extern int jumlahBengkel;

// Prototipe fungsi utama sandi (Menu 3 & 1)
void tampilkanSemuaData();
void bubbleSortBengkel();
void cariBengkelByDaerah();

#endif

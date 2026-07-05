#ifndef SANDI_TAMPILKANDATA_H
#define SANDI_TAMPILKANDATA_H

#include <string>
// TAMBAHKAN BARIS INI untuk meminjam struct dari file Rafly
#include "../Rafly/ManajemenBengkel.h" 

// --- HAPUS / BLOK struct Bengkel { ... }; YANG ADA DI SINI SEBELUMNYA ---
// (Jangan ada lagi tulisan struct Bengkel { ... } di file ini)

/** NOTE:
* ? Kamu yakin pake extern? Udah dibahas kah sama dosennya?
*
* Better sesuaiin sama materi yang dikasih aja,
* Biar nanti gampang pas dipresentasiin.
*/

// Deklarasi Global Array untuk data Bengkel agar bisa diakses bareng-bareng
// Pastikan namanya dataBengkel ya, bukan databaseBengkel
extern Bengkel dataBengkel[100]; // atau [MAX_DATA] jika 100 error
extern int jumlahBengkel;

// Prototipe fungsi utama sandi (Menu 3 & 1)
void tampilkanSemuaData();
void bubbleSortBengkel();
bool cariBengkelByDaerah();

#endif

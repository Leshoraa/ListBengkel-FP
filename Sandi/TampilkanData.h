#ifndef SANDI_TAMPILKANDATA_H
#define SANDI_TAMPILKANDATA_H

#include <string>


/* NOTE:
* ! JANGAN bikin struct di .h dan deklarasinya.
*
*/

// Struct untuk data Bengkel (Maksimal 100 data di Array)
struct Bengkel {
    int id;
    std::string namaBengkel;
    std::string daerah;
};

/* NOTE:
* ? Kamu yakin pake extern? Udah dibahas kah sama dosennya?
*
* Better sesuaiin sama materi yang dikasih aja,
* Biar nanti gampang pas dipresentasiin.
*/
1
// Deklarasi Global Array untuk data Bengkel agar bisa diakses bareng-bareng
extern Bengkel databaseBengkel[100];
extern int jumlahBengkel; 

// Prototipe Fungsi Utama Sandi (Menu 3)
void tampilkanSemuaData();
void bubbleSortBengkel();

#endif
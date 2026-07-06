#ifndef SANDI_TAMPILKANDATA_H
#define SANDI_TAMPILKANDATA_H

#include <string>
// TAMBAHKAN BARIS INI untuk meminjam struct dari file Rafly
#include "../Rafly/ManajemenBengkel.h" 





extern Bengkel dataBengkel[100]; 
extern int jumlahBengkel;

void tampilkanSemuaData();
void bubbleSortBengkel();
bool cariBengkelByDaerah();

#endif

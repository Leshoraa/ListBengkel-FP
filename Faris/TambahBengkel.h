#ifndef TAMBAHBENGKEL_H
#define TAMBAHBENGKEL_H

#include "../Rafly/ManajemenBengkel.h"

// ============================================================
//  DEKLARASI FUNGSI UTAMA (dipanggil dari main.cpp)
// ============================================================

void tambahBengkel(Bengkel data[], int &n);

// ============================================================
//  DEKLARASI FUNGSI PENDUKUNG
// ============================================================

bool  arrayPenuh(int n);
int   generateID(Bengkel data[], int n);
void  inputDetailBengkel(Bengkel &b, int id);
void  simpanKeBengkel(Bengkel data[], int &n, Bengkel baru);

#endif

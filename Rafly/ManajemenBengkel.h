#ifndef MANAJEMENBENGKEL_H
#define MANAJEMENBENGKEL_H

#include <string>
using namespace std;
struct Bengkel {
    int    id;
    string nama;
    string jenis_layanan;
    string alamat;
    string no_telepon;
};

const int MAX_DATA = 100;

//  DEKLARASI FUNGSI UTAMA (dipanggil dari main.cpp)
void manajemenDataBengkel(Bengkel data[], int &n);

//  DEKLARASI FUNGSI PENDUKUNG
int  cariBengkelByID(Bengkel data[], int n, int idCari);
void updateBengkel(Bengkel *b);
void hapusBengkel(Bengkel data[], int &n, int index);
void tampilDetailBengkel(const Bengkel &b);
#endif 

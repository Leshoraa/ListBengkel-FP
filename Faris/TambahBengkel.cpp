#include "TambahBengkel.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

//  CEK KAPASITAS - Apakah array sudah penuh (MAX_DATA = 100)
bool arrayPenuh(int n) {
    return n >= MAX_DATA;
}


//  GENERATE ID OTOMATIS - ID unik berdasarkan data yang ada
//  Mencari nilai ID tertinggi lalu +1
int generateID(Bengkel data[], int n) {
    if (n == 0) return 1;

    int maxID = data[0].id;
    for (int i = 1; i < n; i++) {
        if (data[i].id > maxID) {
            maxID = data[i].id;
        }
    }
    return maxID + 1;
}

//  INPUT - Mengisi detail bengkel baru dari keyboard
void inputDetailBengkel(Bengkel &b, int id) {
    b.id = id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nama Bengkel      : ";
    getline(cin, b.nama);

    cout << "Jenis Layanan     : ";
    getline(cin, b.jenis_layanan);

    cout << "Alamat            : ";
    getline(cin, b.alamat);

    cout << "No. Telepon       : ";
    getline(cin, b.no_telepon);

    cout << "Harga Estimasi Rp : ";
    cin  >> b.harga;
}

//  SIMPAN - Menyimpan struct Bengkel ke dalam array
void simpanKeBengkel(Bengkel data[], int &n, Bengkel baru) {
    data[n] = baru;
    n++;
}

//  FUNGSI UTAMA MENU 2 - Tambah Bengkel
//  Alur: Cek Penuh -> Input Detail -> Simpan ke Array Struct
void tambahBengkel(Bengkel data[], int &n) {
    cout << "========================================" << endl;
    cout << "         TAMBAH DATA BENGKEL            " << endl;
    cout << "========================================" << endl;

    // --- CEK ARRAY PENUH ---
    if (arrayPenuh(n)) {
        cout << "\n>> Maaf, memori penuh! Data bengkel sudah mencapai batas maksimum ("
             << MAX_DATA << " data). <<" << endl;
        return;
    }

    // --- GENERATE ID OTOMATIS ---
    int idBaru = generateID(data, n);
    cout << "\nID Bengkel (otomatis) : " << idBaru << endl;
    cout << "Isi detail bengkel berikut:\n" << endl;

    // --- INPUT DETAIL BENGKEL ---
    Bengkel baru;
    inputDetailBengkel(baru, idBaru);

    // --- SIMPAN KE ARRAY STRUCT ---
    simpanKeBengkel(data, n, baru);

    cout << "\n>> Data bengkel berhasil disimpan! "
         << "Total data saat ini: " << n << " bengkel. <<" << endl;

    // --- TAMPILKAN KONFIRMASI ---
    cout << "\n== Data yang Tersimpan ==" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "| ID           : " << baru.id                                          << endl;
    cout << "| Nama         : " << baru.nama                                        << endl;
    cout << "| Layanan      : " << baru.jenis_layanan                               << endl;
    cout << "| Alamat       : " << baru.alamat                                      << endl;
    cout << "| No. Telepon  : " << baru.no_telepon                                  << endl;
    cout << "| Harga        : Rp " << fixed << setprecision(0) << baru.harga        << endl;
    cout << "+-------------------------------------+" << endl;
}

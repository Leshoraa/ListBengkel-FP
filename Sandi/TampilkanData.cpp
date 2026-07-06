#include "TampilkanData.h"
#include <iostream>
#include <string>

using namespace std;

// Inisialisasi variabel tanpa extern
Bengkel dataBengkel[100];
int jumlahBengkel = 0; 

// Deklarasi fungsi dari file lain (tanpa extern)
void pushSearchHistory(string aktivitas); 

// ========================================================
// TUGAS SANDI: MENU 3 - TAMPILKAN & SORTING
// ========================================================

// Sesuai Modul 6: Bubble Sort
void bubbleSortBengkel() {
    for (int i = 0; i < jumlahBengkel - 1; i++) {
        for (int j = 0; j < jumlahBengkel - i - 1; j++) {
            if (dataBengkel[j].nama > dataBengkel[j + 1].nama) {
                // Proses Swap (Tukar)
                Bengkel temp = dataBengkel[j];
                dataBengkel[j] = dataBengkel[j + 1];
                dataBengkel[j + 1] = temp;
            }
        }
    }
}

void tampilkanSemuaData() {
    if (jumlahBengkel == 0) {
        cout << "  ┌────────────────────────────────────────┐\n";
        cout << "  │                                        │\n";
        cout << "  │        Database Bengkel Kosong!        │\n";
        cout << "  │                                        │\n";
        cout << "  └────────────────────────────────────────┘\n";
        return;
    }

    bubbleSortBengkel();

    // Menggunakan \t (Tab) Sesuai Modul 1
    cout << "  ┌────┬──────┬─────────────────────────┬─────────────────────────┐\n";
    cout << "  │ No\t│ ID\t│ Nama Bengkel\t\t│ Daerah\t\t  │\n";
    cout << "  ├────┼──────┼─────────────────────────┼─────────────────────────┤\n";
    
    for (int i = 0; i < jumlahBengkel; i++) {
        cout << "  │ " << (i + 1) << "\t│ "
             << dataBengkel[i].id << "\t│ "
             << dataBengkel[i].nama << "\t\t│ "
             << dataBengkel[i].alamat << "\t\t  │\n";
    }
    cout << "  └────┴──────┴─────────────────────────┴─────────────────────────┘\n";
}

// ========================================================
// TUGAS SANDI: MENU 1 - CARI BENGKEL BERDASARKAN DAERAH
// ========================================================

void cariBengkelByDaerah() {
    string inputDaerah;

    cout << "  ┌─ Masukkan nama daerah yang dicari: ";
    
    // Sesuai Modul 3: Penggunaan getline standar tanpa ws
    getline(cin, inputDaerah); 

    cout << "  │\n";

    bool ditemukan = false;
    
    // Sesuai Modul 7: Sequential Search dengan exact match (==)
    for (int i = 0; i < jumlahBengkel; i++) {
        if (dataBengkel[i].alamat == inputDaerah) { // <- DIUBAH MENJADI ==
            if (!ditemukan) {
                cout << "  ├─ Hasil Pencarian:\n";
                cout << "  │\n";
            }
            cout << "  │  ├─ ID      : " << dataBengkel[i].id << "\n";
            cout << "  │  ├─ Bengkel : " << dataBengkel[i].nama << "\n";
            cout << "  │  └─ Daerah  : " << dataBengkel[i].alamat << "\n";
            cout << "  │\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "  ├─ Hasil Pencarian: Tidak ditemukan data di daerah tersebut.\n";
    }

    cout << "  └────────────────────────────────────────────────────────────\n";
}
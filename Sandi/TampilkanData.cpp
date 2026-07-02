#include "TampilkanData.h"
#include <iostream>
#include <iomanip>

using namespace std;

extern void pushSearchHistory(string aktivitas); 

// ======================================================
// TUGAS SANDI: MENU 3 - TAMPILKAN & SORTING
// ======================================================

void bubbleSortBengkel() {
    for (int i = 0; i < jumlahBengkel - 1; i++) {
        for (int j = 0; j < jumlahBengkel - i - 1; j++) {
            // Sudah diganti menjadi .nama
            if (dataBengkel[j].nama > dataBengkel[j + 1].nama) {
                Bengkel temp = dataBengkel[j];
                dataBengkel[j] = dataBengkel[j + 1];
                dataBengkel[j + 1] = temp;
            }
        }
    }
}

void tampilkanSemuaData() {
    if (jumlahBengkel == 0) {
        cout << "╭──────────────────────────────────────────╮\n";
        cout << "│                                          │\n";
        cout << "│         Database Bengkel Kosong!         │\n";
        cout << "│                                          │\n";
        cout << "╰──────────────────────────────────────────╯\n";
        return;
    }

    bubbleSortBengkel();

    cout << "╭────┬─────┬──────────────────────┬───────────────────────────╮\n";
    cout << "│ " << left << setw(2) << "No" << " │ "
         << setw(3) << "ID" << " │ " 
         << setw(20) << "Nama Bengkel" << " │ " 
         << setw(25) << "Daerah" << " │\n";
    cout << "├────┼─────┼──────────────────────┼───────────────────────────┤\n";
    
    for (int i = 0; i < jumlahBengkel; i++) {
        // Sudah diganti menjadi .nama dan .alamat
        cout << "│ " << left << setw(2) << (i + 1) << " │ " 
             << setw(3) << dataBengkel[i].id << " │ "
             << setw(20) << dataBengkel[i].nama << " │ " 
             << setw(25) << dataBengkel[i].alamat << " │\n";
    }
    cout << "╰────┴─────┴──────────────────────┴───────────────────────────╯\n";
}

// ======================================================
// TUGAS SANDI: MENU 1 - CARI BENGKEL BERDASARKAN DAERAH
// ======================================================

void cariBengkelByDaerah() {
    string inputDaerah;
    
    cout << "╭─ Masukkan nama daerah yang dicari: ";
    getline(cin >> ws, inputDaerah);
    
    // pushSearchHistory("Mencari Daerah: " + inputDaerah); 
    
    cout << "│\n";
    
    bool ditemukan = false;
    for (int i = 0; i < jumlahBengkel; i++) {
        // Sudah diganti menjadi .alamat
        if (dataBengkel[i].alamat.find(inputDaerah) != string::npos) {
            if (!ditemukan) {
                cout << "├─ Hasil Pencarian:\n";
                cout << "│\n";
            }
            // Sudah diganti menjadi .nama dan .alamat
            cout << "│  ├─ ID      : " << dataBengkel[i].id << "\n";
            cout << "│  ├─ Bengkel : " << dataBengkel[i].nama << "\n";
            cout << "│  │  Daerah  : " << dataBengkel[i].alamat << "\n";
            cout << "│  │\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "├─ Hasil Pencarian: Tidak ditemukan data di daerah tersebut.\n";
    }
    
    cout << "╰──────────────────────────────────────────────────\n";
}

#include "TampilkanData.h"
#include <iostream>
#include <string>

using namespace std;

// Variabel data bengkel
Bengkel dataBengkel[100];
int jumlahBengkel = 0; 

void pushSearchHistory(string aktivitas); 

void bubbleSortBengkel() {
    for (int i = 0; i < jumlahBengkel - 1; i++) {
        for (int j = 0; j < jumlahBengkel - i - 1; j++) {
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
        cout << "  ┌────────────────────────────────────────┐\n";
        cout << "  │        Database Bengkel Kosong!        │\n";
        cout << "  └────────────────────────────────────────┘\n";
        return;
    }

    bubbleSortBengkel();

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

void cariBengkelByDaerah() {
    string inputDaerah;
    cout << "  ┌─ Masukkan nama daerah yang dicari: ";
    getline(cin, inputDaerah); 
    cout << "  │\n";

    bool ditemukan = false;
    for (int i = 0; i < jumlahBengkel; i++) {
        if (dataBengkel[i].alamat == inputDaerah) { 
            if (!ditemukan) {
                cout << "  ├─ Hasil Pencarian:\n  │\n";
            }
            cout << "  │  ├─ ID      : " << dataBengkel[i].id << "\n";
            cout << "  │  ├─ Bengkel : " << dataBengkel[i].nama << "\n";
            cout << "  │  └─ Daerah  : " << dataBengkel[i].alamat << "\n  │\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "  ├─ Hasil Pencarian: Tidak ditemukan data di daerah tersebut.\n";
    }
    cout << "  └────────────────────────────────────────────────────────────\n";
}
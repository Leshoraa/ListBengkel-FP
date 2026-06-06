#include "TampilkanData.h"
#include <iostream>

using namespace std;

// Inisialisasi variabel global
Bengkel databaseBengkel[100];
int jumlahBengkel = 0; 

// ==========================================
// TUGAS SANDI: MENU 3 - TAMPILKAN & SORTING
// ==========================================

// Fungsi Bubble Sort A-Z berdasarkan Nama Bengkel
void bubbleSortBengkel() {
    for (int i = 0; i < jumlahBengkel - 1; i++) {
        for (int j = 0; j < jumlahBengkel - i - 1; j++) {
            // Membandingkan nama bengkel (A-Z)
            if (databaseBengkel[j].namaBengkel > databaseBengkel[j + 1].namaBengkel) {
                // Proses SWAP / Tukar posisi data
                Bengkel temp = databaseBengkel[j];
                databaseBengkel[j] = databaseBengkel[j + 1];
                databaseBengkel[j + 1] = temp;
            }
        }
    }
}

// Fungsi Menampilkan Semua Data
void tampilkanSemuaData() {
    cout << "\n=== MENU 3: TAMPILKAN SEMUA DATA BENGKEL ===" << endl;
    
    // Validasi Data Kosong (Sesuai Flowchart)
    if (jumlahBengkel == 0) {
        cout << "[Pesan]: Database Kosong! Belum ada data bengkel." << endl;
        cout << "Kembali Ke Menu..." << endl;
        return;
    }

    // Jalankan Sorting Bubble Sort A-Z sebelum ditampilkan
    bubbleSortBengkel();

    // Tampilkan data dalam bentuk tabel sederhana
    cout << "---------------------------------------------------------\n";
    cout << "| No | ID   | Nama Bengkel              | Daerah        |\n";
    cout << "---------------------------------------------------------\n";
    for (int i = 0; i < jumlahBengkel; i++) {
        cout << "| " << (i + 1) << "  | " 
             << databaseBengkel[i].id << "    | "
             << databaseBengkel[i].namaBengkel << "\t\t| "
             << databaseBengkel[i].daerah << "\t|\n";
    }
    cout << "---------------------------------------------------------\n";
    cout << "Kembali Ke Menu..." << endl;
}
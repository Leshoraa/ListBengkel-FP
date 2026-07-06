#include "TambahBengkel.h"
#include "../Rafly/FileHandling.h"
#include "../Utils.h"
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
void inputDetailBengkel(Bengkel data[], int n, Bengkel &b, int id) {
    b.id = id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Nama Bengkel      : ";
        getline(cin, b.nama);
        
        if (b.nama.empty()) {
            cout << "  [!] Validasi: tolong isi Nama Bengkel!\n\n";
            continue;
        }

        bool isDuplicate = false;
        for (int i = 0; i < n; i++) {
            if (data[i].nama == b.nama) {
                isDuplicate = true;
                break;
            }
        }
        
        if (isDuplicate) {
            cout << "  [!] Nama '" << b.nama << "' sudah terdaftar.\n";
            cout << "      Silakan gunakan nama bengkel yang lain.\n\n";
        } else {
            break;
        }
    }

    int pilihLayanan = 0;
    while (true) {
        cout << "\nJenis Layanan / Spesialis:\n";
        cout << "1. Spesialis Motor\n";
        cout << "2. Spesialis Mobil\n";
        cout << "3. Umum (Motor & Mobil)\n";
        cout << "Pilih (1-3)       : ";
        cin >> pilihLayanan;
        
        if (pilihLayanan == 1) {
            b.jenis_layanan = "Spesialis Motor";
            break;
        } else if (pilihLayanan == 2) {
            b.jenis_layanan = "Spesialis Mobil";
            break;
        } else if (pilihLayanan == 3) {
            b.jenis_layanan = "Umum (Motor & Mobil)";
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "\nAlamat            : ";
        getline(cin, b.alamat);

        if (b.alamat.empty()) {
            cout << "  [!] Validasi: tolong isi Alamat!\n";
        } else {
            break;
        }
    }

    while (true) {
        cout << "No. Telepon       : ";
        getline(cin, b.no_telepon);
        
        if (b.no_telepon.empty()) {
            cout << "  [!] Validasi: tolong isi No. Telepon!\n\n";
            continue;
        }

        bool isDuplicate = false;
        for (int i = 0; i < n; i++) {
            if (data[i].no_telepon == b.no_telepon) {
                isDuplicate = true;
                break;
            }
        }
        
        if (isDuplicate) {
            cout << "  [!] No. Telepon '" << b.no_telepon << "' sudah terdaftar.\n";
            cout << "      Silakan gunakan nomor telepon yang lain.\n\n";
        } else {
            break;
        }
    }
}

//  SIMPAN - Menyimpan struct Bengkel ke dalam array
void simpanKeBengkel(Bengkel data[], int &n, Bengkel baru) {
    data[n] = baru;
    n++;
}

//  FUNGSI UTAMA MENU 2 - Tambah Bengkel
//  Alur: Cek Penuh -> Input Detail -> Simpan ke Array Struct
void tambahBengkel(Bengkel data[], int &n) {
    cout << CYAN << "╭──────────────────────────────────────────────────────\n";
    cout << "│ TAMBAH DATA BENGKEL BARU\n";
    cout << "├──────────────────────────────────────────────────────\n" << RESET;

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
    inputDetailBengkel(data, n, baru, idBaru);

    // --- SIMPAN KE ARRAY STRUCT ---
    simpanKeBengkel(data, n, baru);
    
    // --- SIMPAN KE FILE FSTREAM ---
    saveData(data, n);

    cout << "\n>> Data bengkel berhasil disimpan! "
         << "Total data saat ini: " << n << " bengkel. <<" << endl;

    // --- TAMPILKAN KONFIRMASI ---
    cout << "\n" << CYAN << "╭──────────────────────────────────────────────────────\n";
    cout << "│ BUKTI REGISTRASI BENGKEL (Data Tersimpan)\n";
    cout << "├──────────────────────────────────────────────────────\n" << RESET;
    cout << "│ ID           : " << baru.id << endl;
    cout << "│ Nama         : " << baru.nama << endl;
    cout << "│ Layanan      : " << baru.jenis_layanan << endl;
    cout << "│ Alamat       : " << baru.alamat << endl;
    cout << "│ No. Telepon  : " << baru.no_telepon << endl;
    cout << CYAN << "╰──────────────────────────────────────────────────────\n" << RESET;
}

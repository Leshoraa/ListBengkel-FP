#include "ManajemenBengkel.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;


//  SEARCHING - Linear Search berdasarkan ID
int cariBengkelByID(Bengkel data[], int n, int idCari) {
    for (int i = 0; i < n; i++) {
        if (data[i].id == idCari) {
            return i;   
        }
    }
    return -1;          
}


//  HELPER - Tampilkan detail satu bengkel
void tampilDetailBengkel(const Bengkel &b) {
    cout << "╭──────────────────────────────────────────────────────\n";
    cout << "│ ID           : " << b.id << endl;
    cout << "│ Nama         : " << b.nama << endl;
    cout << "│ Layanan      : " << b.jenis_layanan << endl;
    cout << "│ Alamat       : " << b.alamat << endl;
    cout << "│ No. Telepon  : " << b.no_telepon << endl;
    cout << "│ Harga        : Rp " << fixed << setprecision(0) << b.harga << endl;
    cout << "╰──────────────────────────────────────────────────────\n";
}

//  UPDATE - Mengubah data bengkel menggunakan POINTER
void updateBengkel(Bengkel *b) {
    int pilihField;

    cout << "\n╭──── Data Saat Ini \n";
    tampilDetailBengkel(*b);

    cout << "│\n";
    cout << "│ Pilih field yang ingin diubah:\n";
    cout << "│ 1. Nama Bengkel\n";
    cout << "│ 2. Jenis Layanan\n";
    cout << "│ 3. Alamat\n";
    cout << "│ 4. No. Telepon\n";
    cout << "│ 5. Harga\n";
    cout << "│ 6. Ubah Semua Data\n";
    cout << "│\n";
    cout << "├──── Pilih : ";
    cin >> pilihField;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

      // pointer arrow operator
    switch (pilihField) {
        case 1:
            cout << "Nama baru : ";
            getline(cin, b->nama);           
            break;
        case 2:
            cout << "Layanan baru : ";
            getline(cin, b->jenis_layanan);
            break;
        case 3:
            cout << "Alamat baru : ";
            getline(cin, b->alamat);
            break;
        case 4:
            cout << "No. Telepon baru : ";
            getline(cin, b->no_telepon);
            break;
        case 5:
            cout << "Harga baru : Rp ";
            cin >> b->harga;
            break;
        case 6:
            cout << "Nama baru : ";
            getline(cin, b->nama);
            cout << "Layanan baru : ";
            getline(cin, b->jenis_layanan);
            cout << "Alamat baru : ";
            getline(cin, b->alamat);
            cout << "No. Telepon baru : ";
            getline(cin, b->no_telepon);
            cout << "Harga baru : Rp ";
            cin >> b->harga;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }

    cout << "\n╭──────────────────────────────────────────────────────\n";
    cout << "│ Data berhasil diperbarui!\n";
    cout << "╰──────────────────────────────────────────────────────\n";
    cout << "\n╭──── Data Setelah Update \n";
    tampilDetailBengkel(*b);
}

//  DELETE - Hapus data & SHIFTING elemen array
void hapusBengkel(Bengkel data[], int &n, int index) {
    cout << "\n╭──── Data yang akan dihapus \n";
    tampilDetailBengkel(data[index]);

    char konfirmasi;
    cout << "├──── Yakin ingin menghapus data ini? (y/n) : ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = index; i < n - 1; i++) {
            data[i] = data[i + 1];
        }
        n--;  

        cout << "\n╭──────────────────────────────────────────────────────\n";
        cout << "│ Data berhasil dihapus! Sisa data: " << n << " bengkel\n";
        cout << "╰──────────────────────────────────────────────────────\n";
    } else {
        cout << "\n╭──────────────────────────────────────────────────────\n";
        cout << "│ Penghapusan dibatalkan.\n";
        cout << "╰──────────────────────────────────────────────────────\n";
    }
}

//  FUNGSI UTAMA MENU 4 - Manajemen Data Bengkel
//  Menggabungkan : Searching + Pointer + Shifting
void manajemenDataBengkel(Bengkel data[], int &n) {
    if (n == 0) {
        cout << "Database bengkel kosong! Tidak ada data untuk dikelola." << endl;
        return;
    }

    int idCari;
    cout << "╭──────────────────────────────────────────────────────\n";
    cout << "│ MANAJEMEN DATA BENGKEL (UPDATE/DELETE)\n";
    cout << "├──────────────────────────────────────────────────────\n";
    
    cout << "│ Daftar Bengkel Tersedia:\n";
    cout << "│ ╭──────┬─────────────────────────────────╮\n";
    cout << "│ │ ID   │ Nama Bengkel                    │\n";
    cout << "│ ├──────┼─────────────────────────────────┤\n";
    for (int i = 0; i < n; i++) {
        cout << "│ │ " << left << setw(4) << data[i].id 
             << " │ " << setw(31) << data[i].nama << " │\n";
    }
    cout << "│ ╰──────┴─────────────────────────────────╯\n";

    cout << "│\n";
    cout << "├──── Masukkan ID Bengkel : ";
    cin >> idCari;

    // SEARCHING - cari posisi index berdasarkan ID
    int index = cariBengkelByID(data, n, idCari);


    if (index == -1) {
        cout << "\n╭──────────────────────────────────────────────────────\n";
        cout << "│ ID Bengkel [" << idCari << "] tidak ditemukan!\n";
        cout << "╰──────────────────────────────────────────────────────\n";
        return;
    }

    cout << "\n╭──────────────────────────────────────────────────────\n";
    cout << "│ ID Bengkel [" << idCari << "] ditemukan!\n";
    cout << "╰──────────────────────────────────────────────────────\n";
    tampilDetailBengkel(data[index]);

    int aksi;
    cout << "│\n";
    cout << "│ Pilih Aksi:\n";
    cout << "│ 1. Update Data\n";
    cout << "│ 2. Delete Data\n";
    cout << "│ 3. Batal (Kembali ke Menu)\n";
    cout << "│\n";
    cout << "├──── Pilih : ";
    cin >> aksi;

    switch (aksi) {
        case 1:
            updateBengkel(&data[index]);
            break;
        case 2:
            hapusBengkel(data, n, index);
            break;
        case 3:
            cout << "Kembali ke menu utama." << endl;
            break;
        default:
            cout << "Aksi tidak valid!" << endl;
            break;
    }
}

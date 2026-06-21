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
    cout << "+-------------------------------------+" << endl;
    cout << "| ID           : " << b.id << endl;
    cout << "| Nama         : " << b.nama << endl;
    cout << "| Layanan      : " << b.jenis_layanan << endl;
    cout << "| Alamat       : " << b.alamat << endl;
    cout << "| No. Telepon  : " << b.no_telepon << endl;
    cout << "| Harga        : Rp " << fixed << setprecision(0) << b.harga << endl;
    cout << "+-------------------------------------+" << endl;
}

//  UPDATE - Mengubah data bengkel menggunakan POINTER
void updateBengkel(Bengkel *b) {
    int pilihField;

    cout << "\n== Data Saat Ini ==" << endl;
    tampilDetailBengkel(*b);

    cout << "\nPilih field yang ingin diubah:" << endl;
    cout << "1. Nama Bengkel" << endl;
    cout << "2. Jenis Layanan" << endl;
    cout << "3. Alamat" << endl;
    cout << "4. No. Telepon" << endl;
    cout << "5. Harga" << endl;
    cout << "6. Ubah Semua Data" << endl;
    cout << "Pilih : ";
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

    cout << "\n>> Data berhasil diperbarui! <<" << endl;
    cout << "\n== Data Setelah Update ==" << endl;
    tampilDetailBengkel(*b);
}

//  DELETE - Hapus data & SHIFTING elemen array
void hapusBengkel(Bengkel data[], int &n, int index) {
    cout << "\n== Data yang akan dihapus ==" << endl;
    tampilDetailBengkel(data[index]);

    char konfirmasi;
    cout << "Yakin ingin menghapus data ini? (y/n) : ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = index; i < n - 1; i++) {
            data[i] = data[i + 1];
        }
        n--;  

        cout << "\n>> Data berhasil dihapus! Sisa data: " << n << " bengkel <<" << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
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
    cout << "========================================" << endl;
    cout << "  MANAJEMEN DATA BENGKEL (UPDATE/DELETE)" << endl;
    cout << "========================================" << endl;
    
    cout << "\nDaftar Bengkel Tersedia:" << endl;
    cout << "+------+---------------------------------+" << endl;
    cout << "| ID   | Nama Bengkel                    |" << endl;
    cout << "+------+---------------------------------+" << endl;
    for (int i = 0; i < n; i++) {
        cout << "| " << left << setw(4) << data[i].id 
             << " | " << setw(31) << data[i].nama << " |" << endl;
    }
    cout << "+------+---------------------------------+" << endl;

    cout << "\nMasukkan ID Bengkel : ";
    cin >> idCari;

    // SEARCHING - cari posisi index berdasarkan ID
    int index = cariBengkelByID(data, n, idCari);


    if (index == -1) {
        cout << "\n>> ID Bengkel [" << idCari << "] tidak ditemukan! <<" << endl;
        return;
    }

    cout << "\n>> ID Bengkel [" << idCari << "] ditemukan! <<" << endl;
    tampilDetailBengkel(data[index]);

    int aksi;
    cout << "\nPilih Aksi:" << endl;
    cout << "1. Update Data" << endl;
    cout << "2. Delete Data" << endl;
    cout << "3. Batal (Kembali ke Menu)" << endl;
    cout << "Pilih : ";
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

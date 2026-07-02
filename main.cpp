#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Utils.h"
#include "Affan/BookingServis.cpp"
#include "Affan/LogRiwayat.cpp"
#include "Rafly/ManajemenBengkel.cpp"
#include "Faris/FileHandling.cpp"
#include "Faris/TambahBengkel.cpp"

using namespace std;

Bengkel dataBengkel[MAX_DATA];
int jumlahBengkel = 0;

void tampilmenu() {
    cout << CYAN << "╭───────────────────────────────────────────╮\n";
    cout << "│ SISTEM MANAGEMEN BENGKEL\n";
    cout << "├───────────────────────────────────────────╯\n" << RESET;
    cout << "│ 1. Cari Bengkel\n";
    cout << "│ 2. Tambah bengkel\n";
    cout << "│ 3. Tampilkan Semua Bengkel\n";
    cout << "│ 4. Managemen Data Bengkel(Update/Delete)\n";
    cout << "│ 5. Booking Service\n";
    cout << "│ 6. Log Riwayat\n";
    cout << "│ 7. Keluar\n";
    cout << "│ 8. Statistik Data Bengkel\n";
    cout << CYAN << "├───────────────────────────────────────────╯\n" << RESET;
    cout << "│\n";
    cout << "╰──── Pilih menu : ";
}

void dealokasiMemori() {
    clearQueue();
    clearStack();
    cout << "│ Proses Dealokasi Memori Selesai...\n";
}

void tampilkanStatistik(Bengkel data[], int n) {
    if (n == 0) {
        cout << MERAH << "│ Database masih kosong, belum ada statistik.\n" << RESET;
        return;
    }
    float termurah = data[0].harga;
    float termahal = data[0].harga;
    float total = 0;
    string namaTermurah = data[0].nama;
    string namaTermahal = data[0].nama;
    
    for (int i = 0; i < n; i++) {
        if (data[i].harga < termurah) {
            termurah = data[i].harga;
            namaTermurah = data[i].nama;
        }
        if (data[i].harga > termahal) {
            termahal = data[i].harga;
            namaTermahal = data[i].nama;
        }
        total += data[i].harga;
    }
    float rata = total / n;
    
    cout << KUNING << "╭──────────────────────────────────────────────────────\n";
    cout << "│ STATISTIK DATA BENGKEL\n";
    cout << "├──────────────────────────────────────────────────────\n" << RESET;
    cout << "│ Total Bengkel Terdaftar : " << CYAN << n << " Bengkel\n" << RESET;
    cout << "│ Bengkel Termurah        : " << HIJAU << namaTermurah << " (Rp " << termurah << ")\n" << RESET;
    cout << "│ Bengkel Termahal        : " << MERAH << namaTermahal << " (Rp " << termahal << ")\n" << RESET;
    cout << "│ Rata-rata Harga Layanan : " << KUNING << "Rp " << rata << "\n" << RESET;
    cout << KUNING << "╰──────────────────────────────────────────────────────\n" << RESET;
}

bool loginSistem() {
    bool isLogin = false;
    while (!isLogin) {
        system("clear");
        cout << CYAN << "╭───────────────────────────────────────────╮\n";
        cout << "│        SISTEM BENGKEL FP (LOGIN)          │\n";
        cout << "├───────────────────────────────────────────╯\n" << RESET;
        cout << "│ 1. Login\n";
        cout << "│ 2. Register\n";
        cout << "│ 3. Keluar\n";
        cout << CYAN << "├───────────────────────────────────────────╯\n" << RESET;
        cout << "│ Pilih opsi: ";
        int opsi = ambilInputAngka();

        if (opsi == 1) {
            string user, pass, u, p;
            cout << "│ Username : "; cin >> user;
            cout << "│ Password : "; cin >> pass;
            bool found = false;
            ifstream file("data_users.txt");
            if (file.is_open()) {
                while (file >> u >> p) {
                    if (u == user && p == pass) {
                        found = true;
                        break;
                    }
                }
                file.close();
            }
            if (found) {
                cout << HIJAU << "│ Login Berhasil!\n" << RESET;
                isLogin = true;
            } else {
                cout << MERAH << "│ Username atau password salah!\n" << RESET;
            }
        } else if (opsi == 2) {
            string user, pass;
            cout << "│ Buat Username : "; cin >> user;
            cout << "│ Buat Password : "; cin >> pass;
            ofstream file("data_users.txt", ios::app);
            if (file.is_open()) {
                file << user << " " << pass << "\n";
                file.close();
                cout << HIJAU << "│ Registrasi berhasil! Silakan Login.\n" << RESET;
            } else {
                cout << MERAH << "│ Gagal membuat file pengguna.\n" << RESET;
            }
        } else if (opsi == 3) {
            return false;
        } else {
            cout << MERAH << "│ Pilihan tidak valid!\n" << RESET;
        }
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(10000, '\n');
        cin.get();
    }
    return true;
}

int main() {
    // Load data from file at startup
    loadData(dataBengkel, jumlahBengkel);
    
    if (!loginSistem()) {
        cout << "Keluar dari program...\n";
        return 0;
    }

    int pilihan;
    do {
        system("clear");
        tampilmenu();
        pilihan = ambilInputAngka();
        system("clear");
        cout << endl;

        switch(pilihan) {
            case 1:
            {
                int idCari;
                cout << CYAN << "╭──────────────────────────────────────────────────────\n";
                cout << "│ CARI BENGKEL\n";
                cout << "├──────────────────────────────────────────────────────\n" << RESET;
                cout << "│ Masukkan ID Bengkel yang dicari: ";
                idCari = ambilInputAngka();
                
                int index = cariBengkelByID(dataBengkel, jumlahBengkel, idCari);
                if (index != -1) {
                    cout << HIJAU << "│\n│ Bengkel ditemukan!\n" << RESET;
                    tampilDetailBengkel(dataBengkel[index]);
                } else {
                    cout << MERAH << "│\n│ Bengkel dengan ID [" << idCari << "] tidak ditemukan.\n" << RESET;
                    cout << CYAN << "╰──────────────────────────────────────────────────────\n" << RESET;
                }
                
                // Masukkan ke history
                pushSearchHistory("Mencari ID: " + to_string(idCari));
                break;
            }
            case 2:
                tambahBengkel(dataBengkel, jumlahBengkel);
                break;
            case 3:
                cout << "Menu Tambahkan Semua Data\n";
                break;
            case 4:
                manajemenDataBengkel(dataBengkel, jumlahBengkel);
                break;
            case 5:
                menuBookingServis();
                break;
            case 6:
                menuLogRiwayat();
                break;
            case 7:
                cout << HIJAU << "Terimakasih\n" << RESET;
                dealokasiMemori();
                break;
            case 8:
                tampilkanStatistik(dataBengkel, jumlahBengkel);
                break;
            default:
                cout << MERAH << "Pilihan Tidak Valid!!\n" << RESET;
                break;
        }
        cout << endl;
        if (pilihan != 7) {
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore(10000, '\n');
            cin.get();
        }
    } while (pilihan != 7);
    return 0;
}
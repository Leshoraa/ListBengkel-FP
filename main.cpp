#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Utils.h"
#include "Affan/BookingServis.cpp"
#include "Affan/LogRiwayat.cpp"
#include "Rafly/ManajemenBengkel.cpp"
#include "Rafly/FileHandling.cpp"
#include "Faris/TambahBengkel.cpp"
#include "Sandi/TampilkanData.cpp"
#include <iomanip>

using namespace std;

Bengkel dataBengkel[MAX_DATA];
int jumlahBengkel = 0;

void tampilmenu() {
    cout << CYAN << "╭───────────────────────────────────────────╮\n";
    cout << "│ SISTEM MANAGEMEN BENGKEL\n";
    cout << "├───────────────────────────────────────────╯\n" << RESET;
    cout << "│ 1. Pencarian Bengkel \n";
    cout << "│ 2. Registrasi Bengkel Baru \n";
    cout << "│ 3. Daftar Seluruh Bengkel \n";
    cout << "│ 4. Manajemen Data Bengkel \n";
    cout << "│ 5. Layanan Booking Servis \n";
    cout << "│ 6. Riwayat Pencarian \n";
    cout << "│ 7. Laporan & Statistik Data\n";
    cout << "│ 8. Keluar Aplikasi\n";
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
    int totMotor = 0, totMobil = 0, totUmum = 0, totLain = 0;
    
    for (int i = 0; i < n; i++) {
        if (data[i].jenis_layanan == "Spesialis Motor") {
            totMotor++;
        } else if (data[i].jenis_layanan == "Spesialis Mobil") {
            totMobil++;
        } else if (data[i].jenis_layanan == "Umum (Motor & Mobil)") {
            totUmum++;
        } else {
            totLain++;
        }
    }
    
    // Lambda untuk generate progress bar ASCII
    auto getBar = [&](int count, int maxBarSize = 25) {
        if (n == 0) return string("");
        int barLength = (count * maxBarSize) / n;
        string bar = "";
        for (int i = 0; i < barLength; i++) bar += "█";
        return bar;
    };
    
    // Lambda untuk hitung persentase
    auto getPct = [&](int count) {
        if (n == 0) return 0.0f;
        return ((float)count / n) * 100.0f;
    };
    
    cout << KUNING << "╭──────────────────────────────────────────────────────────────────────\n";
    cout << "│ VISUALISASI STATISTIK DATA BENGKEL (Total: " << n << ")\n";
    cout << "├──────────────────────────────────────────────────────────────────────\n" << RESET;
    
    cout << "│ " << left << setw(22) << "Spesialis Motor" << " │ " << HIJAU << left << setw(25) << getBar(totMotor) << RESET 
         << " │ " << totMotor << " (" << fixed << setprecision(1) << getPct(totMotor) << "%)\n";
         
    cout << "│ " << left << setw(22) << "Spesialis Mobil" << " │ " << BIRU << left << setw(25) << getBar(totMobil) << RESET 
         << " │ " << totMobil << " (" << fixed << setprecision(1) << getPct(totMobil) << "%)\n";
         
    cout << "│ " << left << setw(22) << "Umum (Motor & Mobil)" << " │ " << KUNING << left << setw(25) << getBar(totUmum) << RESET 
         << " │ " << totUmum << " (" << fixed << setprecision(1) << getPct(totUmum) << "%)\n";
         
    if (totLain > 0) {
        cout << "│ " << left << setw(22) << "Layanan Lainnya" << " │ " << CYAN << left << setw(25) << getBar(totLain) << RESET 
             << " │ " << totLain << " (" << fixed << setprecision(1) << getPct(totLain) << "%)\n";
    }
    
    cout << KUNING << "╰──────────────────────────────────────────────────────────────────────\n" << RESET;
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
            int idUser, idU;
            cout << "│ Username : "; cin >> user;
            cout << "│ Password : "; cin >> pass;
            bool found = false;
            ifstream file("data_users.txt");
            if (file.is_open()) {
                while (file >> idU >> u >> p) {
                    if (u == user && p == pass) {
                        found = true;
                        idUser = idU;
                        break;
                    }
                }
                file.close();
            }
            if (found) {
                cout << HIJAU << "│ Login Berhasil! (ID Anda: " << idUser << ")\n" << RESET;
                isLogin = true;
            } else {
                cout << MERAH << "│ Username atau password salah!\n" << RESET;
            }
        } else if (opsi == 2) {
            string user, pass, u, p;
            int idU;
            cout << "│ Buat Username : "; cin >> user;
            
            // Cek apakah username sudah ada dan cari maxID
            bool exists = false;
            int maxId = 0;
            ifstream fileIn("data_users.txt");
            if (fileIn.is_open()) {
                while (fileIn >> idU >> u >> p) {
                    if (idU > maxId) maxId = idU;
                    if (u == user) {
                        exists = true;
                        // Jangan di-break agar bisa menemukan maxId dari seluruh file
                    }
                }
                fileIn.close();
            }

            if (exists) {
                cout << MERAH << "│ Username sudah terdaftar! Silakan gunakan username lain.\n" << RESET;
            } else {
                cout << "│ Buat Password : "; cin >> pass;
                int newId = maxId + 1;
                ofstream fileOut("data_users.txt", ios::app);
                if (fileOut.is_open()) {
                    fileOut << newId << " " << user << " " << pass << "\n";
                    fileOut.close();
                    cout << HIJAU << "│ Registrasi berhasil! (ID Baru Anda: " << newId << "). Silakan Login.\n" << RESET;
                } else {
                    cout << MERAH << "│ Gagal membuat file pengguna.\n" << RESET;
                }
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
                cout << CYAN << "╭──────────────────────────────────────────────────────\n";
                cout << "│ CARI BENGKEL BERDASARKAN DAERAH\n";
                cout << "├──────────────────────────────────────────────────────\n" << RESET;
                
                // Panggil fungsi buatan Sandi
                cariBengkelByDaerah();
                
                break;
            }
            case 2:
                tambahBengkel(dataBengkel, jumlahBengkel);
                break;
            case 3:
                cout << CYAN << "╭──────────────────────────────────────────────────────\n";
                cout << "│ SEMUA DATA BENGKEL (SORTED A-Z)\n";
                cout << "├──────────────────────────────────────────────────────\n" << RESET;
                
                // Panggil fungsi buatan Sandi
                tampilkanSemuaData();
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
                tampilkanStatistik(dataBengkel, jumlahBengkel);
                break;
            case 8:
                cout << HIJAU << "Terimakasih\n" << RESET;
                dealokasiMemori();
                break;
            
            default:
                cout << MERAH << "Pilihan Tidak Valid!!\n" << RESET;
                break;
        }
        cout << endl;
        if (pilihan != 8) {
            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore(10000, '\n');
            cin.get();
        }
    } while (pilihan != 8);
    return 0;
}
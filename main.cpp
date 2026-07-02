#include <iostream>
#include "Affan/ServiceManager.h"
#include "Rafly/ManajemenBengkel.h"  

using namespace std;

// Array global & jumlah data bengkel (dipakai semua modul)
Bengkel dataBengkel[MAX_DATA];
int jumlahBengkel = 0;
void tampilmenu() {
    cout << "=====================================\n";
    cout << "  SISTEM MANAGEMEN BENGKEL\n";
    cout << "=====================================\n";
    cout << "1. Cari Bengkel\n";
    cout << "2. Tambah bengkel\n";
    cout << "3. Tampilkan Semua Bengkel\n";
    cout << "4. Managemen Data Bengkel(Update/Delete)\n";
    cout << "5. Booking Service\n";
    cout << "6. Log Riwayat\n";
    cout << "7. keluar\n";
    cout << "=====================================\n";
    cout << "Pilih menu : ";
}
    int main() {
        int pilihan;
        do {
            tampilmenu();
            cin >> pilihan;
            cout << endl;

            switch(pilihan) {
                case 1:
                    cout << "Menu Cari Bengkel\n";
                    break;
                case 2:
                    cout << "Menu Tambah Bengkel\n";
                    break;
                case 3:
                    cout << "Menu Tambahkan Semua Data\n";
                    break;
                case 4:
                    manajemenDataBengkel(dataBengkel, jumlahBengkel);
                    break;
                case 5:
                    enqueueBooking();
                    break;
                case 6:
                    displaySearchHistory();
                    break;
                case 7:
                    cout << "Terimakasih\n";
                    break;
                default:
                    cout << "Pilihan Tidak Valid!!\n";
                    break;
            }
            cout << endl;
        }
        while (pilihan != 7);
        return 0;
    }
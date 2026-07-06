#include "BookingServis.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct BookingNode {
    int tokenId;
    string customerName;
    string namaBengkel;
    string layanan;
    BookingNode* next;
};

BookingNode* queueFront = nullptr;
BookingNode* queueRear = nullptr;

extern bool cariBengkelByDaerah();
extern bool cekBengkelValid(string);

/**
 * @brief Daftarin pelanggan baru ke antrean servis.
 * 
 * Pake konsep Queue (FIFO - First In First Out).
 * Token antrean di-generate otomatis acak.
 */
void enqueueBooking() {
    cout << "\n--- Cari Bengkel Berdasarkan Lokasi ---\n";
    while (true) {
        if (cariBengkelByDaerah()) {
            break;
        } else {
            cout << "│ [!] Silakan coba masukkan nama daerah lain yang tersedia.\n\n";
        }
    }
    cout << "\n";

    string customerName;
    cout << "╭──── Masukkan Nama Pelanggan: ";
    getline(cin, customerName);

    string pilihanBengkel;
    while (true) {
        cout << "├──── Masukkan Nama Bengkel yang Dipilih: ";
        getline(cin, pilihanBengkel);
        
        if (cekBengkelValid(pilihanBengkel)) {
            break;
        } else {
            cout << "│ [!] Nama Bengkel tidak valid atau tidak terdaftar. Silakan periksa kembali ketikan Anda.\n";
        }
    }

    cout << "│\n";
    cout << "│ 1. Kendala Kerusakan\n";
    cout << "│ 2. Servis rutin\n";
    cout << "│\n";
    cout << "├──── Pilih menu: ";
    int opsi;
    cin >> opsi;
    cin.ignore();

    string detailLayanan;
    if (opsi == 1) {
        cout << "│\n";
        cout << "╰──── Isikan Kendala Kerusakan: ";
        getline(cin, detailLayanan);
    } else {
        detailLayanan = "Servis rutin";
    }

    // Generate 3 digit token acak (100 - 999)
    int newToken = rand() % 900 + 100;

    BookingNode* newNode = new BookingNode;
    if (!newNode) {
        cerr << "Kesalahan sistem: Alokasi memori gagal." << endl;
        return;
    }

    newNode->tokenId = newToken;
    newNode->customerName = customerName;
    newNode->namaBengkel = pilihanBengkel;
    newNode->layanan = detailLayanan;
    newNode->next = nullptr;

    if (!queueFront) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }
    
    // --- CETAK TIKET ANTREAN ---
    bool isNotaCreated = false;
    string filename = "nota_booking_" + to_string(newToken) + ".txt";
    ofstream nota(filename);
    if (nota.is_open()) {
        nota << "==========================================\n";
        nota << "        STATUS TIKET (REAL-TIME)\n";
        nota << "==========================================\n";
        nota << "Token   : [" << newToken << "]\n";
        nota << "Nama    : " << customerName << "\n";
        nota << "Bengkel : " << pilihanBengkel << "\n";
        nota << "Layanan : " << detailLayanan << "\n";
        nota << "Status  : Menunggu Giliran\n";
        nota << "==========================================\n";
        nota << "Terima kasih, silakan tunggu panggilan!\n";
        nota.close();
        isNotaCreated = true;
    }
    // ------------------------

    cout << "\n\n\n";
    cout << "╭──────────────────────────────────────────────────────\n";
    cout << "│\n";
    cout << "│ Token [" << newToken << "] berhasil didaftarkan ke dalam antrean." << endl;
    if (isNotaCreated) cout << "│ Tiket tercetak di file: " << filename << endl;
    cout << "│\n";
    cout << "╰──────────────────────────────────────────────────────\n\n\n\n";
}

void dequeueBooking() {
    if (!queueFront) {
        cout << "Antrean kosong. Tidak ada pelanggan yang bisa dipanggil." << endl;
        return;
    }
    BookingNode* temp = queueFront;
    queueFront = queueFront->next;
    
    if (!queueFront) {
        queueRear = nullptr;
    }
    
    cout << "\nMemanggil Antrean:" << endl;
    cout << "Token   : [" << temp->tokenId << "]" << endl;
    cout << "Nama    : " << temp->customerName << endl;
    cout << "Bengkel : " << temp->namaBengkel << endl;
    cout << "Layanan : " << temp->layanan << endl;
    cout << "Silakan menuju area servis.\n" << endl;

    // --- UPDATE STATUS DI NOTA ---
    string filename = "nota_booking_" + to_string(temp->tokenId) + ".txt";
    ofstream nota(filename);
    if (nota.is_open()) {
        nota << "==========================================\n";
        nota << "        STATUS TIKET (REAL-TIME)\n";
        nota << "==========================================\n";
        nota << "Token   : [" << temp->tokenId << "]\n";
        nota << "Nama    : " << temp->customerName << "\n";
        nota << "Bengkel : " << temp->namaBengkel << "\n";
        nota << "Layanan : " << temp->layanan << "\n";
        nota << "Status  : SELESAI DIPANGGIL\n";
        nota << "==========================================\n";
        nota << "Terima kasih telah menggunakan layanan kami!\n";
        nota.close();
        cout << "Status tiket pada file " << filename << " telah diupdate menjadi SELESAI DIPANGGIL.\n\n";
    }

    delete temp;
}

void displayQueue() {
    if (!queueFront) {
        cout << "Antrean saat ini kosong." << endl;
        return;
    }
    
    cout << "\nDaftar Antrean Saat Ini:" << endl;
    BookingNode* current = queueFront;
    int no = 1;
    while (current) {
        cout << no++ << ". Token [" << current->tokenId << "] - " << current->customerName << " @ " << current->namaBengkel << " (" << current->layanan << ")" << endl;
        current = current->next;
    }
}

void menuBookingServis() {
    int opsi;
    do {
        cout << "\n╭───────────────────────────────────────────╮\n";
        cout << "│ BOOKING SERVICE (Antrean)\n";
        cout << "├───────────────────────────────────────────╯\n";
        cout << "│ 1. Ambil Antrean \n";
        cout << "│ 2. Panggil Antrean \n";
        cout << "│ 3. Lihat Daftar Antrean\n";
        cout << "│ 4. Kembali ke Menu Utama\n";
        cout << "├───────────────────────────────────────────╯\n";
        cout << "│\n";
        cout << "╰──── Pilih menu: ";
        cin >> opsi;
        
        switch (opsi) {
            case 1:
                enqueueBooking();
                break;
            case 2:
                dequeueBooking();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                cout << "Kembali..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (opsi != 4);
}

void clearQueue() {
    BookingNode* current = queueFront;
    while (current != nullptr) {
        BookingNode* next = current->next;
        delete current;
        current = next;
    }
    queueFront = nullptr;
    queueRear = nullptr;
}
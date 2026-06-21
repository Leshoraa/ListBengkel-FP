#include "BookingServis.h"
#include <iostream>
#include <cstdlib>

using namespace std;

struct BookingNode {
    int tokenId;
    string customerName;
    string layanan;
    BookingNode* next;
};

BookingNode* queueFront = nullptr;
BookingNode* queueRear = nullptr;

/**
 * @brief Daftarin pelanggan baru ke antrean servis.
 * 
 * Pake konsep Queue (FIFO - First In First Out).
 * Token antrean di-generate otomatis acak.
 */
void enqueueBooking() {
    string customerName;
    cout << "Input Nama Pelanggan: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "1. Kendala Kerusakan\n";
    cout << "2. Servis rutin\n";
    cout << "Pilih menu: ";
    int opsi;
    cin >> opsi;
    cin.ignore();

    string detailLayanan;
    if (opsi == 1) {
        cout << "Isikan Kendala Kerusakan: ";
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
    newNode->layanan = detailLayanan;
    newNode->next = nullptr;

    if (!queueFront) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }

    cout << "Token [" << newToken << "] berhasil didaftarkan ke dalam antrean." << endl;
}
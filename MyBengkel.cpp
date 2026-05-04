#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;

// node buat antrean booking (Queue)
struct BookingNode {
    int tokenId;
    string customerName;
    BookingNode* next;
};

// node buat riwayat pencarian (Stack)
struct HistoryNode {
    string keyword;
    HistoryNode* next;
};

// pointer global buat ngelola Queue dan Stack
BookingNode* queueFront = nullptr;
BookingNode* queueRear = nullptr;
HistoryNode* stackTop = nullptr;

/**
 * enqueueBooking - Masukkin pelanggan ke antrean servis
 * pake prinsip FIFO (First In First Out)
 */
void enqueueBooking() {
    string customerName;
    cout << "Input Nama Pelanggan: ";
    cin.ignore();
    getline(cin, customerName);

    int newToken = rand() % 900 + 100;

    BookingNode* newNode = new BookingNode;
    if (!newNode) {
        cerr << "Kesalahan sistem: Alokasi memori gagal." << endl;
        return; 
    }

    newNode->tokenId = newToken;
    newNode->customerName = customerName;
    newNode->next = nullptr;

    // logika queue: masukkin node baru di posisi paling belakang.
    if (!queueFront) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }
    
    cout << "Token [" << newToken << "] berhasil didaftarkan ke dalam antrean." << endl;
}

/**
 * displaySearchHistory - nampilin log aktivitas dari Stack
 * pake prinsip LIFO (Last In First Out)
 */
void displaySearchHistory() {
    if (!stackTop) {
        cout << "Log riwayat kosong. Belum ada aktivitas pencarian." << endl;
        return;
    }

    HistoryNode* current = stackTop;
    while (current) {
        cout << "-> " << current->keyword << endl;
        current = current->next;
    }
}

/**
 * 
 * NOTE:  
 * ini fungsi wajib dipanggil ke code tiap kali ada pencarian
 */
void pushSearchHistory(string keyword) {
    HistoryNode* newNode = new HistoryNode;
    if (!newNode) return;
    
    newNode->keyword = keyword;
    newNode->next = stackTop;
    stackTop = newNode;
}

int main() {
    
}
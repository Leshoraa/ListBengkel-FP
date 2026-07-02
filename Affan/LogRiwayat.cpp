#include "LogRiwayat.h"
#include <iostream>

using namespace std;

struct HistoryNode {
    string keyword;
    HistoryNode* next;
};

HistoryNode* stackTop = nullptr;

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

void popSearchHistory() {
    if (!stackTop) {
        cout << "Tidak ada riwayat untuk dihapus (Undo)." << endl;
        return;
    }
    HistoryNode* temp = stackTop;
    stackTop = stackTop->next;
    cout << "Riwayat pencarian terakhir ('" << temp->keyword << "') telah dihapus." << endl;
    delete temp;
}

void menuLogRiwayat() {
    int opsi;
    do {
        cout << "\n╭───────────────────────────────────────────╮\n";
        cout << "│ LOG RIWAYAT (Pencarian)\n";
        cout << "├───────────────────────────────────────────╯\n";
        cout << "│ 1. Tampilkan Riwayat\n";
        cout << "│ 2. Undo (Hapus Riwayat Terakhir)\n";
        cout << "│ 3. Kembali ke Menu Utama\n";
        cout << "├───────────────────────────────────────────╯\n";
        cout << "│\n";
        cout << "╰──── Pilih menu: ";
        cin >> opsi;

        switch (opsi) {
            case 1:
                displaySearchHistory();
                break;
            case 2:
                popSearchHistory();
                break;
            case 3:
                cout << "Kembali..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (opsi != 3);
}

void clearStack() {
    HistoryNode* current = stackTop;
    while (current != nullptr) {
        HistoryNode* next = current->next;
        delete current;
        current = next;
    }
    stackTop = nullptr;
}

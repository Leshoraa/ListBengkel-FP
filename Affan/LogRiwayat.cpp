#include "LogRiwayat.h"
#include <iostream>

using namespace std;

struct HistoryNode {
    string keyword;
    HistoryNode* next;
};

HistoryNode* stackTop = nullptr;
HistoryNode* redoStackTop = nullptr;

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

    // Bersihkan stack redo ketika ada pencarian baru
    while (redoStackTop) {
        HistoryNode* temp = redoStackTop;
        redoStackTop = redoStackTop->next;
        delete temp;
    }
}

void popSearchHistory() {
    if (!stackTop) {
        cout << "Tidak ada riwayat untuk dihapus (Undo)." << endl;
        return;
    }
    HistoryNode* temp = stackTop;
    stackTop = stackTop->next;
    
    // Simpan ke redo stack
    temp->next = redoStackTop;
    redoStackTop = temp;
    
    cout << "Riwayat pencarian terakhir ('" << temp->keyword << "') telah di-Undo." << endl;
}

void redoSearchHistory() {
    if (!redoStackTop) {
        cout << "Tidak ada riwayat untuk dikembalikan (Redo)." << endl;
        return;
    }
    HistoryNode* temp = redoStackTop;
    redoStackTop = redoStackTop->next;
    
    // Kembalikan ke undo stack
    temp->next = stackTop;
    stackTop = temp;
    
    cout << "Riwayat pencarian ('" << temp->keyword << "') telah di-Redo." << endl;
}

void menuLogRiwayat() {
    int opsi;
    do {
        cout << "\n╭───────────────────────────────────────────╮\n";
        cout << "│ LOG RIWAYAT (Pencarian)\n";
        cout << "├───────────────────────────────────────────╯\n";
        cout << "│ 1. Tampilkan Riwayat\n";
        cout << "│ 2. Undo (Hapus Riwayat Terakhir)\n";
        cout << "│ 3. Redo (Kembalikan Riwayat)\n";
        cout << "│ 4. Kembali ke Menu Utama\n";
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
                redoSearchHistory();
                break;
            case 4:
                cout << "Kembali..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (opsi != 4);
}

void clearStack() {
    HistoryNode* current = stackTop;
    while (current != nullptr) {
        HistoryNode* next = current->next;
        delete current;
        current = next;
    }
    stackTop = nullptr;

    current = redoStackTop;
    while (current != nullptr) {
        HistoryNode* next = current->next;
        delete current;
        current = next;
    }
    redoStackTop = nullptr;
}

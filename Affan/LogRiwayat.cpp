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

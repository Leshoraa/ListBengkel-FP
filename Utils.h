#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Warna ANSI
const string RESET   = "\033[0m";
const string MERAH   = "\033[1;31m";
const string HIJAU   = "\033[1;32m";
const string KUNING  = "\033[1;33m";
const string BIRU    = "\033[1;34m";
const string CYAN    = "\033[1;36m";

// Fungsi Validasi Input Angka (Anti-Crash)
inline int ambilInputAngka() {
    int angka;
    while (!(cin >> angka)) {
        cout << MERAH << "│ Error: Input harus berupa angka! Silakan ulangi: " << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return angka;
}

#endif

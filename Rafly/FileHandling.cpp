#include "FileHandling.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string NAMA_FILE = "data_bengkel.txt";

// Menyimpan data array Bengkel ke dalam file
void saveData(Bengkel data[], int n) {
    ofstream file(NAMA_FILE);
    if (!file.is_open()) {
        cerr << "Gagal membuka file untuk menyimpan data!" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        file << data[i].id << "|"
             << data[i].nama << "|"
             << data[i].jenis_layanan << "|"
             << data[i].alamat << "|"
             << data[i].no_telepon << endl;
    }
    
    file.close();
}

// Membaca data dari file dan memasukkannya ke dalam array Bengkel
void loadData(Bengkel data[], int &n) {
    ifstream file(NAMA_FILE);
    if (!file.is_open()) {
        // File mungkin belum ada jika ini pertama kali dijalankan
        return; 
    }

    n = 0;
    string line;
    while (getline(file, line) && n < MAX_DATA) {
        // Parsing line dengan delimiter '|'
        size_t pos = 0;
        
        pos = line.find('|');
        if (pos == string::npos) continue;
        data[n].id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        if (pos == string::npos) continue;
        data[n].nama = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        if (pos == string::npos) continue;
        data[n].jenis_layanan = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        if (pos == string::npos) continue;
        data[n].alamat = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        if (pos != string::npos) {
            data[n].no_telepon = line.substr(0, pos);
        } else {
            data[n].no_telepon = line;
        }
        
        n++;
    }
    
    file.close();
}

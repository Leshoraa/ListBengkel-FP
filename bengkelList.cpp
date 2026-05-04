#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

struct Bengkel {
    string id;
    string nama;
    string daerah;
    string alamat;
    string telepon;
    string pemilik;
};

struct HistoryNode {
    string kataKunci;
    HistoryNode* next;
};

struct BookingNode {
    int nomorAntrean;
    string namaPelanggan;
    BookingNode* next;
};

const int KAPASITAS_MAKSIMAL = 100;
Bengkel daftarBengkel[KAPASITAS_MAKSIMAL];
int totalBengkel = 0;

HistoryNode* stackTop = nullptr;
BookingNode* queueFront = nullptr;
BookingNode* queueRear = nullptr;

void bersihkanBufferInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string ubahKeHurufKecil(const string& teks) {
    string hasil = teks;
    for (size_t i = 0; i < hasil.length(); ++i) {
        if (hasil[i] >= 'A' && hasil[i] <= 'Z') {
            hasil[i] = hasil[i] + ('a' - 'A');
        }
    }
    return hasil;
}

void rekamRiwayat(const string& daerah) {
    HistoryNode* nodeBaru = new HistoryNode;
    nodeBaru->kataKunci = daerah;
    nodeBaru->next = stackTop;
    stackTop = nodeBaru;
}

void cetakLayarUtama() {
    cout << "=========================================\n";
    cout << "      GRAB BENGKEL - SOLUSI MOGOK\n";
    cout << "=========================================\n";
    cout << "    __o\n";
    cout << "  _ \\<_\n";
    cout << " (_)/(_)  [SISTEM BOOKING ONLINE]\n";
    cout << "=========================================\n";
    cout << "rafi" << endl;
    cout << "sandi" << endl;
}

void cariDataBengkel() {
    if (totalBengkel == 0) {
        cout << "Basis data bengkel kosong.\n";
        return;
    }
    
    string kriteriaDaerah;
    cout << "Masukkan daerah yang dicari: ";
    getline(cin, kriteriaDaerah);
    
    rekamRiwayat(kriteriaDaerah);
    
    string kriteriaHurufKecil = ubahKeHurufKecil(kriteriaDaerah);
    bool statusDitemukan = false;
    
    cout << "\nHasil Pencarian:\n";
    for (int i = 0; i < totalBengkel; i++) {
        string daerahHurufKecil = ubahKeHurufKecil(daftarBengkel[i].daerah);
        if (daerahHurufKecil.find(kriteriaHurufKecil) != string::npos) {
            cout << "- " << daftarBengkel[i].nama << " (" << daftarBengkel[i].alamat << ")\n";
            statusDitemukan = true;
        }
    }
    
    if (!statusDitemukan) {
        cout << "Data tidak ditemukan untuk wilayah " << kriteriaDaerah << ".\n";
    }
}

void tambahDataBengkel() {
    if (totalBengkel >= KAPASITAS_MAKSIMAL) {
        cout << "Kapasitas penyimpanan sistem penuh.\n";
        return;
    }
    
    Bengkel entitasBaru;
    cout << "ID Bengkel: ";
    cin >> entitasBaru.id;
    bersihkanBufferInput();
    
    cout << "Nama Bengkel: ";
    getline(cin, entitasBaru.nama);
    cout << "Daerah: ";
    getline(cin, entitasBaru.daerah);
    cout << "Alamat Lengkap: ";
    getline(cin, entitasBaru.alamat);
    cout << "Nomor Telepon: ";
    getline(cin, entitasBaru.telepon);
    cout << "Nama Pemilik: ";
    getline(cin, entitasBaru.pemilik);
    
    daftarBengkel[totalBengkel] = entitasBaru;
    totalBengkel++;
    
    cout << "Data diregistrasi dengan sukses.\n";
}

void tampilkanListTerurut() {
    if (totalBengkel == 0) {
        cout << "Basis data bengkel kosong.\n";
        return;
    }
    
    Bengkel salinanData[KAPASITAS_MAKSIMAL];
    for (int i = 0; i < totalBengkel; i++) {
        salinanData[i] = daftarBengkel[i];
    }
    
    for (int i = 0; i < totalBengkel - 1; i++) {
        int indeksMinimum = i;
        for (int j = i + 1; j < totalBengkel; j++) {
            if (salinanData[j].nama < salinanData[indeksMinimum].nama) {
                indeksMinimum = j;
            }
        }
        if (indeksMinimum != i) {
            Bengkel sementara = salinanData[i];
            salinanData[i] = salinanData[indeksMinimum];
            salinanData[indeksMinimum] = sementara;
        }
    }
    
    cout << string(90, '-') << "\n";
    cout << left << setw(10) << "ID" << setw(20) << "Nama" << setw(15) << "Daerah" << setw(20) << "Telepon" << setw(15) << "Pemilik" << "\n";
    cout << string(90, '-') << "\n";
    
    for (int i = 0; i < totalBengkel; i++) {
        cout << left << setw(10) << salinanData[i].id 
             << setw(20) << salinanData[i].nama 
             << setw(15) << salinanData[i].daerah 
             << setw(20) << salinanData[i].telepon 
             << setw(15) << salinanData[i].pemilik << "\n";
    }
    cout << string(90, '-') << "\n";
}

void hapusDataBengkelBerdasarkanIndeks(int indeksTarget) {
    for (int i = indeksTarget; i < totalBengkel - 1; i++) {
        daftarBengkel[i] = daftarBengkel[i + 1];
    }
    totalBengkel--;
}

void prosesUbahAtauHapus() {
    if (totalBengkel == 0) {
        cout << "Basis data bengkel kosong.\n";
        return;
    }
    
    string targetIdentitas;
    cout << "Masukkan ID Bengkel target modifikasi/penghapusan: ";
    cin >> targetIdentitas;
    bersihkanBufferInput();
    
    Bengkel* pointerTarget = nullptr;
    int indeksDitemukan = -1;
    
    for (int i = 0; i < totalBengkel; i++) {
        if (daftarBengkel[i].id == targetIdentitas) {
            pointerTarget = &daftarBengkel[i];
            indeksDitemukan = i;
            break;
        }
    }
    
    if (!pointerTarget) {
        cout << "Entitas dengan ID " << targetIdentitas << " tidak terdaftar.\n";
        return;
    }
    
    cout << "Aksi (1: Modifikasi, 2: Hapus): ";
    int kodeAksi;
    if (!(cin >> kodeAksi)) {
        bersihkanBufferInput();
        cout << "Input tidak valid.\n";
        return;
    }
    bersihkanBufferInput();
    
    if (kodeAksi == 1) {
        string inputBuffer;
        
        cout << "Nama Bengkel (" << pointerTarget->nama << "): ";
        getline(cin, inputBuffer);
        if (!inputBuffer.empty()) pointerTarget->nama = inputBuffer;
        
        cout << "Daerah (" << pointerTarget->daerah << "): ";
        getline(cin, inputBuffer);
        if (!inputBuffer.empty()) pointerTarget->daerah = inputBuffer;
        
        cout << "Alamat (" << pointerTarget->alamat << "): ";
        getline(cin, inputBuffer);
        if (!inputBuffer.empty()) pointerTarget->alamat = inputBuffer;
        
        cout << "Telepon (" << pointerTarget->telepon << "): ";
        getline(cin, inputBuffer);
        if (!inputBuffer.empty()) pointerTarget->telepon = inputBuffer;
        
        cout << "Pemilik (" << pointerTarget->pemilik << "): ";
        getline(cin, inputBuffer);
        if (!inputBuffer.empty()) pointerTarget->pemilik = inputBuffer;
        
        cout << "Data bengkel sukses diperbarui.\n";
    } else if (kodeAksi == 2) {
        hapusDataBengkelBerdasarkanIndeks(indeksDitemukan);
        cout << "Data bengkel dihapus dari sistem.\n";
    } else {
        cout << "Kode aksi tidak dikenali.\n";
    }
}

void mendaftarkanBooking() {
    string namaPelanggan;
    cout << "Masukkan Nama Lengkap Anda: ";
    getline(cin, namaPelanggan);
    
    int idAcak = (rand() % 100) + 1;
    
    BookingNode* pesananBaru = new BookingNode;
    pesananBaru->nomorAntrean = idAcak;
    pesananBaru->namaPelanggan = namaPelanggan;
    pesananBaru->next = nullptr;
    
    if (queueRear == nullptr) {
        queueFront = queueRear = pesananBaru;
    } else {
        queueRear->next = pesananBaru;
        queueRear = pesananBaru;
    }
    
    cout << "Registrasi Booking Sukses. Token Panggilan Anda: " << idAcak << "\n";
}

void cetakRiwayatPencarian() {
    if (stackTop == nullptr) {
        cout << "Log sistem riwayat pencarian kosong.\n";
        return;
    }
    
    cout << "Riwayat Pencarian (LIFO - Terbaru Prioritas):\n";
    HistoryNode* pointerMaju = stackTop;
    while (pointerMaju != nullptr) {
        cout << "-> " << pointerMaju->kataKunci << "\n";
        pointerMaju = pointerMaju->next;
    }
}

void pendelegasianMemoriDinamis() {
    while (stackTop != nullptr) {
        HistoryNode* simpulSementara = stackTop;
        stackTop = stackTop->next;
        delete simpulSementara;
    }
    
    while (queueFront != nullptr) {
        BookingNode* simpulSementara = queueFront;
        queueFront = queueFront->next;
        delete simpulSementara;
    }
    queueRear = nullptr;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int sesiPilihan = 0;
    
    do {
        cetakLayarUtama();
        cout << "1. Cari Bengkel (Search)\n";
        cout << "2. Register Bengkel Baru (Admin Insert)\n";
        cout << "3. Tampilkan Buku Induk Bengkel (Sorted ASC)\n";
        cout << "4. Manajemen Data Bengkel (Update/Delete)\n";
        cout << "5. Booking Servis Darurat (Queue)\n";
        cout << "6. Log Riwayat Pencarian (Stack)\n";
        cout << "7. Terminasi Sesi\n";
        cout << "=========================================\n";
        cout << "Input eksekusi: ";
        
        if (!(cin >> sesiPilihan)) {
            bersihkanBufferInput();
            continue;
        }
        bersihkanBufferInput();
        
        switch (sesiPilihan) {
            case 1: cariDataBengkel(); break;
            case 2: tambahDataBengkel(); break;
            case 3: tampilkanListTerurut(); break;
            case 4: prosesUbahAtauHapus(); break;
            case 5: mendaftarkanBooking(); break;
            case 6: cetakRiwayatPencarian(); break;
            case 7: cout << "Sesi diterminasi. Menutup modul.\n"; break;
            default: cout << "Kode operasi di luar jangkauan sistem.\n"; break;
        }
        
        if (sesiPilihan != 7) {
            cout << "\n[Enter] validasi rute layar...";
            cin.get();
            cout << string(50, '\n');
        }
        
    } while (sesiPilihan != 7);
    
    pendelegasianMemoriDinamis();
    return 0;
}

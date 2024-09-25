#include <iostream>
#include <string>

using namespace std;


const int MAKS_JUMLAH_RUMAH = 1000; 


struct Rumah { 
    int id;                   
    string alamat;           
    string harga;           
    bool terjual;           
};


void tambahRumah(Rumah* daftarRumah, int* jumlah) {
    if (*jumlah >= MAKS_JUMLAH_RUMAH) {
        cout << "Data rumah penuh!" << endl;
        return;
    }

    Rumah rumahBaru;
    bool idValid = false;


    while (!idValid) {
        cout << endl;
        cout << "Masukkan ID rumah: ";
        cin >> rumahBaru.id;

        idValid = true;
        for (int i = 0; i < *jumlah; i++) {
            if (daftarRumah[i].id == rumahBaru.id) {
                cout << "ID rumah sudah ada, silakan masukkan ID yang berbeda." << endl;
                idValid = false;
                break;
            }
        }
    }

    cout << "Masukkan alamat rumah: ";
    cin.ignore(); 
    getline(cin, rumahBaru.alamat);
    cout << "Masukkan harga rumah: ";
    getline(cin, rumahBaru.harga);
    rumahBaru.terjual = false;

    daftarRumah[*jumlah] = rumahBaru;
    (*jumlah)++;
    cout << "Rumah berhasil ditambahkan!" << endl;
}

void tampilkanRumah(const Rumah* daftarRumah, int jumlah) {
    if (jumlah == 0) {
        cout << endl;
        cout << "Belum ada data rumah." << endl;
        return;
    }
    cout << endl;
    cout << "=== Daftar Rumah ===" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << "ID: " << daftarRumah[i].id << endl;
        cout << "Alamat: " << daftarRumah[i].alamat << endl;
        cout << "Harga: " << daftarRumah[i].harga << endl;
        cout << "Status: " << (daftarRumah[i].terjual ? "Terjual" : "Belum Terjual") << endl;
        cout << "------------------------" << endl;
    }
}

void perbaruiRumah(Rumah* daftarRumah, int jumlah) {
    int id;
    cout << endl;
    cout << "Masukkan ID rumah yang ingin diperbarui: ";
    cin >> id;

    for (int i = 0; i < jumlah; i++) {
        if (daftarRumah[i].id == id) {
            cout << "Masukkan alamat baru: ";
            cin.ignore();
            getline(cin, daftarRumah[i].alamat);
            cout << "Masukkan harga baru: ";
            getline(cin, daftarRumah[i].harga);
            cout << "Informasi rumah berhasil diperbarui!" << endl;
            return;
        }
    }
    cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
}

void perbaruiStatusRumah(Rumah* daftarRumah, int jumlah) {
    int id;
    cout << endl;
    cout << "Masukkan ID rumah yang ingin diperbarui statusnya: ";
    cin >> id;

    for (int i = 0; i < jumlah; i++) {
        if (daftarRumah[i].id == id) {
            cout << "Apakah rumah sudah terjual? (1 = Ya, 0 = Tidak): ";
            cin >> daftarRumah[i].terjual;
            cout << "Status rumah berhasil diperbarui!" << endl;
            return;
        }
    }
    cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
}

void hapusRumah(Rumah* daftarRumah, int* jumlah) {
    int id;
    cout << endl;
    cout << "Masukkan ID rumah yang ingin dihapus: ";
    cin >> id;

    for (int i = 0; i < *jumlah; i++) {
        if (daftarRumah[i].id == id) {
            for (int j = i; j < (*jumlah) - 1; j++) {
                daftarRumah[j] = daftarRumah[j + 1];
            }
            (*jumlah)--; 
            cout << "Rumah berhasil dihapus!" << endl;
            return;
        }
    }
    cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
}


void tampilkanMenu() {
    cout << endl;
    cout << "=== Sistem Agen Perumahan ===" << endl;
    cout << "1. Tambah Rumah" << endl;
    cout << "2. Lihat Daftar Rumah" << endl;
    cout << "3. Update Rumah" << endl;
    cout << "4. Update Status Rumah" << endl;
    cout << "5. Hapus Rumah" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    Rumah daftarRumah[MAKS_JUMLAH_RUMAH]; 
    int jumlahRumah = 0; 

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahRumah(daftarRumah, &jumlahRumah);
                break;
            case 2:
                tampilkanRumah(daftarRumah, jumlahRumah);
                break;
            case 3:
                perbaruiRumah(daftarRumah, jumlahRumah);
                break;
            case 4:
                perbaruiStatusRumah(daftarRumah, jumlahRumah);
                break;
            case 5:
                hapusRumah(daftarRumah, &jumlahRumah);
                break;
            case 6:
                cout << "Terima kasih telah menggunakan sistem agen perumahan!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 6);

    return 0;
}

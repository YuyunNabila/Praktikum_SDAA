#include <iostream>
#include <string>

using namespace std;

struct Rumah {
    int id;
    string alamat;
    string harga;
    bool terjual;
    Rumah* next;  
};


void tambahRumah(Rumah*& head) {
    Rumah* rumahBaru = new Rumah;
    bool idValid = false;

    while (!idValid) {
        cout << endl;
        cout << "Masukkan ID rumah: ";
        cin >> rumahBaru->id;

        idValid = true;
        Rumah* temp = head;
        while (temp != nullptr) {
            if (temp->id == rumahBaru->id) {
                cout << "ID rumah sudah ada, silakan masukkan ID yang berbeda." << endl;
                idValid = false;
                break;
            }
            temp = temp->next;
        }
    }

    cout << "Masukkan alamat rumah: ";
    cin.ignore();
    getline(cin, rumahBaru->alamat);
    cout << "Masukkan harga rumah: ";
    getline(cin, rumahBaru->harga);
    rumahBaru->terjual = false;
    rumahBaru->next = nullptr;

    if (head == nullptr) {
        head = rumahBaru;
    } else {
        Rumah* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = rumahBaru;
    }

    cout << "Rumah berhasil ditambahkan!" << endl;
}

void tampilkanRumah(Rumah* head) {
    if (head == nullptr) {
        cout << "Belum ada data rumah." << endl;
        return;
    }

    Rumah* temp = head;
    cout << "=== Daftar Rumah ===" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << endl;
        cout << "Alamat: " << temp->alamat << endl;
        cout << "Harga: " << temp->harga << endl;
        cout << "Status: " << (temp->terjual ? "Terjual" : "Belum Terjual") << endl;
        cout << "------------------------" << endl;
        temp = temp->next;
    }
}

void perbaruiRumah(Rumah* head) {
    int id;
    cout << "Masukkan ID rumah yang ingin diperbarui: ";
    cin >> id;

    Rumah* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Masukkan alamat baru: ";
            cin.ignore();
            getline(cin, temp->alamat);
            cout << "Masukkan harga baru: ";
            getline(cin, temp->harga);
            cout << "Informasi rumah berhasil diperbarui!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
}

void perbaruiStatusRumah(Rumah* head) {
    int id;
    cout << "Masukkan ID rumah yang ingin diperbarui statusnya: ";
    cin >> id;

    Rumah* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Apakah rumah sudah terjual? (1 = Ya, 0 = Tidak): ";
            cin >> temp->terjual;
            cout << "Status rumah berhasil diperbarui!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
}

void hapusRumah(Rumah*& head) {
    int id;
    cout << "Masukkan ID rumah yang ingin dihapus: ";
    cin >> id;

    Rumah* temp = head;
    Rumah* prev = nullptr;

    while (temp != nullptr) {
        if (temp->id == id) {
            if (prev == nullptr) {
                head = temp->next;  
            } else {
                prev->next = temp->next; 
            }
            delete temp;
            cout << "Rumah berhasil dihapus!" << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
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
    Rumah* head = nullptr;  

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahRumah(head);
                break;
            case 2:
                tampilkanRumah(head);
                break;
            case 3:
                perbaruiRumah(head);
                break;
            case 4:
                perbaruiStatusRumah(head);
                break;
            case 5:
                hapusRumah(head);
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

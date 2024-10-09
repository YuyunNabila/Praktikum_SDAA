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

// Stack Node
struct StackNode {
    Rumah* rumah;
    StackNode* next;
};

// Queue Node
struct QueueNode {
    Rumah* rumah;
    QueueNode* next;
};

class Stack {
private:
    StackNode* top;

public:
    Stack() : top(nullptr) {}

    void push(Rumah* rumah) {
        StackNode* newNode = new StackNode{ rumah, top };
        top = newNode;
    }

    Rumah* pop() {
        if (top == nullptr) return nullptr;
        StackNode* temp = top;
        Rumah* rumah = top->rumah;
        top = top->next;
        delete temp;
        return rumah;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(Rumah* rumah) {
        QueueNode* newNode = new QueueNode{ rumah, nullptr };
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Rumah* dequeue() {
        if (front == nullptr) return nullptr;
        QueueNode* temp = front;
        Rumah* rumah = front->rumah;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return rumah;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

void tambahRumahBiasa(Rumah*& head) {
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
    rumahBaru->next = head;
    head = rumahBaru;
}

void tampilkanRumahBiasa(Rumah* head) {
    Rumah* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Alamat: " << temp->alamat << ", Harga: " << temp->harga << ", Terjual: " << (temp->terjual ? "Ya" : "Tidak") << endl;
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
            cout << "Status terjual (1 untuk ya, 0 untuk tidak): ";
            cin >> temp->terjual;
            cout << "Rumah berhasil diperbarui!" << endl;
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

void menuTambahRumah(Rumah*& head, Stack& rumahStack, Queue& rumahQueue) {
    int pilihanTambah;
    cout << endl;
    cout << "Pilih jenis tambah data:" << endl;
    cout << "1. Tambah rumah biasa" << endl;
    cout << "2. Tambah rumah ke stack" << endl;
    cout << "3. Tambah rumah ke queue" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihanTambah;

    switch (pilihanTambah) {
        case 1:
            tambahRumahBiasa(head);
            break;
        case 2: {
            int id;
            cout << "Masukkan ID rumah yang ingin ditambahkan ke stack: ";
            cin >> id;
            Rumah* temp = head;
            while (temp != nullptr) {
                if (temp->id == id) {
                    rumahStack.push(temp);
                    cout << "Rumah berhasil ditambahkan ke stack!" << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
            break;
        }
        case 3: {
            int id;
            cout << "Masukkan ID rumah yang ingin ditambahkan ke queue: ";
            cin >> id;
            Rumah* temp = head;
            while (temp != nullptr) {
                if (temp->id == id) {
                    rumahQueue.enqueue(temp);
                    cout << "Rumah berhasil ditambahkan ke queue!" << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Rumah dengan ID " << id << " tidak ditemukan." << endl;
            break;
        }
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

void menuLihatRumah(Rumah* head, Stack& rumahStack, Queue& rumahQueue) {
    int pilihanLihat;
    cout << endl;
    cout << "Pilih jenis lihat data:" << endl;
    cout << "1. Lihat data biasa" << endl;
    cout << "2. Ambil data dari stack" << endl;
    cout << "3. Ambil data dari queue" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihanLihat;

    switch (pilihanLihat) {
        case 1:
            tampilkanRumahBiasa(head);
            break;
        case 2: {
            Rumah* rumah = rumahStack.pop();
            if (rumah != nullptr) {
                cout << "Rumah diambil dari stack:" << endl;
                cout << "ID: " << rumah->id << ", Alamat: " << rumah->alamat << ", Harga: " << rumah->harga << ", Terjual: " << (rumah->terjual ? "Ya" : "Tidak") << endl;
            } else {
                cout << "Stack kosong!" << endl;
            }
            break;
        }
        case 3: {
            Rumah* rumah = rumahQueue.dequeue();
            if (rumah != nullptr) {
                cout << "Rumah diambil dari queue:" << endl;
                cout << "ID: " << rumah->id << ", Alamat: " << rumah->alamat << ", Harga: " << rumah->harga << ", Terjual: " << (rumah->terjual ? "Ya" : "Tidak") << endl;
            } else {
                cout << "Queue kosong!" << endl;
            }
            break;
        }
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

void tampilkanMenu() {
    cout << endl;
    cout << "=== Sistem jual beli Perumahan ===" << endl;
    cout << "1. Tambah Rumah" << endl;
    cout << "2. Lihat Rumah" << endl;
    cout << "3. Perbarui Rumah" << endl;
    cout << "4. Hapus Rumah" << endl;
    cout << "5. Exit" << endl;
    cout << "Masukkan pilihan: ";
}

int main() {
    Rumah* head = nullptr;
    Stack rumahStack;
    Queue rumahQueue;
    int pilihan;

    while (true) {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                menuTambahRumah(head, rumahStack, rumahQueue);
                break;
            case 2:
                menuLihatRumah(head, rumahStack, rumahQueue);
                break;
            case 3:
                perbaruiRumah(head);
                break;
            case 4:
                hapusRumah(head);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    }

    return 0;
}

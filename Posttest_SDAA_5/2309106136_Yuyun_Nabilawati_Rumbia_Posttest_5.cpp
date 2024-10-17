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

// Fungsi untuk merge sort (ascending)
Rumah* merge(Rumah* left, Rumah* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->id < right->id) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Rumah* mergeSort(Rumah* head) {
    if (!head || !head->next) return head;

    Rumah* slow = head;
    Rumah* fast = head->next;

    // Memisahkan list menjadi dua bagian
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Rumah* mid = slow->next;
    slow->next = nullptr;

    // Rekursi untuk membagi dan mengurutkan
    Rumah* left = mergeSort(head);
    Rumah* right = mergeSort(mid);

    return merge(left, right);
}

// Fungsi untuk quick sort (descending)
Rumah* partition(Rumah* head, Rumah* end, Rumah** newHead, Rumah** newEnd) {
    Rumah* pivot = end;
    Rumah* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->id > pivot->id) {  // Descending order
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            Rumah* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;

    return pivot;
}

Rumah* getTail(Rumah* cur);

Rumah* quickSortRecursive(Rumah* head, Rumah* end) {
    if (!head || head == end) return head;

    Rumah* newHead = nullptr, *newEnd = nullptr;
    Rumah* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Rumah* temp = newHead;
        while (temp->next != pivot) temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecursive(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecursive(pivot->next, newEnd);

    return newHead;
}

Rumah* getTail(Rumah* cur) {
    while (cur != nullptr && cur->next != nullptr) cur = cur->next;
    return cur;
}

Rumah* quickSort(Rumah* head) {
    return quickSortRecursive(head, getTail(head));
}

// Fungsi menambah rumah biasa
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

// Fungsi untuk menampilkan rumah
void tampilkanRumahBiasa(Rumah* head) {
    Rumah* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Alamat: " << temp->alamat << ", Harga: " << temp->harga << ", Terjual: " << (temp->terjual ? "Ya" : "Tidak") << endl;
        temp = temp->next;
    }
}

// Fungsi memperbarui rumah
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

// Fungsi menghapus rumah
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

// Menu untuk menambah rumah
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

// Menu untuk melihat rumah
void menuLihatRumah(Rumah*& head, Stack& rumahStack, Queue& rumahQueue) {
    int pilihanLihat;
    cout << endl;
    cout << "Pilih jenis lihat data:" << endl;
    cout << "1. Lihat data biasa" << endl;
    cout << "2. Ambil data dari stack" << endl;
    cout << "3. Ambil data dari queue" << endl;
    cout << "4. Sorting data ascending (merge sort)" << endl;
    cout << "5. Sorting data descending (quick sort)" << endl;
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
        case 4: {
            head = mergeSort(head);
            cout << "Data setelah diurutkan secara ascending (merge sort):" << endl;
            tampilkanRumahBiasa(head);
            break;
        }
        case 5: {
            head = quickSort(head);
            cout << "Data setelah diurutkan secara descending (quick sort):" << endl;
            tampilkanRumahBiasa(head);
            break;
        }
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

int main() {
    Rumah* head = nullptr;
    Stack rumahStack;
    Queue rumahQueue;
    int pilihan;

    do {
        cout << endl;
        cout << "=== Menu Rumah ===" << endl;
        cout << "1. Tambah rumah" << endl;
        cout << "2. Lihat rumah" << endl;
        cout << "3. Perbarui rumah" << endl;
        cout << "4. Hapus rumah" << endl;
        cout << "5. Keluar" << endl;
        cout << "Masukkan pilihan: ";
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
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihan != 5);

    return 0;
}

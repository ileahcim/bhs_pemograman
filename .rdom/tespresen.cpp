#include <iostream>
using namespace std;

// Deklarasi struktur Node
struct Node {
    int data;
    Node* next;
};

// Deklarasi struktur LinkedList
struct LinkedList {
    Node* head;

    LinkedList() {
        head = NULL;
    }

    // Fungsi untuk membuat node baru
    Node* buatNode(int data) {
        Node* nodeBaru = new Node;
        nodeBaru->data = data;
        nodeBaru->next = NULL;
        return nodeBaru;
    }

    // Fungsi untuk menambah node di awal
    void insertDepan(int data) {
        Node* nodeBaru = buatNode(data);
        nodeBaru->next = head;
        head = nodeBaru;
    }

    // Fungsi untuk menambah node di tengah setelah nilai tertentu
    void insertTengah(int data, int setelahData) {
        Node* nodeBaru = buatNode(data);
        Node* current = head;
        while (current != NULL && current->data != setelahData) {
            current = current->next;
        }
        if (current != NULL) {
            nodeBaru->next = current->next;
            current->next = nodeBaru;
        } else {
            cout << "Node dengan data " << setelahData << " tidak ditemukan!" << endl;
        }
    }

    // Fungsi untuk menambah node di akhir
    void insertBelakang(int data) {
        Node* nodeBaru = buatNode(data);
        if (head == NULL) {
            head = nodeBaru;
            return;
        }
        Node* nodeAkhir = head;
        while (nodeAkhir->next != NULL) {
            nodeAkhir = nodeAkhir->next;
        }
        nodeAkhir->next = nodeBaru;
    }

    // Fungsi untuk menghapus node di awal
    void hapusDepan() {
        if (head == NULL) {
            cout << "Linked list kosong." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Fungsi untuk menghapus node di tengah berdasarkan nilai tertentu
    void hapusTengah(int data) {
        if (head == NULL) {
            cout << "Linked list kosong." << endl;
            return;
        }
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* prevNode = head;
        while (prevNode->next != NULL && prevNode->next->data != data) {
            prevNode = prevNode->next;
        }
        if (prevNode->next == NULL) {
            cout << "Node dengan data " << data << " tidak ditemukan." << endl;
            return;
        }
        Node* temp = prevNode->next;
        prevNode->next = temp->next;
        delete temp;
    }

    // Fungsi untuk menghapus node di akhir
    void hapusAkhir() {
        if (head == NULL) {
            cout << "Linked list kosong." << endl;
            return;
        }
        Node* temp = head;
        Node* prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            head = NULL;
        }
        delete temp;
    }

    // Fungsi untuk menampilkan linked list
    void tampilkan() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList list;
    char pilihan;
    int data, key;

    do {
        cout << "\nPilihan Menu:\n";
        cout << "1. Insert Depan\n";
        cout << "2. Insert Tengah\n";
        cout << "3. Insert Belakang\n";
        cout << "4. Hapus Depan\n";
        cout << "5. Hapus Tengah\n";
        cout << "6. Hapus Akhir\n";
        cout << "7. Tampilkan Data\n";
        cout << "8. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case '1':
                cout << "Masukkan data untuk disisipkan di depan: ";
                cin >> data;
                list.insertDepan(data);
                break;
            case '2':
                cout << "Masukkan data node sebelumnya (key): ";
                cin >> key;
                cout << "Masukkan data: ";
                cin >> data;
                list.insertTengah(data, key);
                break;
            case '3':
                cout << "Masukkan data untuk disisipkan di belakang: ";
                cin >> data;
                list.insertBelakang(data);
                break;
            case '4':
                list.hapusDepan();
                break;
            case '5':
                cout << "Masukkan data node yang ingin dihapus: ";
                cin >> key;
                list.hapusTengah(key);
                break;
            case '6':
                list.hapusAkhir();
                break;
            case '7':
                list.tampilkan();
                break;
            case '8':
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != '8');

    return 0;
}
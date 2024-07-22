#include <iostream>
using namespace std;

void menu() {
    cout << "Pilihan menu:\n";
    cout << "1. Tambah\n";
    cout << "2. Kurang\n";
    cout << "3. Kali\n";
    cout << "4. Bagi\n";
}

void tambah() {
    int a, b;
    cout << "Masukkan dua angka untuk penjumlahan: ";
    cin >> a >> b;
    cout << "Hasil penjumlahan: " << a + b << endl;
}

void kurang() {
    int a, b;
    cout << "Masukkan dua angka untuk pengurangan: ";
    cin >> a >> b;
    cout << "Hasil pengurangan: " << a - b << endl;
}

void kali() {
    int a, b;
    cout << "Masukkan dua angka untuk perkalian: ";
    cin >> a >> b;
    cout << "Hasil perkalian: " << a * b << endl;
}

void bagi() {
    int a, b;
    cout << "Masukkan dua angka untuk pembagian: ";
    cin >> a >> b;
    if (b != 0) {
        cout << "Hasil pembagian: " << static_cast<float>(a) / b << endl;
    } else {
        cout << "Tidak bisa melakukan pembagian dengan nol\n";
    }
}

int main() {
    menu();
    tambah();
    kurang();
    kali();
    bagi();
    return 0;
}

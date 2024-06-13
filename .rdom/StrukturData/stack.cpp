#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

class TumpukanBuku {
private:
    // Tumpukan buku yang digunakan untuk menyimpan nama buku
    stack<string> tumpukan;

public:
    // Metode untuk menambahkan buku ke tumpukan
    void tambah(const string& buku) {
        tumpukan.push(buku);
        cout << "Buku \"" << buku << "\" telah ditambahkan ke tumpukan.\n";
    }

    // Metode untuk menghapus buku dari tumpukan
    void hapus() {
        if (tumpukan.empty()) {
            cout << "Tumpukan kosong. Tidak ada buku untuk dihapus.\n";
        } else {
            string bukuTeratas = tumpukan.top();
            tumpukan.pop();
            cout << "Buku \"" << bukuTeratas << "\" telah dihapus dari tumpukan.\n";
        }
    }

    // Metode untuk melihat buku teratas tanpa menghapusnya
    void lihat() const {
        if (tumpukan.empty()) {
            cout << "Tumpukan kosong. Tidak ada buku untuk dilihat.\n";
        } else {
            cout << "Buku teratas: \"" << tumpukan.top() << "\"\n";
        }
    }

    // Metode untuk mengecek apakah tumpukan kosong atau tidak
    bool kosong() const {
        return tumpukan.empty();
    }

    // Metode untuk mengetahui ukuran tumpukan buku
    int ukuran() const {
        return tumpukan.size();
    }
};

// Fungsi untuk mengubah string menjadi huruf kecil
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main() {
    TumpukanBuku tumpukanBuku;
    string perintah;
    
    // Sementara program sedang berjalan, akan meminta pengguna untuk memilih operasi
    while (true) {
        cout << "Masukkan operasi (push, pop, peek, isEmpty, size, exit): ";
        cin >> perintah;

        // Konversi perintah menjadi huruf kecil
        perintah = toLowerCase(perintah);

        // Berdasarkan perintah yang diberikan oleh pengguna, akan dilakukan operasi yang sesuai
        if (perintah == "push") {
            cout << "Masukkan nama buku: ";
            cin.ignore(); 
            string buku;
            getline(cin, buku);
            tumpukanBuku.tambah(buku);
        } else if (perintah == "pop") {
            tumpukanBuku.hapus();
        } else if (perintah == "peek") {
            tumpukanBuku.lihat();
        } else if (perintah == "isempty") {
            if (tumpukanBuku.kosong()) {
                cout << "Tumpukan kosong.\n";
            } else {
                cout << "Tumpukan tidak kosong.\n";
            }
        } else if (perintah == "size") {
            cout << "Ukuran tumpukan: " << tumpukanBuku.ukuran() << "\n";
        } else if (perintah == "exit") {
            break;
        } else {
            cout << "Perintah tidak dikenali.\n";
        }
    }

    return 0;
}

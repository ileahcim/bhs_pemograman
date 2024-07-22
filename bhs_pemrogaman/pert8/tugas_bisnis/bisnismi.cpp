#include <iostream>
#include <string>

using namespace std; // Added this line

class MieAyamBusiness {
private:
    int modal;
    int penjualan;
    int pengeluaran;
    string strategiPemasaran;

public:
    MieAyamBusiness(int m, int p, int peng, string sp) : modal(m), penjualan(p), pengeluaran(peng), strategiPemasaran(sp) {}

    void analisisKeuangan() {
        int laba = penjualan - pengeluaran;
        cout << "Laba/Rugi: " << laba << endl;
        if (laba > 0) {
            cout << "Bisnis berjalan dengan baik." << endl;
        } else {
            cout << "Perlu evaluasi bisnis." << endl;
        }
    }

    void setStrategiPemasaran(string sp) {
        strategiPemasaran = sp;
    }

    void getStrategiPemasaran() {
        cout << "Strategi Pemasaran: " << strategiPemasaran << endl;
    }
};

int main() {
    int modalAwal;
    int totalPenjualan;
    int totalPengeluaran;
    string strategi;

    cout << "Masukkan modal awal: ";
    cin >> modalAwal;

    cout << "Masukkan total penjualan: ";
    cin >> totalPenjualan;

    cout << "Masukkan total pengeluaran: ";
    cin >> totalPengeluaran;

    cout << "Masukkan strategi pemasaran: ";
    cin.ignore();
    getline(cin, strategi);

    MieAyamBusiness bisnisMieAyam(modalAwal, totalPenjualan, totalPengeluaran, strategi);

    bisnisMieAyam.analisisKeuangan();
    bisnisMieAyam.getStrategiPemasaran();

    return 0;
}

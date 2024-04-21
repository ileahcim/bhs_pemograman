#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string judul;
    string pengarang;
    int tahun;
};

int main() {
    Buku bku1;
    Buku bku2;

    cout << "==========================" <<endl;
    bku1.judul = "Tutor Gaming";
    bku1.pengarang = "Micel";
    bku1.tahun = 2022;

    cout << "Judul		:" << bku1.judul << endl;
    cout << "Pengarang	:" << bku1.pengarang << endl;
    cout << "Tahun		:" << bku1.tahun << endl;
    
	

	cout << "==========================" <<endl;

    bku2.judul = "Cara Coding";
    bku2.pengarang = "Moci";
    bku2.tahun = 2222;

    cout << "Judul		:" << bku2.judul << endl;
    cout << "Pengarang	:" << bku2.pengarang << endl;
    cout << "Tahun		:" << bku2.tahun << endl;

    return 0;

}

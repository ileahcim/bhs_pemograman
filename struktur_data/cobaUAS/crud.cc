#include <iostream>
#include <mysql/mysql.h>
#include <sstream>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "cpp_crud";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Menghubungkan ke database berhasil." << endl;
        } else {
            cerr << "Koneksi gagal." << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init failed" << endl;
    }
    return conn;
}

void create_perbukuan(const string& judul, const string& penulis, const string& penerbit, const string& tahun_terbit, const string& isbn) {
    MYSQL* conn = connect_db();
    if (conn) {
        string query = "INSERT INTO klsss (judul, penulis, penerbit, tahun_terbit, isbn) VALUES ('" + judul + "', '" + penulis + "', '" + penerbit + "', '" + tahun_terbit + "', '" + isbn  + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "INSERT gagal" << mysql_error(conn) << endl;
        } else {
            cout << "Berhasil membuat data." << endl;
        }
        mysql_close(conn);
    }
}

void get_perbukuan() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM klsss")) {
            cerr << "SELECT gagal" << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "\nID: " << row[0] << "\nJudul        : " << row[1] << "\nPenulis       : " << row[2] << "\nPenerbit     : " << row[3] << "\nTahun Terbit : " << row[4] << "\nISBN          : " << row[5] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_perbukuan(int perbukuan_id ,const string& judul, const string& penulis, const string& penerbit , const string& tahun_terbit, const string& isbn) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE klsss SET judul = '" << judul << "', penulis = '" << penulis << "', penerbit = '" << penerbit << "', tahun_terbit = '" << tahun_terbit << "', isbn = '" << isbn << "' WHERE id = " << perbukuan_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal" << mysql_error(conn) << endl;
        } else {
            cout << "Data berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

void delete_perbukuan(int perbukuan_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM klsss  WHERE id = " << perbukuan_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal" << mysql_error(conn) << endl;
        } else {
            cout << "Data berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void admin_menu() {
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Memasukkan Data Perbukuan\n";
        cout << "2. Tampilkan Semua Data Perbukuan\n";
        cout << "3. Memperbarui Data Perbukuan\n";
        cout << "4. Hapus Data Perbukuan\n";
        cout << "5. Exit\n";
        cout << "Masukkan Pilihan : ";
        cin >> choice;

        if (choice == 1) {
            string judul, penulis, penerbit, tahun_terbit, isbn;
            cout << "\nMasukkan Judul : ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan Penulis : ";
            getline(cin, penulis);
            cout << "Masukkan Penerbit : ";
            getline(cin, penerbit);
            cout << "Masukkan Tahun Terbit: ";
            getline(cin, tahun_terbit);
            cout << "Masukkan ISBN: ";
            getline(cin, isbn);
            create_perbukuan(judul, penulis, penerbit, tahun_terbit, isbn);
        } else if (choice == 2) {
            get_perbukuan();
        } else if (choice == 3) {
            int perbukuan_id;
            string judul, penulis, penerbit, tahun_terbit, isbn;
            cout << "Masukkan user ID Untuk Diperbarui : ";
            cin >> perbukuan_id;
            cin.ignore();
            cout << "Masukkan Judul Baru : ";
            getline(cin, judul);
            cout << "Masukkan Penulis Baru : ";
            getline(cin, penulis);
            cout << "Masukkan Penerbit Baru : ";
            getline(cin, penerbit);
            cout << "Masukkan Tahun Terbit Baru : ";
            getline(cin, tahun_terbit);
            cout << "Masukkan ISBN Baru : ";
            getline(cin, isbn);
            update_perbukuan(perbukuan_id, judul, penulis, penerbit, tahun_terbit, isbn);
        } else if (choice == 4) {
            int perbukuan_id;
            cout << "Masukkan user ID Untuk Dihapus: ";
            cin >> perbukuan_id;
            delete_perbukuan(perbukuan_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silahkan coba lagi." << endl;
        }
    }
}

void user_menu() {
    int choice;
    while (true) {
        cout << "\nMenu User:\n";
        cout << "1. Tampilkan Data Perbukuan\n";
        cout << "2. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            get_perbukuan();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silahkan coba lagi." << endl;
        }
    }
}

int main() {
    int role;
    cout << "1. Admin\n2. User\nMasukkan peran anda : ";
    cin >> role;

    if (role == 1) {
        admin_menu();
    } else if (role == 2) {
        user_menu();
    } else {
        cout << "Peran tidak valid. Program akan keluar." << endl;
    }

    return 0;
}
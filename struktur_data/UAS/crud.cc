#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <string>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "perpustakaan";
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
            cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init gagal" << endl;
    }
    return conn;
}

void register_admin(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    if (conn) {
        string query = "INSERT INTO admins (username, password) VALUES ('" + username + "', '" + password + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Registrasi gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Registrasi berhasil." << endl;
        }
        mysql_close(conn);
    }
}

bool login_admin(const string& username, const string& password) {
    MYSQL* conn = connect_db();
    if (conn) {
        string query = "SELECT * FROM admins WHERE username = '" + username + "' AND password = '" + password + "'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "Login gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return false;
        }
        MYSQL_RES* res = mysql_store_result(conn);
        bool logged_in = mysql_num_rows(res) > 0;
        mysql_free_result(res);
        mysql_close(conn);
        if (logged_in) {
            cout << "Login berhasil." << endl;
        } else {
            cout << "Username atau password salah." << endl;
        }
        return logged_in;
    }
    return false;
}

void create_perbukuan(const string& judul, const string& penulis, const string& penerbit, const string& tahun_terbit, const string& id) {
    MYSQL* conn = connect_db();
    if (conn) {
        string query = "INSERT INTO perbukuan (judul, penulis, penerbit, tahun_terbit, id) VALUES ('" + judul + "', '" + penulis + "', '" + penerbit + "', '" + tahun_terbit + "', '" + id + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "INSERT gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Berhasil membuat data." << endl;
        }
        mysql_close(conn);
    }
}

void data_buku() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM perbukuan")) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "\nID: " << row[0] << "\nJudul: " << row[1] << "\nPenulis: " << row[2] << "\nPenerbit: " << row[3] << "\nTahun Terbit: " << row[4] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_buku(int perbukuan_id, const string& judul, const string& penulis, const string& penerbit, const string& tahun_terbit, const string& id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE perbukuan SET judul = '" << judul << "', penulis = '" << penulis << "', penerbit = '" << penerbit << "', tahun_terbit = '" << tahun_terbit << "', id = '" << id << "' WHERE id = " << perbukuan_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Data berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

void hapus_buku(int perbukuan_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM perbukuan WHERE id = " << perbukuan_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Data berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

void admin_menu() {
    while (true) {
        int choice;
        cout << "\nMenu Admin:\n";
        cout << "1. Input buku baru\n";
        cout << "2. Tampilkan Semua buku\n";
        cout << "3. Memperbarui Data Perbukuan\n";
        cout << "4. Hapus Data buku\n";
        cout << "5. Keluar\n";
        cout << "Masukkan Pilihan: ";
        cin >> choice;

        if (choice == 1) {
            string judul, penulis, penerbit, tahun_terbit, id;
            cout << "\nMasukkan Judul: ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan Penulis: ";
            getline(cin, penulis);
            cout << "Masukkan Penerbit: ";
            getline(cin, penerbit);
            cout << "Masukkan Tahun Terbit: ";
            getline(cin, tahun_terbit);
            cout << "Masukkan ID: ";
            getline(cin, id);
            create_perbukuan(judul, penulis, penerbit, tahun_terbit, id);
        } else if (choice == 2) {
            data_buku();
        } else if (choice == 3) {
            int perbukuan_id;
            string judul, penulis, penerbit, tahun_terbit, id;
            cout << "Masukkan ID untuk diperbarui: ";
            cin >> perbukuan_id;
            cin.ignore();
            cout << "Masukkan Judul Baru: ";
            getline(cin, judul);
            cout << "Masukkan Penulis Baru: ";
            getline(cin, penulis);
            cout << "Masukkan Penerbit Baru: ";
            getline(cin, penerbit);
            cout << "Masukkan Tahun Terbit Baru: ";
            getline(cin, tahun_terbit);
            cout << "Masukkan ID Baru: ";
            getline(cin, id);
            update_buku(perbukuan_id, judul, penulis, penerbit, tahun_terbit, id);
        } else if (choice == 4) {
            int perbukuan_id;
            cout << "Masukkan ID untuk dihapus: ";
            cin >> perbukuan_id;
            hapus_buku(perbukuan_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silahkan coba lagi." << endl;
        }
    }
}

void user_menu() {
    while (true) {
        int choice;
        cout << "\nMenu User:\n";
        cout << "1. Tampilkan Data Perbukuan\n";
        cout << "2. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            data_buku();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silahkan coba lagi." << endl;
        }
    }
}

void admin_login_or_register() {
    while (true) {
        int choice;
        cout << "\nMenu Admin:\n";
        cout << "1. Registrasi Admin\n";
        cout << "2. Login Admin\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Masukkan Username: ";
            cin >> username;
            cout << "Masukkan Password: ";
            cin >> password;
            register_admin(username, password);
        } else if (choice == 2) {
            string username, password;
            cout << "Masukkan Username: ";
            cin >> username;
            cout << "Masukkan Password: ";
            cin >> password;
            if (login_admin(username, password)) {
                admin_menu();
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silahkan coba lagi." << endl;
        }
    }
}

int main() {
    int role;
    cout << "1. Admin\n2. User\nMasukkan peran anda: ";
    cin >> role;

    if (role == 1) {
        admin_login_or_register();
    } else if (role == 2) {
        user_menu();
    } else {
        cout << "Peran tidak valid. Program akan keluar." << endl;
    }

    return 0;
}

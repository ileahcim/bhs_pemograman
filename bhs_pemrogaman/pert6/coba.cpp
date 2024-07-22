// Struct Untuk Bookstore atau Toko Buku

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string publisher;
    double price;
};

vector<Book> bookstore;

void addBook(int id, string title, string author, string publisher, double price) {
    Book newBook = {id, title, author, publisher, price};
    bookstore.push_back(newBook);
}

void clearScreen() {
    // Output ANSI escape sequence to clear screen
    cout << "\033[2J\033[1;1H";
}

void displayBooks() {
    cout << left << setw(10) << "ID" << setw(20) << "Title" << setw(20) << "Author" << setw(20) << "Publisher" << setw(10) << "Price" << endl;
    for (const auto &book : bookstore) {
        cout << left << setw(10) << book.id << setw(20) << book.title << setw(20) << book.author << setw(20) << book.publisher << setw(10) << book.price << endl;
    }
}

void displayBook(const Book &book) {
    cout << left << setw(10) << "ID" << setw(20) << "Title" << setw(20) << "Author" << setw(20) << "Publisher" << setw(10) << "Price" << endl;
    cout << left << setw(10) << book.id << setw(20) << book.title << setw(20) << book.author << setw(20) << book.publisher << setw(10) << book.price << endl;
}

void searchBook(int id) {
    auto it = find_if(bookstore.begin(), bookstore.end(), [&id](const Book& book) { return book.id == id; });
    if (it != bookstore.end()) {
        cout << "Book found:" << endl;
        displayBook(*it);
    } else {
        cout << "Book not found. Please search again with the correct ID." << endl;
    }
    getchar();
}

int main() {
    int choice;
    int id;
    string title;
    string author;
    string publisher;
    double price;

    while (true) {
    clearScreen();
    cout << "1. Add book to database\n2. Display all books\n3. Search for a book\n4. Exit\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            clearScreen();
            cout << "Enter book ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear the input buffer

            cout << "Enter book title: ";
            getline(cin, title);

            cout << "Enter book author: ";
            getline(cin, author);

            cout << "Enter book publisher: ";
            getline(cin, publisher);

            cout << "Enter book price: ";
            cin >> price;

            addBook(id, title, author, publisher, price);
            break;
        case 2:
            getchar();
            clearScreen();
            displayBooks();
            cout << endl;
            cout << "Press Any Key To Continue..." ;   
            getchar();
            break;
        case 3:
            clearScreen();
            cout << "Enter book ID: ";
            cin >> id;
            searchBook(id);
            cout << endl;
            cout << "Press Any Key To Continue..." ;
            getchar();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice." << endl;
    }
}
}
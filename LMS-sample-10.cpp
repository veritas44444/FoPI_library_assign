#include <iostream>
#include <string>
using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    int issuedTo;
};

// Member structure
struct Member {
    int id;
    string name;
    int booksIssued;
};

int main() {

    const int MAX_BOOKS = 10;
    const int MAX_MEMBERS = 10;

    // ---------- SAMPLE BOOK DATA ----------
    Book books[MAX_BOOKS] = {
        {101, "C++ Basics", "Bjarne", false, 0},
        {102, "Data Structures", "Sahni", false, 0},
        {103, "Algorithms", "CLRS", false, 0},
        {104, "Operating Systems", "Tanenbaum", false, 0},
        {105, "Computer Networks", "Forouzan", false, 0},
        {106, "Databases", "Elmasri", false, 0},
        {107, "Artificial Intelligence", "Russell", false, 0},
        {108, "Software Engineering", "Pressman", false, 0},
        {109, "Discrete Math", "Rosen", false, 0},
        {110, "Python Intro", "Guido", false, 0}
    };

    int bookCount = 10;

    // ---------- SAMPLE MEMBER DATA ----------
    Member members[MAX_MEMBERS] = {
        {1, "Alice", 0},
        {2, "Bob", 0},
        {3, "Charlie", 0},
        {4, "Diana", 0},
        {5, "Ethan", 0},
        {6, "Fatima", 0},
        {7, "George", 0},
        {8, "Hana", 0},
        {9, "Isaac", 0},
        {10, "Julia", 0}
    };

    int memberCount = 10;

    // ---------- MENU LOOP ----------
    while (true) {
        cout << "\nLibrary Menu\n";
        cout << "1. Issue Book\n";
        cout << "2. Return Book\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Display All Books\n";
        cout << "5. Display All Members\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {

            case 1: { // Issue Book
                int bookId, memberId;
                cout << "Enter Book ID: ";
                cin >> bookId;

                Book* bookPtr = NULL;
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].id == bookId) {
                        bookPtr = &books[i];
                        break;
                    }
                }

                if (bookPtr == NULL) {
                    cout << "Book not found.\n";
                    break;
                }

                if (bookPtr->isIssued) {
                    cout << "Book already issued.\n";
                    break;
                }

                cout << "Enter Member ID: ";
                cin >> memberId;

                Member* memberPtr = NULL;
                for (int i = 0; i < memberCount; i++) {
                    if (members[i].id == memberId) {
                        memberPtr = &members[i];
                        break;
                    }
                }

                if (memberPtr == NULL) {
                    cout << "Member not found.\n";
                    break;
                }

                bookPtr->isIssued = true;
                bookPtr->issuedTo = memberPtr->id;
                memberPtr->booksIssued++;

                cout << "Book issued successfully.\n";
                break;
            }

            case 2: { // Return Book
                int bookId;
                cout << "Enter Book ID: ";
                cin >> bookId;

                Book* bookPtr = NULL;
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].id == bookId) {
                        bookPtr = &books[i];
                        break;
                    }
                }

                if (bookPtr == NULL) {
                    cout << "Book not found.\n";
                    break;
                }

                if (!bookPtr->isIssued) {
                    cout << "Book is not issued.\n";
                    break;
                }

                for (int i = 0; i < memberCount; i++) {
                    if (members[i].id == bookPtr->issuedTo) {
                        members[i].booksIssued--;
                        break;
                    }
                }

                bookPtr->isIssued = false;
                bookPtr->issuedTo = 0;

                cout << "Book returned successfully.\n";
                break;
            }

            case 3: { // Search Book
                int bookId;
                cout << "Enter Book ID: ";
                cin >> bookId;

                bool found = false;
                for (int i = 0; i < bookCount; i++) {
                    if (books[i].id == bookId) {
                        cout << "Title: " << books[i].title << endl;
                        cout << "Author: " << books[i].author << endl;
                        cout << "Status: "
                             << (books[i].isIssued ? "Issued" : "Available")
                             << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Book not found.\n";
                }
                break;
            }

            case 4: { // Display Books
                Book* ptr = books;
                for (int i = 0; i < bookCount; i++) {
                    cout << ptr->id << " | "
                         << ptr->title << " | "
                         << ptr->author << " | "
                         << (ptr->isIssued ? "Issued" : "Available")
                         << endl;
                    ptr++;
                }
                break;
            }

            case 5: { // Display Members
                for (int i = 0; i < memberCount; i++) {
                    cout << members[i].id << " | "
                         << members[i].name << " | "
                         << members[i].booksIssued << endl;
                }
                break;
            }

            case 0:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}

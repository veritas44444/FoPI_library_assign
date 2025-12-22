#include <iostream>
#include <string>
using namespace std;

// Define a Book struct to hold book data (ID, title, author, issue status)
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;  // true if book is currently issued
    int issuedTo;   // ID of member who has issued it (0 if none)
};

// Define a Member struct for member data (ID, name, books issued count)
struct Member {
    int id;
    string name;
    int booksIssued; // number of books currently issued to this member
};

int main() {
    const int MAX_BOOKS = 100;    // max books (as per requirement)
    const int MAX_MEMBERS = 100;  // max members

    // Arrays to store books and members
    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    int bookCount = 0;    // current number of books
    int memberCount = 0;  // current number of members

    // Initialize books and members entries
    for(int i = 0; i < MAX_BOOKS; i++) {
        books[i].isIssued = false;
        books[i].issuedTo = 0;
    }
    for(int j = 0; j < MAX_MEMBERS; j++) {
        members[j].booksIssued = 0;
    }

    // Main menu loop: repeats until user chooses to exit
    while (true) {  // using a while loop for menu repetition
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Display All Books\n";
        cout << "7. Display All Members\n";
        cout << "8. Search Member\n";
        cout << "0. Exit\n";
        cout << "Enter your choice (0-8): ";
        
        int choice;
        cin >> choice;

        switch (choice) {  // use switch for menu options
        
            case 1: {  // Add Book
                if (bookCount >= MAX_BOOKS) {
                    cout << "Cannot add more books (limit reached).\n";
                    break;
                }
                cout << "Enter new Book ID: ";
                int newId;
                cin >> newId;
                // Check for duplicate ID
                bool exists = false;
                for(int i = 0; i < bookCount; i++) {
                    if (books[i].id == newId) {
                        exists = true;
                        break;
                    }
                }
                if (exists) {
                    cout << "Book ID already exists! Cannot add.\n";
                } else {
                    cin.ignore();  // clear newline from input buffer
                    cout << "Enter Book Title: ";
                    string newTitle;
                    getline(cin, newTitle);
                    cout << "Enter Book Author: ";
                    string newAuthor;
                    getline(cin, newAuthor);
                    // Store the new book in the array
                    books[bookCount].id = newId;
                    books[bookCount].title = newTitle;
                    books[bookCount].author = newAuthor;
                    books[bookCount].isIssued = false;
                    books[bookCount].issuedTo = 0;
                    bookCount++;
                    cout << "Book added successfully.\n";
                }
                break;
            }
            
            case 2: {  // Add Member
                if (memberCount >= MAX_MEMBERS) {
                    cout << "Cannot add more members (limit reached).\n";
                    break;
                }
                cout << "Enter new Member ID: ";
                int newId;
                cin >> newId;
                // Check for duplicate member ID
                bool exists = false;
                for(int i = 0; i < memberCount; i++) {
                    if (members[i].id == newId) {
                        exists = true;
                        break;
                    }
                }
                if (exists) {
                    cout << "Member ID already exists! Cannot add.\n";
                } else {
                    cin.ignore();
                    cout << "Enter Member Name: ";
                    string newName;
                    getline(cin, newName);
                    // Store the new member in the array
                    members[memberCount].id = newId;
                    members[memberCount].name = newName;
                    members[memberCount].booksIssued = 0;
                    memberCount++;
                    cout << "Member added successfully.\n";
                }
                break;
            }
            
            case 3: {  // Issue Book
                cout << "Enter Book ID to issue: ";
                int bookId;
                cin >> bookId;
                // Find the book in the array
                Book *bookPtr = nullptr;
                for(int i = 0; i < bookCount; i++) {
                    if (books[i].id == bookId) {
                        bookPtr = &books[i];  // pointer to the book struct
                        break;
                    }
                }
                if (bookPtr == nullptr) {
                    cout << "Book ID not found.\n";
                    break;
                }
                if (bookPtr->isIssued) {
                    cout << "Book is already issued to member ID "
                         << bookPtr->issuedTo << ".\n";
                    break;
                }
                cout << "Enter Member ID to issue to: ";
                int memId;
                cin >> memId;
                // Find the member in the array
                Member *memPtr = nullptr;
                for(int j = 0; j < memberCount; j++) {
                    if (members[j].id == memId) {
                        memPtr = &members[j];
                        break;
                    }
                }
                if (memPtr == nullptr) {
                    cout << "Member ID not found.\n";
                    break;
                }
                // Mark the book as issued
                bookPtr->isIssued = true;
                bookPtr->issuedTo = memPtr->id;
                memPtr->booksIssued++;
                cout << "Book issued successfully to member " << memPtr->name << ".\n";
                break;
            }
            
            case 4: {  // Return Book
                cout << "Enter Book ID to return: ";
                int bookId;
                cin >> bookId;
                // Find the book
                Book *bookPtr = nullptr;
                for(int i = 0; i < bookCount; i++) {
                    if (books[i].id == bookId) {
                        bookPtr = &books[i];
                        break;
                    }
                }
                if (bookPtr == nullptr) {
                    cout << "Book ID not found.\n";
                    break;
                }
                if (!bookPtr->isIssued) {
                    cout << "This book is not issued to any member.\n";
                    break;
                }
                // Decrement the member's issued count
                int returnMemId = bookPtr->issuedTo;
                for(int j = 0; j < memberCount; j++) {
                    if (members[j].id == returnMemId) {
                        if (members[j].booksIssued > 0) {
                            members[j].booksIssued--;
                        }
                        break;
                    }
                }
                // Update book status
                bookPtr->isIssued = false;
                bookPtr->issuedTo = 0;
                cout << "Book returned successfully.\n";
                break;
            }
            
            case 5: {  // Search Book
                cout << "Search Book by (1) ID or (2) Title: ";
                int option;
                cin >> option;
                bool found = false;
                if (option == 1) {
                    cout << "Enter Book ID: ";
                    int searchId;
                    cin >> searchId;
                    // Linear search by ID
                    for(int i = 0; i < bookCount; i++) {
                        if (books[i].id == searchId) {
                            cout << "Book found: ID " << books[i].id 
                                 << ", Title \"" << books[i].title
                                 << "\", Author " << books[i].author
                                 << ". Status: " 
                                 << (books[i].isIssued ? "Issued" : "Available")
                                 << ".\n";
                            found = true;
                            break;
                        }
                    }
                } else if (option == 2) {
                    cin.ignore();
                    cout << "Enter Book Title: ";
                    string searchTitle;
                    getline(cin, searchTitle);
                    // Linear search by title
                    for(int i = 0; i < bookCount; i++) {
                        if (books[i].title == searchTitle) {
                            cout << "Book found: ID " << books[i].id
                                 << ", Title \"" << books[i].title
                                 << "\", Author " << books[i].author
                                 << ". Status: " 
                                 << (books[i].isIssued ? "Issued" : "Available")
                                 << ".\n";
                            found = true;
                            break;
                        }
                    }
                } else {
                    cout << "Invalid search option.\n";
                    break;
                }
                if (!found) {
                    cout << "Book not found.\n";
                }
                break;
            }
            
            case 6: {  // Display All Books
                if (bookCount == 0) {
                    cout << "No books in the system.\n";
                } else {
                    cout << "List of Books (ID, Title, Author, Status):\n";
                    // Iterate through the books array using a pointer
                    Book *bPtr = books;
                    for(int i = 0; i < bookCount; i++) {
                        cout << bPtr->id << "\t" 
                             << bPtr->title << "\t" 
                             << bPtr->author << "\t"
                             << (bPtr->isIssued ? "Issued" : "Available") 
                             << "\n";
                        bPtr++;  // move pointer to next Book
                    }
                }
                break;
            }
            
            case 7: {  // Display All Members
                if (memberCount == 0) {
                    cout << "No members in the system.\n";
                } else {
                    cout << "List of Members (ID, Name, Books Issued):\n";
                    for(int i = 0; i < memberCount; i++) {
                        cout << members[i].id << "\t" 
                             << members[i].name << "\t"
                             << members[i].booksIssued << "\n";
                    }
                }
                break;
            }
            
            case 8: {  // Search Member
                cout << "Search Member by (1) ID or (2) Name: ";
                int option;
                cin >> option;
                bool found = false;
                if (option == 1) {
                    cout << "Enter Member ID: ";
                    int searchId;
                    cin >> searchId;
                    for(int i = 0; i < memberCount; i++) {
                        if (members[i].id == searchId) {
                            cout << "Member found: ID " << members[i].id 
                                 << ", Name " << members[i].name
                                 << ", Books Issued: " << members[i].booksIssued 
                                 << ".\n";
                            found = true;
                            break;
                        }
                    }
                } else if (option == 2) {
                    cin.ignore();
                    cout << "Enter Member Name: ";
                    string searchName;
                    getline(cin, searchName);
                    for(int i = 0; i < memberCount; i++) {
                        if (members[i].name == searchName) {
                            cout << "Member found: ID " << members[i].id 
                                 << ", Name " << members[i].name
                                 << ", Books Issued: " << members[i].booksIssued 
                                 << ".\n";
                            found = true;
                            break;
                        }
                    }
                } else {
                    cout << "Invalid search option.\n";
                    break;
                }
                if (!found) {
                    cout << "Member not found.\n";
                }
                break;
            }
            
            case 0:  // Exit
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            
            default:
                cout << "Invalid choice. Please enter a number between 0 and 8.\n";
        }
    }

    return 0;
}


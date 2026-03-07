#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

struct Book {
    string isbn;
    string title;
    string author;
    int totalCopies;
    int availableCopies;
};

struct Member {
    string id;
    string name;
};

struct Loan {
    string isbn;
    string memberId;
    int checkoutDay;
    int dueDay;
};

struct LibraryState {
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;
    int currentDay;
};

inline void addBook(LibraryState& state, const Book& b) {
    state.books.push_back(b);
}

inline void addMember(LibraryState& state, const Member& m) {
    state.members.push_back(m);
}

inline Book* findBook(LibraryState& state, string isbn) {
    for (int i = 0; i < state.books.size(); i++) {
        if (state.books[i].isbn == isbn) return &state.books[i];
    }
    return nullptr;
}

inline Member* findMember(LibraryState& state, string id) {
    for (int i = 0; i < state.members.size(); i++) {
        if (state.members[i].id == id) return &state.members[i];
    }
    return nullptr;
}

inline void checkoutBook(LibraryState& state, string isbn, string memberId) {
    Book* b = findBook(state, isbn);
    Member* m = findMember(state, memberId);
    if (!b) throw runtime_error("Error: Book not found!");
    if (!m) throw runtime_error("Error: Member not found!");
    if (b->availableCopies <= 0) throw runtime_error("Error: No copies available!");

    b->availableCopies--;
    state.loans.push_back({isbn, memberId, state.currentDay, state.currentDay + 14});
}

inline void returnBook(LibraryState& state, string isbn, string memberId) {
    Book* b = findBook(state, isbn);
    if (b) b->availableCopies++;
    for (int i = 0; i < state.loans.size(); i++) {
        if (state.loans[i].isbn == isbn && state.loans[i].memberId == memberId) {
            state.loans.erase(state.loans.begin() + i);
            break;
        }
    }
}
#endif

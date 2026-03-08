#include "reports.h"
#include "library.h"
#include "storage.h"
#include "utils.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;
int main() {
    
     LibraryState state;
    string dbPath = "library_data.txt"; 
    loadDatabase(state, "library_data.txt");
    saveDatabase(state, "library_data.txt");

    int choice;
    while (true) {
         try{
            cout <<BLUE<< "\n  ====== Library Management System ======" <<RESET<< endl;
            cout <<BLUE<< "Current Day: " << state.currentDay <<RESET<< endl;
            cout << "1.  Add New Book" << endl;  //
            cout << "2.  Add New Member" << endl;
            cout << "3.  Checkout Book (Borrow)" << endl; //
            cout << "4.  Return Book" << endl;
            cout << "5.  Search for a Book" << endl;
            cout << "6.  Generate Overdue Report" << endl;
            cout << "7.  Export Overdue List (.txt)" << endl;
            cout << "8.  Advance to Next Day" << endl; //
            cout << "9.  Save and Exit" << endl; //
            cout << "Enter choice: ";
            

            if (!(cin >> choice)) {
                throw runtime_error("Invalid input! Please enter a number.");
            }
            
            switch (choice) {
                 case 1:{ 
                    Book b;
                    cout << "\n--- Add New Book ---" << endl;
                    cout << "Enter ISBN: "; cin >> b.isbn;
                    cout << "Enter Title: "; 
                    cin.ignore();
                    getline(cin, b.title);
                    cout << "Enter Author: "; 
                    getline(cin, b.author);
                    cout << "Enter Total Copies: "; cin >> b.totalCopies;
                    
                    b.availableCopies = b.totalCopies; 
                    
                    addBook(state, b); 
                    logActivity("Member B added book: " + b.title); 
                    cout << GREEN << "Book added successfully!" << RESET << endl;
                    break;
                }

                 case 2:{
                   Member m;
                   cout << "Enter Member ID: "; cin >> m.id;
                   cout << "Enter Member Name: "; cin.ignore(); getline(cin, m.name);
                   addMember(state, m);
                   logActivity("Added Member: " + m.name);
                   cout << GREEN << "Success: Member registered!" << RESET << endl;
                   break;

                 }
                 
                 case 3:{ 
                    string isbn, memberId;
                    cout << "\n--- Checkout Book ---" << endl;
                    cout << "Enter Book ISBN: "; cin >> isbn;
                    cout << "Enter Member ID: "; cin >> memberId;

                    checkoutBook(state, isbn, memberId); 
                    
                    logActivity("Book " + isbn + " checked out by " + memberId); 
                    cout << GREEN << "Checkout completed successfully!" << RESET << endl;
                    break;
                }
                 

                case 4: { // Return Book
                    string isbn, mid;
                    cout << "Enter Book ISBN: "; cin >> isbn;
                    cout << "Enter Member ID: "; cin >> mid;
                    returnBook(state, isbn, mid);
                    logActivity("Member " + mid + " returned " + isbn);
                    cout << GREEN << "Success: Book returned to shelf!" << RESET << endl;
                    break;
                }
                case 5: { // Search Book
                    string isbn;
                    cout << "Enter ISBN to search: "; cin >> isbn;
                    Book* b = findBook(state, isbn);
                    if (b) {
                        cout << "\nFound: \"" << b->title << "\" by " << b->author << endl;
                        cout << "Status: " << b->availableCopies << " / " << b->totalCopies << " available." << endl;
                    } else {
                        cout << RED << "Book not found." << RESET << endl;
                    }
                    break;
                }
                 case 6:
                     generateOverdueReport(state);
                    break;
                 case 7:
                      exportOverdueBooks(state, "overdue_report.txt");
                      break;
                 case 8:
                      state.currentDay++;
                     cout << GREEN << "Advanced to next day: " << state.currentDay << RESET << endl;
                     break;
                      case 9:
                      saveDatabase(state, dbPath);                
                      cout << GREEN << "Data saved successfully. Exiting..." << RESET << endl;
                     return 0;
                 default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }
}
            
        catch (const exception& e) {
            cout << RED << " Error!! " << e.what() << RESET << endl;
            cin.clear(); 
            cin.ignore(1000, '\n'); 
        }
    }

    return 0;
}

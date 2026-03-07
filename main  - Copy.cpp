#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"
using namespace std;

struct Book {
    int id;
    string title;
    bool isBorrowed;
    int borrowDay;
};

// save data to file
void saveToFile(vector<Book> books) {
    ofstream myFile("library_data.txt");
    if ( myFile.is_open() ) {
        for (int i = 0; i < books.size(); i++) {
            myFile << books[i].id << " "  << books[i].title << " "  
            << books[i].isBorrowed << " " << books[i].borrowDay << endl;
                  
        }
        myFile.close();
        cout << "Data saved successfully to library_data.txt" << endl;
    } 
    else {
        cout << "Error !! Could not open file for saving!" << endl;
    }
}

// load data from file
void loadFromFile(vector<Book> &books) {
    ifstream readFile("library_data.txt");
    if (readFile.is_open()) {
        Book temp;
        while (readFile >> temp.id >> temp.title >> temp.isBorrowed >> temp.borrowDay) {
            books.push_back(temp);
        }
        readFile.close();
        cout << "Data loaded successfully." << endl;
    }
    else {
        cout << "No existing data found. Starting with an empty library." << endl;
    }
} 


// overdue fine calculation
void checkFine(int bDay, int rDay) {

    int daysUsed = rDay - bDay;
    if (daysUsed > 14) {
        int fine = (daysUsed - 14) * 5;
        cout << "Oh noo!You are Late! Fine is: " << fine << " pound." << endl;
    } else {
        cout << " Returned on time. No fine." << endl;
    }
}

int main() {
    vector<Book> books;
    loadFromFile(books); 

    int choice;
    while (true) {
        // the clu
        cout << BLUE << "\n    Library System     " << RESET << endl;
        cout << BLUE << "1. Add Book (Member A task)\n" << RESET;
        cout << BLUE << "2. Borrow Book (Member A task)\n" << RESET;
        cout << BLUE << "3. Return & Check Fine \n" << RESET;
        cout << BLUE << "4. Exit & Save\n" << RESET;
        cout << "Enter Choice: ";

        // try-catch
        try {
            if (!(cin >> choice)) { 
                
                // if input is not a number 
                throw "invalid input! please enter a number.";
            }

            if (choice == 1) {
                cout << "[working on Member A's code here...]" << endl;
            } 
            else if (choice == 3) {
                // overdue fine calculation
                int bDay; cout << "Enter borrow day: "; cin >> bDay;
                int rDay; cout << "Enter return day: "; cin >> rDay;
                checkFine(bDay, rDay);
            }
            else if (choice == 4) {
                saveToFile(books);
                break;
            }
        }
        catch (const char* msg) {
            cout << RED << "Error!! " << msg << RESET << endl;
            cin.clear(); 
            cin.ignore(100, '\n'); 
        }
    }
    return 0;
}


/*
int main() {
    LibraryState state;
    string dbPath = "library_data.txt";

    // 1. أول حاجة بنعملها بنحمل البيانات القديمة
    loadDatabase(state, dbPath);

    int choice;
    bool running = true;

    while (running) {
        try {
            cout << "\n--- Library Management System ---" << endl;
            cout << "Current Day: " << state.currentDay << endl;
            cout << "1. Add Book (Member A)" << endl;
            cout << "2. Checkout Book (Member A)" << endl;
            cout << "3. Generate Overdue Report (Member B)" << endl;
            cout << "4. Export Overdue List (Member B)" << endl;
            cout << "5. Advance to Next Day" << endl;
            cout << "6. Save and Exit" << endl;
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                throw runtime_error("Invalid input! Please enter a number.");
            }

            switch (choice) {
                case 1:
                    cout << "[Waiting for Member A's addBook function...]" << endl;
                    break;
                case 2:
                    cout << "[Waiting for Member A's checkoutBook function...]" << endl;
                    break;
                case 3:
                    // شغلك إنتي
                    generateOverdueReport(state);
                    break;
                case 4:
                    // شغلك إنتي
                    exportOverdueBooks(state, "overdue_report.txt");
                    break;
                case 5:
                    state.currentDay++; // بنزود اليوم عشان نجرب الغرامات
                    cout << "System day advanced to: " << state.currentDay << endl;
                    break;
                case 6:
                    // شغلك إنتي
                    saveDatabase(state, dbPath);
                    running = false;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        } 
        catch (const exception& e) {
            cout << "⚠️ Error: " << e.what() << endl;
            cin.clear(); // بيمسح الخطأ من الـ input
            cin.ignore(1000, '\n'); // بيتجاهل الكلام الغلط اللي اليوزر دخله
        }
    }

    return 0;
}

*/

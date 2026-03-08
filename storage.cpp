#include "storage.h"
#include "utils.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

void saveDatabase(const LibraryState& state, const string& dbPath){

    ofstream myFile(dbPath);
    if ( myFile.is_open() ) {
        for (int i = 0; i < state.books.size(); i++) {
            myFile << state.books[i].isbn << "|"  
                   << state.books[i].title << "|"
                   << state.books[i].author << "|"
                   << state.books[i].totalCopies << "|"  
                   << state.books[i].availableCopies << endl;
                  
        }
        myFile.close();
        cout << GREEN << "Data saved successfully to " << dbPath << RESET << endl;
    } 
    else {
        cout << RED << "Error !! Could not open file for saving!" << RESET << endl;
    }
}



// load data from file
void loadDatabase(LibraryState& state, const string& dbPath){
     ifstream readFile(dbPath);
    if (readFile.is_open()) {
        Book temp;
        string line;
        while (getline(readFile, line)) {
            vector<string> p=split(line,'|');
            if(p.size()==5){
                temp.isbn=p[0];
                temp.title=p[1];
                temp.author=p[2];
                temp.totalCopies=stoi(p[3]);
                temp.availableCopies=stoi(p[4]);
                state.books.push_back(temp);
            }
        }
        readFile.close();
        cout << GREEN << "Data loaded successfully." << RESET << endl;
    }
    else {
        cout << RED << "No existing data found." << RESET << endl;
    }

}
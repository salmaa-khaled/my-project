#include "reports.h"
#include "utils.h"

void generateOverdueReport(const LibraryState& state) {
    bool found = false;
    cout << "\n--- Overdue Report ---" << endl;
    for (const auto& record : state.loans) {
        if (state.currentDay > record.dueDay) {
            found = true;
            int days = state.currentDay - record.dueDay;
            cout << "ISBN: " << record.isbn << " | Member: " << record.memberId 
                 << " | Overdue: " << days << " days. Fine: " << days * 5 << endl;
        }
    }
    if (!found) cout << "No overdue books found." << endl;
}

void exportOverdueBooks(const LibraryState& state, const string& filename) {
    ofstream myFile(filename);
    if (myFile.is_open()) {
        myFile << "MemberID|ISBN|DaysOverdue|Fine\n";
        for (const auto& record : state.loans) {
            if (state.currentDay > record.dueDay) {
                int days = state.currentDay - record.dueDay;
                myFile << record.memberId << "|" << record.isbn << "|" << days << "|" << days * 5 << "\n";
            }
        }
        myFile.close();
        cout << GREEN << "Report exported!" << RESET << endl;
    }
}

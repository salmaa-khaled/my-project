#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

inline vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

inline void logActivity(const string& message) {
    ofstream logFile("system_audit.log", ios::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        char dt[26];

        // ctime_s دي النسخة اللي Visual Studio بيحبها عشان الأمان
        ctime_s(dt, sizeof(dt), &now);

        string timeStr(dt);
        if(!timeStr.empty()) timeStr.pop_back(); // بنشيل السطر الزيادة اللي بيجي مع الوقت


        ctime_s(dt, sizeof(dt), &now);
        if (!timeStr.empty()) timeStr.pop_back();

        logFile << "[" << timeStr << "] " << message << endl;
        logFile.close();
    }
}

#endif

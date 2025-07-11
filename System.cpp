#include "System.h"
#include "User.h"
#include "UserManager.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>           
#include <conio.h> 

using namespace std;

System::System() {
    current_LoggedIN_user = nullptr;
}

bool System::registerUser(const string& uname, const string& pass) {
    try {
        User& user = UserManager::searchUser(uname);
        cout << "Username already exists. Try another.\n";
        return false;
    }
    catch (const exception& e) {
        User newUser(uname, pass);
        UserManager::addUser(uname, newUser);
        cout << "Registration successful!" << "\n";
        return true;
    }
}

bool System::login(const string& username, const string& password) {
    try {
        User& user = UserManager::searchUser(username);
        if (user.getpassword() == password) {
            setCurrent_LoggedIN_user(user);  // Set the current logged-in user
            cout << "Login successful. Welcome, " << username << "!" << endl;
            return true;
        }
        else {
            cout << "Incorrect password." << endl;
            return false;
        }
    }
    catch (const exception& e) {
        cout << "User does not exist. Try again." << endl;
        return false;
    }
}

User& System::getCurrent_LoggedIN_user() {
    if (current_LoggedIN_user == nullptr) {
        throw runtime_error("No user is currently logged in.");
    }
    return *current_LoggedIN_user;
}

void System::setCurrent_LoggedIN_user(User& user) {
    current_LoggedIN_user = &user;
}

void System::changeUserPassword(const string& userUsername, const string& newPassword) {
    try {
        User& user = UserManager::searchUser(userUsername);
        user.setPassword(newPassword);
        cout << "Password updated successfully for user: " << user.getUsername() << "\n";
    }
    catch (const exception& e) {
        cout << "User not found. Cannot change password.\n";
    }
}



string System::HidePassword() {

    string password;
    char ch;

    while ((ch = _getch()) != '\r') { // return if (Enter key) pressed
        if (ch == '\b') { // Backspace
            if (!password.empty()) {
                password.pop_back();             // Remove last character
                cout << "\b \b";            // Erase * from screen
            }
        }
        else {
            password += ch;                      // Add typed character to password
           cout << '*';                    // Show * instead of actual char
        }
    }

    cout <<endl;
    return password;
}

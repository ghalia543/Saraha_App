#include "System.h"
#include "User.h"
#include "UserManager.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>               

using namespace std;

System::System() {}

bool System::registerUser(const string& uname, const string& pass)
{
    
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

bool System::login(const string& username, const string& password)
{
    try {
        User& user = UserManager::searchUser(username);
        if (user.getpassword() == password) {      
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

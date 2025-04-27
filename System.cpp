#include "System.h"
#include "User.h"
#include "UserManager.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>               

using namespace std;

System::System(UserManager& um) : userManager(um) {
}

bool System::registerUser(const string& uname, const string& pass)
{
    
    try {
        User& user = userManager.searchUser(uname);
        //cout << "Username already exists. Try another.\n";
        return false;
    }
    catch (const exception& e) {
        
        /*
        cout << "Enter Mobile Number (11 digits): ";
        getline(cin, mobile);
        if (!isValidMobile(mobile)) {
            cout << "Invalid mobile number. It must be 11 digits.\n";
            return;
        }
        if (userManager.searchMobileNumber(mobile)) {
            cout << "Mobile number already used.\n";
            return;
        }
        */
        User newUser(uname, pass);
        userManager.addUser(uname, newUser);
        return true;
       // cout << "Registration successful!" << "\n";
    }
}

bool System::login(const string& username, const string& password)
{
    try {
        User& user = userManager.searchUser(username);
        if (user.getpassword() == password) {      // Check if password is correct
            //cout << "Login successful. Welcome, " << username << "!" << endl;
            return true;
        }
        else {
            //cout << "Incorrect password." << endl;
            return false;
        }
    }
    catch (const exception& e) {
        //cout << "User does not exist." << endl;
        return false;
    }
}

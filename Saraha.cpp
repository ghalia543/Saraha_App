#include "LoginSystem.h"
#include "UserManager.h"
#include "Registeration.h"
#include "System.h"

#include <iostream>

using namespace std;

int main() {
    UserManager userManager;
    System system(userManager);
    if (userManager.loadUsersFromFile()) {
        cout << "Press 1 for login and 2 for registeration: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            

            string username, password;
            cin.ignore();
            cout << "=== Login System ===" << endl;
            cout << "Enter username: ";
            getline(cin, username);
            

            cout << "Enter password: ";
            getline(cin, password);


            system.login(username, password);
        }
        else {
            cout << "=== Registeration System ===" << endl;
            string username, password;
            cin.ignore();
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            system.registerUser(username, password);
        }
    }
    else {
        cout << "Failed to load users from file!" << endl;
        return 1;
    }

    if (!userManager.saveUsersToFile()) {
        cout << "Failed to load users into file!" << endl;
        return 1;
    }

    return 0;
}
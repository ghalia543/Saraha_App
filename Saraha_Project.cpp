#include "UserManager.h"
#include "MessageManager.h"
#include "System.h"

#include <iostream>

using namespace std;

int main() {
    MessageManager messageManager;
    UserManager userManager;

    if (!messageManager.loadMessagesFromFile()) {
        cout << "Failed to load messages from file.\n";
        return 1;
    }
    /*CHECK MESSAGE CORRECTLY LOADED
    else {
        unordered_map <string, Message> return_msg = messageManager.return_msg();
        unordered_map <string, Message>::iterator it;
        for (it = return_msg.begin(); it != return_msg.end(); it++) {
            cout << it->second.getMessageId() << " " << it->second.getReceiverId() << " " << it->second.getSenderId() << " " << it->second.getContent() << " " << it->second.getIsFavorite() << " " << it->second.getSentTime() << "\n";
        }
        cout << "Messages finished";
    }*/
    if (userManager.loadUsersFromFile()) {
        /*CHECK USERS CORRECTLY LOADED
        unordered_map <string, User> return_user = userManager.return_user();
        for (auto it = return_user.begin(); it != return_user.end(); it++) {
            cout << it->second.getId() << " " << it->second.getUsername() << " " << it->second.getpassword() << " " << it->second.getContactList().size() << " ";
            const auto& contactList = it->second.getContactList();  // reference, not copy
            if (!contactList.empty()) {
                for (auto itt = contactList.begin(); itt != contactList.end(); ++itt) {
                    cout << itt->first << " " << itt->second << " ";
                }
            }
            cout << it->second.getReceivedMessages().size() << " " << it->second.getSentMessages().size() << " " << it->second.getFavoriteMessages().size() << "\n";
        }*/
        System system;
        cout << "=========================Saraha=========================\n\n";
        cout << "Press 1 for login and 2 for registeration: ";
        int choice;
        cin >> choice;
        bool isValid;
        string username, password;
        if (choice == 1) {
            cin.ignore();
            cout << "\n                  ===Login System===" << endl;
            do {
                cout << "Enter username: ";
                getline(cin, username);

                cout << "Enter password: ";
                getline(cin, password);

                isValid = system.login(username, password);
            } while (!isValid);
        }
        else {
            cin.ignore();
            cout << "\n                ===Registeration System===" << endl;
            do {
                cout << "Enter username: ";
                getline(cin, username);

                cout << "Enter password: ";
                getline(cin, password);

                isValid = system.registerUser(username, password);
            } while (!isValid);
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
    if (!messageManager.saveMessagesToFile()) {
        cout << "Failed to load messages into file!" << endl;
        return 1;
    }

    return 0;
}

#include "UserManager.h"
#include "MessageManager.h"
#include "System.h"

#include <iostream>

using namespace std;

void startUserMenu(UserManager& userManager, System& system) {
    User& loggedInUser = system.getCurrent_LoggedIN_user();
    bool logedIn = true;

    while (logedIn) {
        cout << "\n===================================================\n";
        cout << "Press 1 to show contacts\n";
        cout << "Press 2 to show sent messages\n";
        cout << "Press 3 to send a message\n";
        cout << "Press 4 to show received messages\n";
        cout << "Press 5 to show received messages from a specific contact\n";
        cout << "Press 6 to add a user to your contacts\n";
        cout << "Press 7 to show favorite messages\n";
        cout << "Press 8 to change password\n";
        cout << "Press 9 to search messages by keyword\n";
        cout << "Press 10 to view stats\n";
        cout << "Press 11 to log out\n\n";

        int c;
        cin >> c;

        switch (c) {
        case 1: {
            loggedInUser.showContacts();
            if (loggedInUser.getContactList().empty()) {
                cout << "Empty!\n";
                break;
            }

            cout << "Do you want to remove a contact?(Y/N)\n";
            char answer;
            cin >> answer;
            if (answer == 'Y' || answer == 'y') {
                string id;
                cout << "Enter user id: ";
                cin >> id;
                loggedInUser.removeContact(id);
            }
            break;
        }

        case 2: {
            if (loggedInUser.getSentMessages().empty()) {
                cout << "Empty!\n";
                break;
            }

            loggedInUser.viewSentMessages();

            cout << "Do you want to undo last sent message?(Y/N)\n";
            char answer1;
            cin >> answer1;
            if (answer1 == 'Y' || answer1 == 'y') {
                loggedInUser.undoLastMessage();
            }
            break;
        }

        case 3: {
            string receiverName, content;
            cout << "Enter the receiver username: ";
            cin.ignore();
            getline(cin, receiverName);
            cout << "Enter the message content: ";
            getline(cin, content);

            try {
                loggedInUser.sendMessage(content, UserManager::searchUser(receiverName));
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }

        case 4: {
            if (loggedInUser.getReceivedMessages().empty()) {
                cout << "Empty!\n";
                break;
            }

            loggedInUser.view_all_recievedMessages();
            cout << "Do you want to add a message to favorites (Y/N): ";
            char choice2;
            cin >> choice2;
            if (choice2 == 'Y' || choice2 == 'y') {
                int num;
                cout << "Enter the number of message (starting from 1): ";
                cin >> num;

                if (num <= 0 || num > loggedInUser.getReceivedMessages().size()) {
                    cout << "Invalid message number.\n";
                }
                else {
                    loggedInUser.putFavorite(num);
                }
            }
            break;
        }

        case 5: {
            string uid;
            cout << "Enter the contact id: ";
            cin >> uid;
            loggedInUser.view_messages_from_contact(uid);
            break;
        }

        case 6: {
            string uid;
            cout << "Enter user id: ";
            cin >> uid;
            loggedInUser.addContact(uid);
            break;
        }

        case 7: {
            if (loggedInUser.getFavoriteMessages().empty()) {
                cout << "Empty!\n";
                break;
            }
            loggedInUser.viewFavorites();
            cout << "Do you want to remove oldest favorite message?(Y/N)\n";
            char answer1;
            cin >> answer1;
            if (answer1 == 'Y' || answer1 == 'y') {
                loggedInUser.RemoveFavoriteMessage();
            }
            break;
        }

        case 8: {
            string oldPass, newPass;
            cout << "Enter current password: ";
            cin.ignore();
            getline(cin, oldPass);

            if (oldPass != loggedInUser.getpassword()) {
                cout << "Incorrect password!\n";
                break;
            }

            cout << "Enter new password: ";
            getline(cin, newPass);

            if (newPass.empty()) {
                cout << "Password cannot be empty!\n";
            }
            else {
                system.changeUserPassword(loggedInUser.getUsername(), newPass);
                cout << "Password changed successfully!\n";
            }
            break;
        }

        case 9: {
            string keyword;
            cout << "Enter keyword to search in received messages: ";
            cin.ignore();
            getline(cin, keyword);

            bool found = false;
            auto& msgs = loggedInUser.getReceivedMessages();
            for (size_t i = 0; i < msgs.size(); ++i) {
                if (msgs[i].getContent().find(keyword) != string::npos) {
                    cout << "Message [" << i + 1 << "] from " << msgs[i].getSenderId() << ": "
                        << msgs[i].getContent() << endl;
                    found = true;
                }
            }

            if (!found) {
                cout << "No messages found containing \"" << keyword << "\".\n";
            }
            break;
        }

        case 10: {
            cout << "=========== Stats ===========" << endl;
            cout << "Total Contacts: " << loggedInUser.getContactList().size() << endl;
            cout << "Total Sent Messages: " << loggedInUser.getSentMessages().size() << endl;
            cout << "Total Received Messages: " << loggedInUser.getReceivedMessages().size() << endl;
            cout << "Total Favorite Messages: " << loggedInUser.getFavoriteMessages().size() << endl;

            if (!loggedInUser.getContactList().empty()) {
                vector<string> sortedContacts = loggedInUser.getSortedContacts();
                cout << "Most Frequent Contact: " << sortedContacts[0] << endl;
            }
            cout << "=============================\n";
            break;
        }

        case 11: {
            cout << "Are you sure you want to logout? (Y/N): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                logedIn = false;
            }
            break;
        }

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

int main() {
    MessageManager messageManager;
    UserManager userManager;

    if (!messageManager.loadMessagesFromFile()) {
        cout << "Failed to load messages from file.\n";
        return 1;
    }

    if (!userManager.loadUsersFromFile()) {
        cout << "Failed to load users from file!\n";
        return 1;
    }

    System system;
    cout << "========================= Saraha =========================\n\n";
    cout << "Press 1 for login and 2 for registration: ";
    int choice;
    cin >> choice;

    bool isValid;
    string username, password;

    if (choice == 1) {
        cin.ignore();
        cout << "\n                  === Login System ===\n";
        do {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            isValid = system.login(username, password);
        } while (!isValid);

        system.setCurrent_LoggedIN_user(UserManager::searchUser(username));
        startUserMenu(userManager, system);
    }
    else if (choice == 2) {
        cin.ignore();
        cout << "\n                === Registration System ===\n";
        do {
            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            isValid = system.registerUser(username, password);
        } while (!isValid);

        cout << "\nRegistration successful. Please login.\n";

        do {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            isValid = system.login(username, password);
        } while (!isValid);

        system.setCurrent_LoggedIN_user(UserManager::searchUser(username));
        startUserMenu(userManager, system);
    }
    else {
        cout << "Invalid choice!\n";
        return 1;
    }

    // Save Data before Exit
    if (!userManager.saveUsersToFile()) {
        cout << "Failed to save users to file!\n";
        return 1;
    }

    if (!messageManager.saveMessagesToFile()) {
        cout << "Failed to save messages to file!\n";
        return 1;
    }

    return 0;
}

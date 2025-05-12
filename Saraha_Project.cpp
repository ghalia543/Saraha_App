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

    if (userManager.loadUsersFromFile()) {

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
            system.setCurrent_LoggedIN_user(userManager.searchUser(username));
            User& loggedInUser = system.getCurrent_LoggedIN_user();
            map<string, int> contacts = loggedInUser.getContactList();
            bool logedIn = true;
            while (logedIn) {
                cout << "===================================================\n";
                cout << "Press 1 to show contacts\n";//show option remove contact inside it
                cout << "Press 2 to show sent messages\n";//show option undo last message inside
                cout << "Press 3 to send a message\n";
                cout << "Press 4 to show recieved messages\n";//show add to favorite messages
                cout << "Press 5 to show recieved messages from a specific contact\n";
                cout << "Press 6 to add a user to your contacts\n";
                cout << "Press 7 to show favorite messages\n";//show remove oldest message
                cout << "Press 8 to log out\n";
                int c;
                cin >> c;
                switch (c)
                {
                case 1:
                    loggedInUser.showContacts();
                    cout << "Do you want to remove a contact?(Y/N)\n";
                    char answer;
                    cin >> answer;
                    if (answer == 'Y' || answer == 'y') {
                        string id;
                        cout << "Enter the user id:";
                        cin >> id;
                        loggedInUser.removeContact(id);
                    }
                    break;
                case 2:
                    loggedInUser.viewSentMessages();
                    
                    cout << "Do you want to undo last sent message?(Y/N)\n";
                    char answer1;
                    cin >> answer1;
                    if (answer1 == 'Y' || answer1 == 'y') {
                        loggedInUser.undoLastMessage();
                    }
                    
                    break;
                case 3:
                {
                    string recievername, content;
                    cout << "Enter the receiver name: ";
                    cin.ignore(); 
                    getline(cin, recievername);

                    cout << "Enter the message content: ";
                    
                    getline(cin, content); 

                    try {
                        loggedInUser.sendMessage(content, userManager.searchUser(recievername));
                    }
                    catch (const exception& e) {
                        cerr << "Error: " << e.what() << endl;
                    }
                    break;
                }
                case 4:
                    loggedInUser.view_all_recievedMessages();
                    cout << "Do you want to add a message to favorites(Y/N)";
                    char choice2;
                    cin >> choice2;
                    if (choice2 == 'Y' || choice2 == 'y') {
                        int num;
                        cout << "Enter the number of message :";
                        cin >> num;
                        loggedInUser.putFavorite(num - 1);
                    }
                    break;
                case 5: {
                    string uid;
                    cout << "Enter the contact ID: ";
                    cin >> uid;
                    loggedInUser.view_messages_from_contact(uid);
                    break;
                }
                case 6: {
                    string uid;
                    cout << "Enter the user id:";
                    cin >> uid;
                    loggedInUser.addContact(uid);
                    break;
                }
                case 7:
                    loggedInUser.viewFavorites();
                    break;
                case 8:
                    logedIn = false;
                    break;
                default:
                    break;
                }
            }
            //loggedInUser.sendMessage("fromghalia", userManager.searchUser("Farah Mohamed"));

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

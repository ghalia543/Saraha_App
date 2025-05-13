#include "User.h"
#include "UserManager.h"
#include <iostream>
#include <unordered_map>
using namespace std;

int User::autoId = 1;

//Constructors
User::User() {}

User::User(string uname, string pwd)
    : id("U" + to_string(autoId++)), username(uname), password(pwd) {
}

User::User(string id, string uname, string pwd)
    : id(id), username(uname), password(pwd) {
}

//setters
void User::setautoId(int nextId) {
    autoId = nextId;
}

void User::setPassword(const string& newPassword) {
    password = newPassword;
}

void User::setContact(string& contactUsername, string& contactMsgCount) {
    contactList.setContact(contactUsername, contactMsgCount);
}

void User::setReceivedMessage(string msgId) {
    receivedMessages.push_back(MessageManager::getMessage(msgId));
}

void User::setSentMessage(string& msgId) {
    sentMessages.push_back(MessageManager::getMessage(msgId));
}

void User::setFavoriteMessage(string msgId) {
    favoriteMessages.push(MessageManager::getMessage(msgId));
}

//getters
string User::getId() { return id; }

string User::getUsername() { return username; }

string User::getpassword() { return password; }

map<string, int> User::getContactList() { return contactList.getContactList(); }

vector<string> User::getSortedContacts() { return contactList.getSortedContacts(); }

vector<Message>& User::getReceivedMessages() { return receivedMessages; }

deque<Message> User::getSentMessages() { return sentMessages; }

queue<Message> User::getFavoriteMessages() { return favoriteMessages; }

//Send a message
void User::sendMessage(string msgContent, User& receiver) {
    Message msg(id, receiver.getUsername(), msgContent);
    msg.setTime();
    MessageManager::addMessage(msg.getMessageId(), msg);
    sentMessages.push_back(msg);
    receiver.receiveMessage(msg);
    cout << "Message sent.\n";
}

//Receiving a new message
void User::receiveMessage(Message msg) {
    receivedMessages.push_back(msg);
    map<string, int> contacts = contactList.getContactList();
    if (contacts.find(msg.getSenderId()) != contacts.end()) {
        contactList.updateContactOnMessage(msg.getSenderId());
    }
}

//Display all sent messages
void User::viewSentMessages() {
    deque<Message> temp = sentMessages;
    cout << "\nSent messages:" << endl;
    cout << "__________________\n";
    while (!temp.empty()) {
        Message msg = temp.back(); temp.pop_back();
        cout << "To User " << msg.getReceiverUsername() << ": " << msg.getContent() << "\n";
    }
}

//Delete last sent message
void User::undoLastMessage() {
    if (sentMessages.empty()) {
        cout << "No message to undo.\n";
        return;
    }
    Message tempMsg = sentMessages.back();
    sentMessages.pop_back();
    try {
        User& receiver = UserManager::searchUser(tempMsg.getReceiverUsername());
        vector<Message>& receiverMessages = receiver.getReceivedMessages();

        bool found = false;
        for (auto it = receiverMessages.begin(); it != receiverMessages.end(); ++it) {
            if (it->getMessageId() == tempMsg.getMessageId()) {
                receiverMessages.erase(it);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Warning: Message not found in receiver's messages.\n";
        }

        MessageManager::deleteMessage(tempMsg.getMessageId());
        if (receiver.contactList.searchContact(id)) {
            receiver.contactList.minusNumberOfMessages(id);
        }

        cout << "Last message undone.\n";

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

//view all recieved messages
void User::view_all_recievedMessages() {
    int msgNum = 1;
    if (!receivedMessages.empty()) {
        for (auto it = receivedMessages.end() - 1;; it--) {
            cout << "\nRecieved messages:" << endl;
            cout << "__________________\n";
            cout << msgNum++ << ". ";
            it->displayMessage();
            if (it == receivedMessages.begin())
                break;
        }
    }
}

//view all recieved messages from specific contact
void User::view_messages_from_contact(string senderId_contact)a           {
    if (!contactList.searchContact(senderId_contact)) {
        cout << "This is not a contact\n";
        return;
    }

    bool found = false;
    int msgNum = 1;

    for (Message& msg : receivedMessages) {
        if (msg.getSenderId() == senderId_contact) {
            cout << "\nRecieved messages:" << endl;
            cout << "__________________\n";
            cout << msgNum++ << ". ";
            msg.displayMessage();
            found = true;
        }
    }
    if (!found) {
        cout << "Empty!" << endl;
    }
}

//contact management
void User::addContact(string contactUsername) {
    contactList.addContact(contactUsername, receivedMessages);
}

void User::removeContact(string contactUsername) {
    try {
        contactList.removeContact(contactUsername);
    }
    catch (const exception& e) {
        return;
    }
}

void User::showContacts() {
    cout << contactList.displayContacts();
}

//Add message to favorites (Fixed)
void User::putFavorite(int msgPos) {
    int reverseIndex = receivedMessages.size()  - msgPos;

    Message& fav = receivedMessages.at(reverseIndex);

    if (!fav.getIsFavorite()) {
        fav.setIsFavorite(true);
        favoriteMessages.push(fav);
        cout << "Message added to favorites.\n";
    }
    else {
        cout << "This message is already in favorites.\n";
    }
}

//Remove a message from favorites
void User::RemoveFavoriteMessage() {
    favoriteMessages.pop();
    cout << "Oldest message removed from favorites.\n";
}

//Display all favorite messages
void User::viewFavorites() {
    queue<Message> temp = favoriteMessages;
    cout << "\nFavorite messages:" << endl;
    cout << "__________________\n";
    while (!temp.empty()) {
        Message msg = temp.front(); temp.pop();
        msg.displayMessage();
        cout << "\n";
    }
}

#include "User.h"
#include "UserManager.h"
#include <iostream>
#include <unordered_map>
using namespace std;

int User::autoId = 1;

//Constructors
User::User(){}

User::User(string uname, string pwd)
    : id("U" + to_string(autoId++)), username(uname), password(pwd) {}

User::User(string id, string uname, string pwd)
    : id(id), username(uname), password(pwd) {}

//setters
void User::setautoId(int nextId) {
    autoId = nextId;
}

void User:: setContact(string& contactId, string& contactMsgCount) {
    contactList.setContact(contactId,  contactMsgCount);
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
string User::getId() {
    return id;
}

string User::getUsername() {
    return username;
}

string User::getpassword() {
    return password;
}

map<string, int> User::getContactList() {
    return contactList.getContactList();
}

vector<string> User::getSortedContacts() {
    return contactList.getSortedContacts();
}

vector<Message>& User::getReceivedMessages() {
    return receivedMessages;
}

deque<Message> User::getSentMessages() {////Nedd Modify as deque
    /*stack<Message> reversedMesssages;
    while (!sentMessages.empty()) {
        Message tempMess = sentMessages.top();
        reversedMesssages.push(tempMess);
        sentMessages.pop();
    }
    return reversedMesssages;*/
    return sentMessages;
}

queue<Message> User::getFavoriteMessages() {
    return favoriteMessages;
}

//Send a message
void  User::sendMessage(string toId, string msgContent, User& receiver) {
    Message msg(id, toId, msgContent);
    msg.setTime();
    MessageManager::addMessage(msg.getMessageId(), msg);
    sentMessages.push_back(msg);
    receiver.receiveMessage(msg);
    cout << "Message sent.\n";
}

//Receiving a new message
void User::receiveMessage(Message msg) {
    receivedMessages.push_back(msg);
    contactList.addContact(msg.getSenderId());   //added to secure contact
    contactList.updateContactOnMessage(msg.getSenderId());  //added to secure 
}

//Display all sent messages
void User::viewSentMessages() {
    deque<Message> temp = sentMessages;
    while (!temp.empty()) {
        Message msg = temp.back(); temp.pop_back();
        cout << "To User " << msg.getReceiverId() << ": " << msg.getContent() << "\n";
    }
}

//Delete last sent message
void User::undoLastMessage() {
    if (sentMessages.empty()) {
        cout << "No message to undo.\n";
        return;
    }
    Message tempMsg = sentMessages.back();
    User receiver = UserManager::searchUser(tempMsg.getReceiverId());
    receiver.getReceivedMessages().pop_back();
    MessageManager::deleteMessage(tempMsg.getMessageId());
    sentMessages.pop_back();
    cout << "Last message undone.\n";
}

//view all recieved messages

void User::view_all_recievedMessages()
{
    if (!receivedMessages.empty())
    {
        for (auto it = receivedMessages.end() - 1; ; it--)
        {
            it->displayMessage();
            if (it == receivedMessages.begin())
                break;
        }
    }
}

//view all recieved messages from specific contact
void User::view_messages_from_contact(string senderID_contact)
{
    bool found = false;
    for (Message& msg : receivedMessages) {
        if (msg.getSenderId() == senderID_contact) {
            cout << "Recieved message from a contact" << endl;
            cout << "________\n";
            msg.displayMessage();
            found = true;
        }
    }
    if (!found) {
        cout << "No messages from contact: " << senderID_contact << endl;
    }
}

//must be in main
void User::view_recieved_messagesMenu()
{
    int choice;
    char c;
    do {
        cout << "        * Recieving Messages *    \n";
        cout << "press 1 : to view all your recieved messages \n";
        cout << "press 2 : to view  recieved messages from a specific contact \n";
        cout << "press 3 : to exit\n";
        cin >> choice;
        string contactID;
        switch (choice)
        {
        case 1:
        {
            view_all_recievedMessages();
        }
        break;
        case 2:

            cout << "Enter the contact id:";
            view_messages_from_contact(contactID);
            break;

        case 3:
            return;


        default:
            break;
        }
        cout << "Continue? y: yes , n: no\n";
        cin >> c;

    } while (c != 'n' && c != 'no');

}

//contact management
void User::addContact(string contactId) {
    contactList.addContact(contactId);
}
void User::showContacts() {
    cout << contactList.displayContacts();
}

//Add message to favorites
void User::putFavorite(int msgPos) {
    if (sentMessages.empty())
    {
        cout << "No message to favorite.\n";
        return;
    }
    Message fav = receivedMessages.at(msgPos);
    fav.setIsFavorite(true);
    favoriteMessages.push(fav);
    cout << "Message added to favorites.\n";
}

//Remove a message from favorites
void User::RemoveFavoriteMessage() {
    favoriteMessages.pop();
    cout << "Oldest message removed from favorites.\n";
}

//Display all favorite messages
void User::viewFavorites() {
    queue<Message> temp = favoriteMessages;
    while (!temp.empty()) {
        Message msg = temp.front(); temp.pop();
        cout << msg.getReceiverId() << ": " << msg.getContent() << "\n";
    }
}

#include "User.h"
//#include "MessageManager.h"
//#include "ChatManager.h"

#include <iostream>
#include <unordered_map>

int User::autoId = 1;

//Constructors
User::User() {}

User::User(string uname, string pwd)
    : id("U" + to_string(autoId++)), username(uname), password(pwd) {}

User::User(string id, string uname, string pwd)
    : id(id), username(uname), password(pwd) {}

//setters
void User::setautoId(int nextId) {
    autoId = nextId;
}
/*
void User::setReceivedMessage(string msgId) {
    MessageManager messages;
    recievedMessages.push(messages.getMessage(msgId));
}

void User::setSentMessage(string msgId) {
    MessageManager messages;
    sentMessages.push(messages.getMessage(msgId));
}

void User::setFavoriteMessage(string msgId) {
    MessageManager messages;
    favoriteMessages.push(messages.getMessage(msgId));
}

void User::setchat(string chatId) {
    ChatManager allChats;
    chats[chatId] = allChats.getchat(chatId);
}
*/

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



vector<string> User::getContacts() {
    return contacts;
}


vector<Message> User:: getReceivedMessages() {
    return recievedMessages;
}

stack<Message> User::getSentMessages() {
    return sentMessages;
}
/*
queue<Message> User::getFavoriteMessages() {
    return favoriteMessages;
}

unordered_map<string, Chat> User::getchats() {
    return chats;
}

//Check password validation
bool User::validatePassword(string pwd) {
    return pwd == password;
}

//Add new contact
void User::addContact(string contactId) {
    contacts.push_back(contactId);
}

//Show all contacts
void User::showContacts() {
    cout << "Your contacts:\n";
    for (string cid : contacts) {
        cout << "- User ID: " << "\n";
    }
}
*/
//Send a message
void  User::sendMessage(string toId, string msgContent, User receiver) {
    Message msg(id, toId, msgContent);
    MessageManager allmessages;
    allmessages.setMessage(msg.getMessageId(), msg);
    sentMessages.push(msg);
    //chats[toId].addMessage(msg);
    receiver.receiveMessage(msg);
    cout << "Message sent.\n";
}

//Receiving a new message
void User::receiveMessage(Message msg) {
    //chats[msg.senderId].addMessage(msg);
    recievedMessages.push(msg);
    contactList.addContact(msg.getSenderId());   //added to secure contact
    contactList.updateContactOnMessage(msg.getSenderId());  //added to secure 
}

//Display all sent messages
void User::viewSentMessages() {
    stack<Message> temp = sentMessages;
    while (!temp.empty()) {
        Message msg = temp.top(); temp.pop();
        cout << "To User " << msg.receiverId << ": " << msg.content << "\n";
    }
}

//Delete last sent message
void User::undoLastMessage() {
    if (sentMessages.empty()) {
        cout << "No message to undo.\n";
        return;
    }
    sentMessages.pop();
    cout << "Last message undone.\n";
}

//view all recieved messages

void User::view_all_recievedMessages()
{
    if (!recievedMessages.empty())
    {
        for (auto it = recievedMessages.end() - 1; ; it--)
        {
            it->display();
            if (it == recievedMessages.begin())
                break;
        }
    }
}

void User::view_messages_from_contact(string senderID_contact)
{
    bool found = false;
    for (Message& msg : recievedMessages) {
        if (msg.getSenderId() == senderID_contact) {
            cout << "                                         Recieved message from a contact" << endl;
            cout << "                                      ________\n";
            msg.display();
            found = true;
        }
    }
    if (!found) {
        cout << "No messages from contact: " << senderID_contact << endl;
    }
}

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
vector<string> User::getContacts() {
    return contactList.getSortedContacts();
}
void User::addContact(string contactId) {
    contactList.addContact(contactId);
}
void User::showContacts() {
    cout << contactList.displayContacts();
}

/*
//Add message to favorites
void User::favoriteLastMessage() {
    if (sentMessages.empty()) {
        cout << "No message to favorite.\n";
        return;
    }
    Message fav = sentMessages.top();
    fav.isFavorite = true;
    favoriteMessages.push(fav);
    cout << "Message added to favorites.\n";
}

//Display all favorite messages
void User::viewFavorites() {
    queue<Message> temp = favoriteMessages;
    while (!temp.empty()) {
        Message msg = temp.front(); temp.pop();
        cout << "To User " << msg.receiverId << ": " << msg.content << "\n";
    }

}
*/

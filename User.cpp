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

/*
queue<Message> User:: getReceivedMessages() {
    return recievedMessages;
}

stack<Message> User::getSentMessages() {
    return sentMessages;
}

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
}

//Display specific chat
void User::viewChatWith(string otherId) {
    if (!chats.count(otherId)) {
        cout << "No chat with this user.\n";
        return;
    }
    chats[otherId].viewChat(id);
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

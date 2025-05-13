#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <vector>
#include <string>
#include "Message.h"
#include "ContactList.h"
#include "MessageManager.h"

using namespace std;

class User {
private:

    static int autoId;
    string id;
    string username;
    string password;
    ContactList contactList;
    vector<Message> receivedMessages;
    deque<Message> sentMessages;
    queue<Message> favoriteMessages;

public:

    //Constructors
    User();
    User(string uname, string pwd);
    User(string id, string uname, string pwd);

    //Setters
    static void setautoId(int nextId);
    void setPassword(const string& newPassword);
    void setContact(string& contactId, string& contactMsgCount);
    void setReceivedMessage(string msgId);
    void setSentMessage(string& msgId);
    void setFavoriteMessage(string msgId);

    //Getters
    string getId();
    string getUsername();
    string getpassword();
    vector<Message>& getReceivedMessages();
    deque<Message> getSentMessages();
    queue<Message> getFavoriteMessages();
    map<string, int> getContactList();
    vector<string> getSortedContacts();

    //Functions
    void sendMessage(string msgContent, User& receiver);
    void receiveMessage(Message msg);
    void viewSentMessages();
    void undoLastMessage();
    void view_all_recievedMessages();
    void view_messages_from_contact(string senderId_contact);
    void view_recieved_messagesMenu();
    void putFavorite(int msgPos);
    void RemoveFavoriteMessage();
    void viewFavorites();
    void addContact(string contactId);
    void removeContact(string contactId);
    void showContacts();

};

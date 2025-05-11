#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
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
    stack<Message> sentMessages;
    queue<Message> favoriteMessages;

public:

    //Constructors
    User();
    User(string uname, string pwd);
    User(string id, string uname, string pwd);

    //Setters
    static void setautoId(int nextId);
    void setContact(string& contactId, string& contactMsgCount);
    void setReceivedMessage(string msgId);
    void setSentMessage(string& msgId);
    void setFavoriteMessage(string msgId);

    //Getters
    string getId();
    string getUsername();
    string getpassword();
    vector<Message>& getReceivedMessages();
    stack<Message> getSentMessages();
    queue<Message> getFavoriteMessages();
    map<string, int> getContactList();
    vector<string> getSortedContacts();

    //Functions
    void sendMessage(string toId, string msgContent, User& receiver);
    void receiveMessage(Message msg);
    void viewSentMessages();
    void undoLastMessage();
    void view_all_recievedMessages();
    void view_messages_from_contact(string senderID_contact);
    void view_recieved_messagesMenu();
    void putFavorite(int msgPos);
    void RemoveFavoriteMessage();
    void viewFavorites();
    void addContact(string contactId);
    void showContacts();
};
/*U1
Toaa Emad
toaa#123
2
U2, 0, U7, 0

U6
ghalia
helloghalia
1
U4, 1

U2
Farah Mohamed
farah#456
2
U6, 0, U4, 0

U3

U8
adam
helloadam
2
U7, 1, U3, 0

U5
Salwa Hamdy
salwa#123
4
U1, 0, U2, 0, U3, 0, U6, 0

U7
habiba
hellohabiba*/
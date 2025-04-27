#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <vector>
#include <string>
//#include "Message.h"
//#include "Chat.h"

using namespace std;

class User {
private:
    static int autoId;
    string id;
    string username;
    string password;
    //string mobileNumber;
    vector<string> contacts;
    //stack<Message> sentMessages;
    //queue<Message> recievedMessages;
    //queue<Message> favoriteMessages;
    //unordered_map<string, Chat> chats;

public:
    User();
    User(string uname, string pwd);
    User(string id, string uname, string pwd);


    void setautoId(int nextId);
    //void setReceivedMessage(string msgId);
    //void setSentMessage(string msgId);
    //void setFavoriteMessage(string msgId);
    //void setchat(string chatId);

    string getId();
    string getUsername();
    string getpassword();
    vector<string> getContacts();

    /*queue<Message> getReceivedMessages();
    stack<Message> getSentMessages();
    queue<Message> getFavoriteMessages();
    unordered_map<string, Chat> getchats();


    bool validatePassword(string pwd);

    void addContact(string contactId);

    void showContacts();

    void sendMessage(string toId, string msgContent, User receiver);

    void receiveMessage(Message msg);

    void viewChatWith(string otherId);

    void viewSentMessages();

    void undoLastMessage();

    void favoriteLastMessage();

    void viewFavorites();
    */
};


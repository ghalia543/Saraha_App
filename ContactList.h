#pragma once
#include<vector>
#include <string>
#include <set>
#include <map>
#include <stdexcept>
#include "Message.h"

using namespace std;

class ContactList {
private:
    set<string> contacts;
    map<string, int> messageCount;

public:
    ContactList();
    void setContact(const string& contactUsername, string& contactMsgCount);
    map<string, int> getContactList();
    void addContact(const string& uname, vector<Message>);
    void removeContact(const string& uname);
    bool searchContact(const string& uname);
    vector <string> getSortedContacts() const;
    string displayContacts() const;
    void updateContactOnMessage(const string& senderUsername);
    void minusNumberOfMessages(const string& senderUsername);
};

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
    void setContact(const string& contactId, string& contactMsgCount);
    map<string, int> getContactList();
    void addContact(const string& uid, vector<Message>);
    void removeContact(const string& uid);
    bool searchContact(const string& uid);
    vector <string> getSortedContacts() const;
    string displayContacts() const;
    void updateContactOnMessage(const string& senderId);
    void minusNumberOfMessages(const string& senderId);
};

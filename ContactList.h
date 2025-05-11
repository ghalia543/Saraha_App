#pragma once
#include<vector>
#include <string>
#include <set>
#include <map>
#include <stdexcept>

using namespace std;

class ContactList {
private:
    set<string> contacts;
    map<string, int> messageCount;

public:
    ContactList();
    void setContact(const string& contactId, string& contactMsgCount);
    map<string, int> getContactList();
    void addContact(const string& id);
    void removeContact(const string& id);
    bool searchContact(const string& id);
    vector <string> getSortedContacts() const;
    string displayContacts() const;
    void updateContactOnMessage(const string& senderId);
};
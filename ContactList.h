#pragma once
#include<vector>
#include <string>
#include <set>
#include <map>
#include <stdexcept>

class ContactList {
private:
    std::set<std::string> contacts;
    std::map<std::string, int> messageCount;

public:
    ContactList();
    void addContact(const std::string& id);
    void removeContact(const std::string& id);
    bool searchContact(const std::string& id);
    std:: vector <std::string> getSortedContacts() const;
    std:: string displayContacts() const;
    void updateContactOnMessage(const std::string& senderId);
};
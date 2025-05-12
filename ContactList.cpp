#include "ContactList.h"
#include <iostream>
#include<vector>
#include <algorithm> 
#include <stdexcept>
#include <sstream>  

using namespace std;

ContactList::ContactList() {}

void ContactList::setContact(const string& contactId, string& contactMsgCount) {
    contacts.insert(contactId);
    messageCount[contactId] = stoi(contactMsgCount);
}

map<string, int> ContactList::getContactList() {
    return messageCount;
}

void ContactList::addContact(const string& id, vector<Message> recievedMessages) {
    bool found = false;
    int numOfMessages = 0;
    for (Message& msg: recievedMessages) {
        if (msg.getSenderId() == id) {
            found = true;
            numOfMessages++;
        }
    }
    if (!found) {
        cout << "This ID didn't send a message before\n";
        return;
    }
    if (contacts.find(id) != contacts.end()) {
        cout << "Contact already exists: " << id << endl;
        return;
    }
    if (messageCount.find(id) != messageCount.end()) {
        cout << "Can't add user(" << id << ") into contacts." << endl;
    }
    else {
        messageCount[id] = numOfMessages;
        contacts.insert(id);
        cout << "New contact added: " << id << endl;
    }
}

void ContactList::removeContact(const string& id) {
    if (contacts.find(id) == contacts.end()) {
        throw runtime_error("Contact not found: " + id);
    }
    contacts.erase(id);
    messageCount.erase(id);
    cout << "Contact removed.\n";
}

bool ContactList::searchContact(const string& id) {
    bool found = contacts.find(id) != contacts.end();
    cout << (found ? "Found: " : "Not found: ") << id << endl;
    return found;
}

vector <string> ContactList::getSortedContacts() const {
    // First, create a vector of all contact IDs
    vector<string> sortedContacts;
    sortedContacts.reserve(contacts.size());

    for (const auto& contact : contacts) {
        sortedContacts.push_back(contact);
    }

    // Sort the vector based on message counts (highest to lowest)
    sort(sortedContacts.begin(), sortedContacts.end(),
        [this](const string& a, const string& b) {
            // Get message counts for both contacts
            auto itA = messageCount.find(a);
            auto itB = messageCount.find(b);

            int countA = (itA != messageCount.end()) ? itA->second : 0;
            int countB = (itB != messageCount.end()) ? itB->second : 0;

            // Sort by message count in descending order
            if (countA != countB) {
                return countA > countB; // Higher count first
            }

            // If counts are equal, sort alphabetically as a tiebreaker
            return a < b;
        });

    return sortedContacts;
}

// Return a formatted string with all contacts and their message counts
string ContactList::displayContacts() const {
    stringstream output;

    // Get contacts sorted by message count
    vector<string> sortedContacts = getSortedContacts();

    if (sortedContacts.empty()) {
        output << "No contacts in the list." << endl;
    }
    else {
        output << "Contact List (sorted by message count):" << endl;
        output << "------------------------------------" << endl;

        for (const auto& contact : sortedContacts) {
            // Find message count in the map
            auto it = messageCount.find(contact);
            int count = (it != messageCount.end()) ? it->second : 0;

            output << "ID: " << contact << " - Messages: " << count << endl;
        }
    }

    // return the full string 
    return output.str();
}

// Update the message count when a contact sends a message
void ContactList::updateContactOnMessage(const string& senderId) {
    // Check if the sender is in our contacts
    if (!searchContact(senderId)) {
        throw invalid_argument("Cannot update message count for non-existent contact: " + senderId);
    }

    // Increment message count
    messageCount[senderId]++;
}

void ContactList::minusNumberOfMessages(const string& senderId)
{
    if (!searchContact(senderId)) {
        throw invalid_argument("Cannot update message count for non-existent contact: " + senderId);
    }

    messageCount[senderId]--;
}

#include "ContactList.h"
#include "UserManager.h"
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

void ContactList::addContact(const string& uid, vector<Message> recievedMessages) {
    bool found = false;
    int numOfMessages = 0;
    for (Message& msg : recievedMessages) {
        string senderId = msg.getSenderId();
        if (uid == senderId) {
            found = true;
            numOfMessages++;
        }
    }
    if (!found) {
        cout << "This user didn't send a message before\n";
        return;
    }
    if (contacts.find(uid) != contacts.end()) {
        cout << "Contact already exists: " << uid << endl;
        return;
    }
    if (messageCount.find(uid) != messageCount.end()) {
        cout << "Can't add user(" << uid << ") into contacts." << endl;
    }
    else {
        messageCount[uid] = numOfMessages;
        contacts.insert(uid);
        cout << "New contact added: " << uid << endl;
    }
}

void ContactList::removeContact(const string& uid) {
    if (contacts.find(uid) == contacts.end()) {
        throw runtime_error("Contact not found: " + uid);
    }
    contacts.erase(uid);
    messageCount.erase(uid);
    cout << "Contact removed.\n";
}

bool ContactList::searchContact(const string& uid) {
    bool found = contacts.find(uid) != contacts.end();
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

    if (!sortedContacts.empty()){
        output << "Contact List (sorted by message count):" << endl;
        output << "------------------------------------" << endl;

        for (const auto& contact : sortedContacts) {
            // Find message count in the map
            auto it = messageCount.find(contact);
            int count = (it != messageCount.end()) ? it->second : 0;

            output << "Username: " << contact << " - Messages: " << count << endl;
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

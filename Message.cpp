// Message.cpp
#include "Message.h"
#include <iostream>
using namespace std;

Message::Message(string from, string to,  string text)
    : senderId(from), receiverId(to), content(text), isFavorite(false) {
    sentTime = std::time(nullptr);
}

// Getters
string Message::getSenderId()  { return senderId; }
string Message::getReceiverId()  { return receiverId; }
string Message::getContent()  { return content; }
bool Message::getIsFavorite()  { return isFavorite; }

// This formats the sentTime nicely
string Message::getSentTime()  {
    tm* localTime = std::localtime(&sentTime);
    ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Setters
void Message::setSenderId(string id) { senderId = id; }
void Message::setReceiverId(string id) { receiverId = id; }
void Message::setContent( string& text) { content = text; }
void Message::setIsFavorite(bool favorite) { isFavorite = favorite; }

// Display method
void Message::display()  {
    cout << "From: " << senderId << ", To: " << receiverId << "\n";
    cout << "Message: " << content << "\n";
    cout << "Favorite: " << (isFavorite ? "Yes" : "No") << "\n";
    cout << "Sent at: " << getSentTime() << "\n";
}

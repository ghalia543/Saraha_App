// Message.cpp
#include "Message.h"
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int Message::autoId = 1;

Message::Message() {}

Message::Message(string from, string to, string text)
    : messageId("M" + to_string(autoId++)), senderId(from), receiverUsername(to), content(text), isFavorite(false) {
    sentTime = "";
}

Message::Message(string messID, string from, string to, string text)
    : messageId(messID), senderId(from), receiverUsername(to), content(text), isFavorite(false) {
    sentTime = "";
}

// Getters
string Message::getMessageId() { return messageId; }
string Message::getSenderId() { return senderId; }
string Message::getReceiverUsername() { return receiverUsername; }
string Message::getContent() { return content; }
bool Message::getIsFavorite() { return isFavorite; }

// This formats the sentTime nicely
string Message::getSentTime() {
    return sentTime;
}

// Setters
void Message::setautoId(int nextId) {
    autoId = nextId;
}
void Message::setMessageId(string id) { messageId = id; }
void Message::setSenderId(string id) { senderId = id; }
void Message::setReceiverUsername(string uname) { receiverUsername = uname; }
void Message::setContent(string& text) { content = text; }
void Message::setIsFavorite(bool favorite) { isFavorite = favorite; }
void Message::setTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    sentTime = buffer;
}
/*void Message::setTime() {
    time_t formattedSentTime = std::time(nullptr);;
    tm* localTime = std::localtime(&formattedSentTime);
    std::ostringstream oss;
    oss << put_time(localTime, "%Y-%m-%d %H:%M:%S");
    sentTime = oss.str();
}*/
void Message::setTime(string time) { sentTime = time; }

// Display method
void Message::displayMessage() {
    cout << "From: " << senderId << "\n";
    cout << "Message: " << content << "\n";
    cout << "Favorite: " << (isFavorite ? "Yes" : "No") << "\n";
    cout << "Sent at: " << getSentTime() << "\n";
}

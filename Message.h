// Message.h
#ifndef MESSAGE_H
#define MESSAGE_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <ctime>
using namespace std;
class Message {
private:
    string senderId;
    string receiverId;
    string content;
    bool isFavorite;
    time_t sentTime;

public:
    Message(string from, string to,  string text);

    // Getters
    string getSenderId() ;
    string getReceiverId() ;
    string getContent() ;
    bool getIsFavorite() ;
    string getSentTime() ; // return formatted time string

    // Setters
    void setSenderId(string id);
    void setReceiverId(string id);
    void setContent( string& text);
    void setIsFavorite(bool favorite);

    // Display method
    void display() ;
};

#endif // MESSAGE_H



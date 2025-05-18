// Message.h
#ifndef MESSAGE_H
#define MESSAGE_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <ctime>

using namespace std;
enum Sentiment
{
    positive,  //0
    negative,  //1
    neutral    //2
};

class Message {
private:
    static int autoId;
    string messageId;
    string senderId;
    string receiverUsername;
    string content;
    bool isFavorite;
    string sentTime;
    Sentiment sentiment=neutral;

public:

    //Constructors
    Message();
    Message(string from, string to, string text);
    Message(string messID, string from, string to, string text);

    // Getters
    string getMessageId();
    string getSenderId();
    string getReceiverUsername();
    string getContent();
    bool getIsFavorite();
   string getSentTime(); // return formatted time string
   Sentiment getSentiment();

    // Setters
    void setautoId(int nextId);
    void setMessageId(string id);
    void setSenderId(string id);
    void setReceiverUsername(string id);
    void setContent(string& text);
    void setIsFavorite(bool favorite);
    void setTime();
    void setTime(string time);
    void setSentiment(Sentiment);

    // Functions
    void displayMessage();
    void sentimentAnalysis();
    string showSentiment();
};

#endif // MESSAGE_H

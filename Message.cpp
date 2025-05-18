// Message.cpp
#include "Message.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <unordered_set>
# include <sstream>

using namespace std;

int Message::autoId = 1;

Message::Message() { }

Message::Message(string from, string to, string text)
{
   
    messageId = "M" + to_string(autoId++);
    senderId = from;
    receiverUsername = to;
    content = text;
    isFavorite = false;
    sentTime = "";
   
    sentimentAnalysis();

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

Sentiment Message::getSentiment()
{
    return sentiment;
}

string Message::showSentiment()
{
    switch(sentiment)
    {
    case positive:
        return "positive";
        break;
    case negative :
        return "negative";
        break;
    case neutral:
            return "neutral";
            break;

    }
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

void Message::setSentiment(Sentiment s)
{
    sentiment = s;
   
}



// Display method
void Message::displayMessage() {
   
    cout << "From: " << senderId << "\n";
    cout << "Message: " << content << "\n";
    cout << "Favorite: " << (isFavorite ? "💌Yes" : "💔No") << "\n";
    cout << "Sent at: " << getSentTime() << "\n";
    cout << "sentiment/emotion: " << showSentiment() << "\n\n";
}

void Message::sentimentAnalysis()
{
    int PosCounter = 0;
    int negCounter = 0;

    unordered_set<string> positiveWords = { "happy", "love", "thank", "amazing", "great", "wonderful", "awesome",
        "nice", "beautiful", "perfect", "cool", "fun", "excited", "proud", "joy", "lovely",
        "kind", "fantastic", "enjoy", "smile", "helpful", "excellent", "cute",
        "inspiring", "talented", "smart", "friendly", "hardworking", "congratulations" , "brilliant" ,"good"};

    unordered_set<string> negativeWords = {
    "angry", "hate", "bad", "annoyed", "disappointed", "terrible", "sad", "upset",
    "horrible", "boring", "stupid", "awful", "worst", "pain", "frustrated", "mad",
    "useless", "ugly", "tired", "rude", "depressed", "liar", "toxic",
    "selfish", "lazy", "fake", "!!", "!!!"
    };



    // to turn each message's content into separated words
    string word;
    
        stringstream ss(content);        // used library sstream    
        while (ss >> word)             
    //   >> that operator reads the content like any inputstream (cin) from the string stream  object until there is nothing to read 
          
        {
        
            if (positiveWords.count(word))
                PosCounter++;
            else if (negativeWords.count(word))
                negCounter++;

        }
        cout << "Message Sentiment Analysis\n" << "positive words :" << PosCounter
            << "\nnegative words :" << negCounter << endl;

        if (PosCounter > negCounter)
        {
            setSentiment(positive);
        }
        else if (PosCounter < negCounter)
        {
            setSentiment(negative);
        }
        else
        {
           setSentiment(neutral);
        }

    //    cout << showSentiment();
    
}


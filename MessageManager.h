#pragma once
#include "Message.h"
#include <string>
#include <unordered_map>

using namespace std;

class MessageManager
{
private:
	const string MessageFilePath = "messages.txt";
	static unordered_map <string, Message> messages;


public:
	MessageManager();

	bool loadMessagesFromFile();
	bool saveMessagesToFile();
	static void addMessage(string mID, Message& newMessage);
	static Message getMessage(string& mID);
	static void deleteMessage(string mID);
};

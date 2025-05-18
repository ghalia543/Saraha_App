#include "MessageManager.h"
#include "UserManager.h"
#include "User.h"
#include "Message.h"
#include <fstream>

unordered_map <string, Message> MessageManager::messages;

MessageManager::MessageManager() {}

bool MessageManager::loadMessagesFromFile() {
	ifstream messageIN(MessageFilePath);

	if (!messageIN) {
		return false;
	}

	Message message;
	string msgID, senderID, receiverID, msgContent, time, isFavorite , sentiment;
	

	while (getline(messageIN, msgID) && getline(messageIN, senderID)
		&& getline(messageIN, receiverID) && getline(messageIN, msgContent)) {

		message = Message(msgID, senderID, receiverID, msgContent);

		bool favorite;
		getline(messageIN, isFavorite);
		if (isFavorite == "true" || isFavorite == "1") {
			favorite = true;
		}
		else {
			favorite = false;
		}
		message.setIsFavorite(favorite);
		getline(messageIN, sentiment);

		if (sentiment == "positive")
			message.setSentiment(positive);
		else if (sentiment == "negative")
			message.setSentiment(negative);
		else 
			message.setSentiment(neutral);

		getline(messageIN, time);
		message.setTime(time);

		messages.insert({ msgID, message });
	}

	message.setautoId(messages.size() + 1);
	return true;
}

bool MessageManager::saveMessagesToFile() {
	ofstream messageOut(MessageFilePath);

	if (!messageOut) {
		return false;
	}

	unordered_map<string, Message>::iterator it;
	for (it = messages.begin(); it != messages.end(); it++) {
		string msgID = it->first;
		Message& msg = it->second;
		messageOut << msgID << "\n"
			<< msg.getSenderId() << "\n"
			<< msg.getReceiverUsername() << "\n"
			<< msg.getContent() << "\n"
			<< msg.getIsFavorite() << "\n"
			<< msg.showSentiment() <<"\n"
			<< msg.getSentTime() << "\n";
	}
	messageOut.close();
	return  true;
}
void MessageManager::addMessage(string mID, Message& newMessage) {
	messages[mID] = newMessage;
}

Message MessageManager::getMessage(string& mID) {
	if (messages.find(mID) != messages.end()) {
		return messages.at(mID);
	}
	else {
		return Message();
	}
}
void MessageManager::deleteMessage(string mID) {
	messages.erase(mID);
}

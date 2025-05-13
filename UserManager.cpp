#include "UserManager.h"
#include "User.h"
#include "ContactList.h"
#include <fstream>
#include <sstream>

unordered_map<string, User> UserManager::users;

UserManager::UserManager() {}

bool UserManager::loadUsersFromFile() {
	ifstream userIN(UserFilePath);

	if (!userIN) {
		return false;
	}

	User user;
	string id, uname, pwd;
	int contactsCount, receivedMessagesCount,
		sentMessagesCount, FavoriteMessagesCount;

	while (getline(userIN, id) && getline(userIN, uname) && getline(userIN, pwd)) {

		User user(id, uname, pwd);

		userIN >> contactsCount;
		userIN.ignore();
		if (contactsCount > 0) {
			string line;
			getline(userIN, line);
			stringstream stream(line);
			for (int i = 0; i < contactsCount; i++) {
				string contactUsername, contactMsgCount;
				if (!getline(stream, contactUsername, ',')) {
					cout << "Warning: Missing contact ID at index " << i << endl;
					break;
				}

				if (!getline(stream, contactMsgCount, ',')) {
					cout << "Warning: Missing contact message count for user " << contactUsername << endl;
					break;
				}
				user.setContact(contactUsername, contactMsgCount);
			}
		}

		userIN >> receivedMessagesCount;
		userIN.ignore();
		if (receivedMessagesCount > 0) {
			string line;
			getline(userIN, line);
			stringstream stream(line);
			for (int i = 0; i < receivedMessagesCount; i++) {
				string messId;
				if (!getline(stream, messId, ',')) {
					cout << "Warning: expected " << receivedMessagesCount << " message IDs, but found fewer.\n";
					break;
				}
				user.setReceivedMessage(messId);
			}
		}

		userIN >> sentMessagesCount;
		userIN.ignore();
		if (sentMessagesCount > 0) {
			string line;
			getline(userIN, line);
			stringstream stream(line);
			for (int i = 0; i < sentMessagesCount; i++) {
				string messId;
				if (!getline(stream, messId, ',')) {
					cout << "Warning: expected " << sentMessagesCount << " message IDs, but found fewer.\n";
					break;
				}
				user.setSentMessage(messId);
			}
		}
		userIN >> FavoriteMessagesCount;
		userIN.ignore();
		if (FavoriteMessagesCount > 0) {
			string line;
			getline(userIN, line);
			stringstream stream(line);
			for (int i = 0; i < FavoriteMessagesCount; i++) {
				string messId;
				if (!getline(stream, messId, ',')) {
					cerr << "Warning: expected " << FavoriteMessagesCount << " message IDs, but found fewer.\n";
					break;
				}
				user.setFavoriteMessage(messId);
			}
		}
		users[uname] = user;
	}
	User::setautoId(users.size() + 1);
	return true;
}

bool UserManager::saveUsersToFile() {
	ofstream userOut(UserFilePath);

	if (!userOut) {
		return false;
	}

	unordered_map<string, User>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		string username = it->first;
		User& user = it->second;
		map<string, int> userContactList = user.getContactList();
		vector<Message>& userReceivedMessages = user.getReceivedMessages();
		deque<Message> userSentMessages = user.getSentMessages();
		queue<Message> userFavoriteMessages = user.getFavoriteMessages();
		userOut << user.getId() << "\n"
			<< username << "\n"
			<< user.getpassword() << "\n"
			<< user.getContactList().size() << "\n";

		bool first = true;
		if (!userContactList.empty()) {
			map<string, int>::iterator contactIt;
			for (contactIt = userContactList.begin(); contactIt != userContactList.end(); contactIt++) {
				if (!first) {
					userOut << ',';
				}
				userOut << contactIt->first << "," << contactIt->second;
				first = false;
			}
			userOut << "\n";
		}

		userOut << userReceivedMessages.size();
		first = true;
		for (int j = 0; j < userReceivedMessages.size(); j++) {
			if (!first) {
				userOut << ',';
			}
			else {
				userOut << "\n";
			}
			userOut << userReceivedMessages[j].getMessageId();
			first = false;
		}

		userOut << "\n" << userSentMessages.size();
		first = true;
		while (!userSentMessages.empty()) {
			if (!first) {
				userOut << ',';
			}
			else {
				userOut << "\n";
			}
			userOut << userSentMessages.front().getMessageId();
			userSentMessages.pop_front();
			first = false;
		}

		userOut << "\n" << userFavoriteMessages.size();
		first = true;
		while (!userFavoriteMessages.empty()) {
			if (!first) {
				userOut << ',';
			}
			else {
				userOut << "\n";
			}
			userOut << userFavoriteMessages.front().getMessageId();
			userFavoriteMessages.pop();
			first = false;
		}
		userOut << "\n";
	}
	userOut.close();
	return true;
}

//Used in user registeration
void UserManager::addUser(string uname, User& newUser) {
	users[uname] = newUser;
}

User& UserManager::searchUser(string uname) {
	if (users.count(uname)) {
		return users.at(uname);
	}
	else {
		throw runtime_error("User not found");
	}
}

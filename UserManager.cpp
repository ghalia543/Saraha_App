#include "User.h"
#include "UserManager.h"
//#include "MessageManager.h"
//#include "ChatManager.h"
#include <fstream>

unordered_map<string, User> UserManager::users;
//unordered_set<string> UserManager::mobileNumbers;

UserManager::UserManager() {}

bool UserManager::loadUsersFromFile() {
	ifstream userIN(UserFilePath);

	if (!userIN) {
		return false;
	}

	User user;
	string id, uname, pwd;
	int contactsCount, receivedMessagesCount,
		sentMessagesCount, FavoriteMessagesCount, chatsCount;

	while (getline(userIN, id) && getline(userIN, uname) && getline(userIN, pwd) ) {

		user = User(id, uname, pwd);
		/*
		userIN >> contactsCount;
		userIN.ignore();
		for (int i = 0; i < contactsCount; i++) {
			string contactId;
			getline(userIN, contactId, ',');
			user.addContact(contactId);
		}

		userIN >> receivedMessagesCount;
		for (int i = 0; i < receivedMessagesCount; i++) {
			string messageId;
			getline(userIN, messageId, ',');
			user.setReceivedMessage(messageId);
		}

		userIN >> sentMessagesCount;
		for (int i = 0; i < sentMessagesCount; i++) {
			string messageId;
			getline(userIN, messageId, ',');
			user.setSentMessage(messageId);
		}

		userIN >> FavoriteMessagesCount;
		for (int i = 0; i < FavoriteMessagesCount; i++) {
			string messageId;
			getline(userIN, messageId, ',');
			user.setFavoriteMessage(messageId);
		}

		userIN >> chatsCount;
		for (int i = 0; i < chatsCount; i++) {
			string chatId;
			getline(userIN, chatId, ',');
			user.setchat(chatId);
		}
*/
		users[user.getUsername()] = user;
		//mobileNumbers.insert(mobileNum);
	}
	user.setautoId(users.size() + 1);
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
		//vector<string> userContacts = user.getContacts();
		//queue<Message> userReceivedMessages = user.getReceivedMessages();
		//stack<Message> userSentMessages = user.getSentMessages();
		//queue<Message> userFavoriteMessage = user.getFavoriteMessages();
		//unordered_map<string, Chat> userchat = user.getchats();
		userOut << user.getId() << "\n"
			<< username << "\n"
			<< user.getpassword() << "\n";
			//<< user.getMobileNumber() << "\n";
		//<< userContacts.size() << "\n";

/*bool first = true;
for (string uId : userContacts) {
	if (!first) {
		userOut << ',';
	}
	userOut << uId;
	first = false;
}

userOut << "\n" << userReceivedMessages.size() << "\n";
first = true;
while(!userReceivedMessages.empty()){
	if (!first) {
		userOut << ',';
	}
	userOut << userReceivedMessages.front().getMessageId();
	userReceivedMessages.pop();
	first = false;
}

userOut << "\n" << userSentMessages.size() << "\n";
first = true;
while (!userSentMessages.empty()) {
	if (!first) {
		userOut << ',';
	}
	userOut << userSentMessages.top().getMessageId();
	userSentMessages.pop();
	first = false;
}

userOut << "\n" << userFavoriteMessage.size() << "\n";
first = true;
while (!userFavoriteMessage.empty()) {
	if (!first) {
		userOut << ',';
	}
	userOut << userFavoriteMessage.front().getMessageId();
	userFavoriteMessage.pop();
	first = false;
}

userOut << "\n" << userchat.size() << "\n";
first = true;
for (const auto& chatPair : userchat) {
	string chatId = chatPair.first;
	if (!first) {
		userOut << ',';
	}
	userOut << chatId;
	first = false;
}
userOut << "\n";
*/
	}
	userOut.close();
	return true;
}

void UserManager::addUser(string uname, User& newUser) {
	users[uname] = newUser;
	//mobileNumbers.insert(newUser.getMobileNumber());
}

User& UserManager::searchUser(string uname) {
	if (users.count(uname)) {
		return users.at(uname);
	}
	else {
		throw runtime_error("User not found");
	}
}
/*
bool UserManager::searchMobileNumber(string mobileNumber) {
	if (mobileNumbers.count(mobileNumber)) {
		return true;
	}
	else {
		return false;
	}
}
*/
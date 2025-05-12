#pragma once
#include<string>
#include<unordered_map>
#include <unordered_set>
#include"User.h"

using namespace std;

class UserManager
{
private:
	const string UserFilePath = "users.txt";
	static unordered_map <string, User> users;
	static unordered_map<string, string> idToUsername;

public:
	UserManager();

	bool loadUsersFromFile();
	bool saveUsersToFile();
	/*unordered_map <string, User> return_user() {
		return users;
	}*/
	static void addUser(string uname, User& newUser);
	static User& searchUser(string uname);
	static User& searchUserById(string uid);
};

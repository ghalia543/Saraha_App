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

public:
	UserManager();

	bool loadUsersFromFile();
	bool saveUsersToFile();
	static void addUser(string uname, User& newUser);
	static User& searchUser(string uname);
};

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
	//static unordered_set<string> mobileNumbers;


public:
	UserManager();

	bool loadUsersFromFile();
	bool saveUsersToFile();

	void addUser(string uname, User& newUser);
	User& searchUser(string uname);
	//bool searchMobileNumber(string mobileNumber);
};

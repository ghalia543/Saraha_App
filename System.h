#pragma once
#include "UserManager.h"
#include <string>
#include <unordered_map>
#include <conio.h> 
#include "User.h"

class System {
private:
    User* current_LoggedIN_user;
public:
    System();
    bool registerUser(const std::string& uname, const std::string& pass);
    bool login(const std::string& username, const std::string& password);
    User& getCurrent_LoggedIN_user();
    void setCurrent_LoggedIN_user(User& user);
    void changeUserPassword(const string& userId, const string& newPassword);
    static string HidePassword();
};

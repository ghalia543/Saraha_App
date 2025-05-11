#pragma once
#include "UserManager.h"
#include <string>
#include <unordered_map>

class System
{

public:
    System();
    bool registerUser(const string& uname, const string& pass);
    bool login(const string& username, const string& password);

};


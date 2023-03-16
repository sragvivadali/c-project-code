#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

UserDatabase::UserDatabase() {
    m_loaded = false;
}

UserDatabase::~UserDatabase()
{
    for (int i = 0; i < m_userList.size(); i++)    //delete all dynamically allocated user objects
        delete m_userList[i];
}

bool UserDatabase::load(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file \"" << filename << "\"" << endl;
        return false;
    }
    string line;
    int lineCount = 0;
    string name;
    string email;
    int size;
    vector<string> watchHistory;
    while (getline(file, line)){
        switch (lineCount){
            case 0:
                name = line;
                lineCount ++;
                break;
            case 1:
                email = line;
                lineCount ++;
                break;
            case 2:
                size = stoi(line);
                lineCount ++;
                break;
            case 3:
                for (int i = 0; i < size; ++i) {
                    getline(file, line);
                    watchHistory.push_back(line);
                }
            default:
                User* user = new User(name, email, watchHistory);
                m_userList.push_back(user);
                m_users.insert(email, user);
                name = "";
                email = "";
                size = 0;
                lineCount = 0;
                watchHistory.clear();
                break;
        }
    }

    m_loaded = true;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator it = m_users.find(email);
    if(!it.is_valid()) 
        return nullptr;
    return it.get_value();
}
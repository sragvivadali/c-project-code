#include "UserDatabase.h"
#include "User.h"
#include "treemm.h"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{
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
                m_users.insert(email, user);
                name = "";
                email = "";
                size = 0;
                lineCount = 0;
                watchHistory.clear();
                break;
        }
    }

    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    return m_users.find(email).get_value();
}

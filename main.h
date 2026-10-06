//password manager
#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>

struct Password
{
    std::string name;
    std::string password;
    std::string category;
};

class PasswordManager
{
    private:
    std::vector<Password> password_storage;
    std::vector<std::string> categories;
    std::string generate_password(int length);

    public:
    void add_password();
    void delete_password();
    void edit_password();
    void search_password(const std::string& queery);
    //--------------------------------------------------------
    void add_category();
    void del_category();
    //--------------------------------------------------------
    void print_vector();
};

#endif
//password manager
#include <iostream>

#include "main.h"

std::string PasswordManager::generate_password(int length)
{
    const std::string lowerChars   = "abcdefghijklmnopqrstuvwxyz";
    const std::string upperChars   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string specialSet   = "!@#$%^&*()-+=~`;:'?/";

    std::string combinedChars;
    combinedChars += upperChars;
    combinedChars += lowerChars;
    combinedChars += specialSet;

    if (combinedChars.empty()) {
        throw std::invalid_argument("At least one character set must be selected");
    }

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, combinedChars.size() - 1);

    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += combinedChars[dist(rng)];
    }
    return result;
}

void PasswordManager::add_password() {
    Password m_password;
    std::cout << "add a new password: ";
    
    std::cout << "Names: ";
    getline(std::cin , m_password.name);
    
    std::cout << "Do you want to generate random password? y/n : ";
    char y_or_n;
    std::cin >> y_or_n;
    if (y_or_n == 'y') {
        int length;
        
        std::cout << "Password length: ";
        std::cin >> length;
        std::cin.ignore();
        
        m_password.password = generate_password(length);
        
        std::cout << "witch category you want to add in: ";
        getline(std::cin, m_password.category);

        std::cout << m_password.password << std::endl;

        password_storage.push_back(m_password);
    }
    if (y_or_n == 'n') {
        return;
    }
}

void PasswordManager::edit_password() {}

void PasswordManager::delete_password() {}

void PasswordManager::search_password(const std::string& queery) {}

void PasswordManager::add_category()
{
    std::string category;
    std::cout << "Enter category: ";
    std::cin >> category;
    categories.push_back(category);
    for (const auto& cat : categories)
    {
        std::cout << "Category added :" << cat << " \n" << std::endl;
    }
}

void PasswordManager::del_category() {}

int main()
{
    PasswordManager m_pass;
    int choice;
    std::string queery;

    while (true)
    {
        std::cout << "Enter your choice: \n";
        std::cout << "1- Add category\n";
        std::cout << "2- Add password\n";
        std::cout << "3- Search password\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                m_pass.add_category();
            break;
            case 2:
                m_pass.add_password();
            break;
            case 3:
                m_pass.search_password(queery);
            break;
        }
    }
}
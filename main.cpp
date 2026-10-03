//password manager
#include <iostream>

#include "main.h"

std::string PasswordManager::generate_password(int length, bool to_lowercase, bool to_uppercase, char special_chars)
{
    srand(time(NULL));
    const std::string lowerChars = "abcdefghijklmnopqrstuvwxyz";
    const std::string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string specialChars = "!@#$%^&*()-+=~`;:'?/";

    std::string combinedChars;

    if (to_uppercase) {
        combinedChars += upperChars;
    }
    if (to_lowercase) {
        combinedChars += lowerChars;
    }
    if (special_chars) {
        combinedChars += specialChars;
    }

    std::string result;

    int combinedCharslength = combinedChars.length();

    for (int i = 0;i < length;i++)
    {
        int randomIndex = rand() % combinedCharslength;
        result = combinedChars[randomIndex];
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
        bool includeUppercase, includeLowercase, includeSpecialChars;
        
        std::cout << "Password length: ";
        std::cin >> length;
        std::cin.ignore();

        std::cout << "Include uppercase letters? (Y/N): ";
        char upperChoice;
        std::cin >> upperChoice;
        std::cin.ignore();
        tolower(upperChoice);
        includeUppercase = (upperChoice == 'y');

        std::cout << "Include lowercase letters? (Y/N): ";
        char lowerChoice;
        std::cin >> lowerChoice;
        std::cin.ignore();
        tolower(lowerChoice);
        includeLowercase = (lowerChoice == 'y');

        std::cout << "Include special characters? (Y/N): ";
        char specialChoice;
        std::cin >> specialChoice;
        std::cin.ignore();
        tolower(specialChoice);
        includeSpecialChars = (specialChoice == 'y');

        m_password.password = generate_password(length, includeLowercase, includeUppercase, includeSpecialChars);

        std::cout << m_password.password;
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
    std::cout << "Category added" << std::endl;
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
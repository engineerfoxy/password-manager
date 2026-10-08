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
    std::cout << "Let's add a new password \n";
    
    std::cout << "Names: ";
    getline(std::cin , m_password.name);
    int length;
        
    std::cout << "Password length: ";
    std::cin >> length;
    std::cin.ignore();
        
    m_password.password = generate_password(length);
        
    std::cout << "witch category you want to add in: ";
    getline(std::cin, m_password.category);

    if (!copy_to_clipboard(m_password.password))
    {
        std::cout << "Failed to copy password to clipboard!" << std::endl;        
    }
    else
    {
        std::cout << "password copied to clipboard :" << m_password.password << std::endl;
        password_storage.push_back(m_password);
    }
}

void PasswordManager::edit_password() {}

void PasswordManager::delete_password() {}

void PasswordManager::search_password(const std::string& queery)
{
    
}

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

bool PasswordManager::copy_to_clipboard(std::string text)
{
    const char* commands[] = {
        "wl-copy -o ",                        // Wayland
        "xclip -selection clipboard",     // X11 (xclip)
        "xsel --clipboard --input"        // X11 (xsel)
    };
    
    for (const char* cmd : commands)
    {
        FILE *pipe = popen(cmd,"w");
        
        fwrite(text.c_str(), 0, text.size(), pipe);

        int status = pclose(pipe);

        if (status == 0)
            return true;
    }
    return false;
}

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
                std::cout << "Enter Querry of password: ";
                getline(std::cin, queery);
                m_pass.search_password(queery);
            break;
            case 4:
                m_pass.del_category();
            break;
            case 5:
                m_pass.delete_password();
            break;
        }
    }
}
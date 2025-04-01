#include <iostream>
#include "4F.h"

int main()
{
    int mainChoice;
    int subChoice;
    std::string input;

    do
    {
        std::cout << "Select an option:\n";
        std::cout << "1. Encrypt\n";
        std::cout << "2. Decrypt\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> mainChoice;
        std::cin.ignore();

        if (mainChoice == 1)
        {
            std::cout << "You have chosen to encrypt.\n";
            std::cout << "Select a cipher:\n";
            std::cout << "1. 4F\n";
            std::cout << "2. Back\n";
            std::cout << "Your choice: ";
            std::cin >> subChoice;
            std::cin.ignore();

            if (subChoice == 1)
            {
                std::cout << "Enter a string to encrypt: ";
                std::getline(std::cin, input);

                std::string encryptedOutput = FourF::encryptWithSuffix(input);
                std::cout << "Encrypted result: " << encryptedOutput << std::endl;
            }
        }
        else if (mainChoice == 2)
        {
            std::cout << "You have chosen to decrypt.\n";
            std::cout << "Select a cipher:\n";
            std::cout << "1. 4F\n";
            std::cout << "2. Back\n";
            std::cout << "Your choice: ";
            std::cin >> subChoice;
            std::cin.ignore();

            if (subChoice == 1)
            {
                std::cout << "Enter a string to decrypt: ";
                std::getline(std::cin, input);

                std::string decryptedOutput = FourF::decrypt(input);
                std::cout << "Decrypted result: " << decryptedOutput << std::endl;
            }
        }
    }
    while (mainChoice != 0);

    return 0;
}
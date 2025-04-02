#include <iostream>
#include "4F.h"

int main()
{
    int mainChoice;
    int cipherChoice;
    std::string input;

    do
    {
        std::cout << "Select an option:\n"
                  << "1. Encrypt\n"
                  << "0. Exit\n"
                  << "Your choice: ";
        std::cin >> mainChoice;
        std::cin.ignore();

        if (mainChoice == 1)
        {
            std::cout << "You have chosen to encrypt.\n"
                      << "Select a cipher:\n"
                      << "1. 4F\n"
                      << "2. Back\n"
                      << "Your choice: ";
            std::cin >> cipherChoice;
            std::cin.ignore();

            if (cipherChoice == 1)
            {
                std::cout << "Enter a string to encrypt: ";
                std::getline(std::cin, input);

                char verboseChoice;
                std::cout << "Verbose mode? (y/n): ";
                std::cin >> verboseChoice;
                bool verbose = (verboseChoice == 'y' || verboseChoice == 'Y');

                try
                {
                    std::string encryptedOutput = FourF::encryptWithSuffix(input, verbose);
                    std::cout << "Encrypted result: " << encryptedOutput << "\n";
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
        }
    }
    while (mainChoice != 0);

    return 0;
}
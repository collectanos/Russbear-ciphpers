#include <iostream>
#include "4F.h"

int main() 
{
    int choice;
    std::string input;

    do 
    {
        std::cout << "Select an encryption method:\n";
        std::cout << "1. 4F Encryption\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) 
        {
            std::cout << "Enter a string: ";
            std::getline(std::cin, input);

            std::string binaryOutput = FourF::stringToBinary(input);
            std::string encryptedOutput = FourF::encrypt(binaryOutput);

            std::cout << "Encrypted result: " << encryptedOutput << std::endl;
        }
    } while (choice != 0);

    return 0;
}
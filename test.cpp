#include <iostream>
#include "4F.h"

int main() {
    int choice;
    std::string binaryInput;

    do {
        std::cout << "Select an encryption method:\n";
        std::cout << "1. 4F Encryption\n";
        std::cout << "0. Exit\n";
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter a binary string: ";
            std::cin >> binaryInput;

            std::string encryptedOutput = FourF::encrypt(binaryInput);
            std::cout << "Encrypted result: " << encryptedOutput << std::endl;
        }
    } while (choice != 0);

    return 0;
}
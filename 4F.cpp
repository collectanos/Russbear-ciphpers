#include "4F.h"
#include <unordered_map>
#include <cctype>

std::string FourF::stringToBinary(const std::string& input) 
{
    std::string binaryString;
    for (char c : input) 
    {
        for (int i = 7; i >= 0; --i) 
        {
            binaryString += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return binaryString;
}

std::string FourF::encryptWithSuffix(const std::string& input) 
{
    std::unordered_map<std::string, char> mapping = 
    {
        {"0000", '0'},
        {"0001", '1'},
        {"0010", '2'},
        {"0011", '3'},
        {"0100", '4'},
        {"0101", '5'},
        {"0110", '6'},
        {"0111", '7'},
        {"1000", '8'},
        {"1001", '9'},
        {"1010", 'A'},
        {"1011", 'B'},
        {"1100", 'C'},
        {"1101", 'D'},
        {"1110", 'E'},
        {"1111", 'F'}
    };

    std::string binaryString = stringToBinary(input);
    std::string paddedBinary = binaryString;

    while (paddedBinary.length() % 4 != 0) 
    {
        paddedBinary = '0' + paddedBinary;
    }

    std::string result;

    for (size_t i = 0; i < paddedBinary.length(); i += 4) 
    {
        std::string fourBits = paddedBinary.substr(i, 4);
        result += mapping[fourBits];
    }

    int letterCount = 0;
    int digitCount = 0;

    for (char c : input) 
    {
        if (std::isalpha(c)) 
        {
            letterCount++;
        } 
        else if (std::isdigit(c)) 
        {
            digitCount++;
        }
    }

    if (letterCount > digitCount) 
    {
        result += "++";
    } 
    else if (digitCount > letterCount) 
    {
        result += "--";
    } 
    else 
    {
        result += "+-";
    }

    return result;
}
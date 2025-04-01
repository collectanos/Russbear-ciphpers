#include "4F.h"
#include <unordered_map>
#include <cctype>
#include <bitset>
#include <algorithm>
#include <cmath>

std::string FourF::stringToBinary(const std::string& input)
{
    std::string binaryString;
    for (unsigned char c : input)
    {
        binaryString += std::bitset<8>(c).to_string();
    }
    return binaryString;
}

std::string FourF::binaryToString(const std::string& binary)
{
    std::string result;
    for (size_t i = 0; i < binary.length(); i += 8)
    {
        std::string byte = binary.substr(i, 8);
        char c = static_cast<char>(std::bitset<8>(byte).to_ulong());
        result += c;
    }
    return result;
}

std::string FourF::hexToBase36(const std::string& hex)
{
    unsigned long long decimal = 0;
    for (char c : hex)
    {
        decimal = decimal * 16 + (std::isdigit(c) ? (c - '0') : (std::toupper(c) - 'A' + 10));
    }

    const std::string base36Chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string base36;
    if (decimal == 0)
    {
        return "0";
    }
    while (decimal > 0)
    {
        base36 = base36Chars[decimal % 36] + base36;
        decimal /= 36;
    }
    return base36;
}

std::string FourF::base36ToHex(const std::string& base36)
{
    const std::string base36Chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned long long decimal = 0;
    for (char c : base36)
    {
        size_t index = base36Chars.find(std::toupper(c));
        decimal = decimal * 36 + index;
    }

    std::string hex;
    if (decimal == 0)
    {
        return "0";
    }
    while (decimal > 0)
    {
        int remainder = decimal % 16;
        char hexChar = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
        hex = std::string(1, hexChar) + hex;
        decimal /= 16;
    }
    return hex;
}

std::string FourF::encryptWithSuffix(const std::string& input)
{
    // Step 1: Convert input to binary
    std::string binaryString = stringToBinary(input);

    // Step 2: Pad binary string to make its length divisible by 4
    while (binaryString.length() % 4 != 0)
    {
        binaryString = '0' + binaryString;
    }

    // Step 3: Convert binary to hexadecimal
    std::string hexResult;
    for (size_t i = 0; i < binaryString.length(); i += 4)
    {
        std::string fourBits = binaryString.substr(i, 4);
        unsigned long value = std::bitset<4>(fourBits).to_ulong();
        char hexChar = (value < 10) ? ('0' + value) : ('A' + value - 10);
        hexResult += hexChar;
    }

    // Step 4: Compress hexadecimal to base-36
    std::string compressedResult = hexToBase36(hexResult);

    // Step 5: Add suffix based on letter/digit analysis
    int letterCount = 0;
    int digitCount = 0;

    for (char c : input)
    {
        if (std::isalpha(c))
        {
            ++letterCount;
        }
        else if (std::isdigit(c))
        {
            ++digitCount;
        }
    }

    std::string suffix;
    if (letterCount > digitCount)
    {
        suffix = "++";
    }
    else if (digitCount > letterCount)
    {
        suffix = "--";
    }
    else
    {
        suffix = "+-";
    }

    return compressedResult + suffix;
}

std::string FourF::decrypt(const std::string& input)
{
    // Step 1: Separate base-36 input and suffix
    std::string base36Input = input.substr(0, input.length() - 2);

    // Step 2: Convert base-36 back to hexadecimal
    std::string hexInput = base36ToHex(base36Input);

    // Step 3: Convert hexadecimal to binary
    std::string binaryString;
    for (char c : hexInput)
    {
        int value = std::isdigit(c) ? (c - '0') : (std::toupper(c) - 'A' + 10);
        binaryString += std::bitset<4>(value).to_string();
    }

    // Step 4: Convert binary back to original text
    std::string result = binaryToString(binaryString);

    return result;
}
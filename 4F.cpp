#include "4F.h"
#include <unordered_map>
#include <cctype>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <iostream>

std::string FourF::stringToBinary(const std::string& input)
{
    std::string binaryString;
    for (unsigned char c : input)
    {
        if (c > 127)
        {
            throw std::invalid_argument("Input contains non-ASCII characters.");
        }
        binaryString += std::bitset<8>(c).to_string();
    }
    std::cout << "Binary: " << binaryString << std::endl;
    return binaryString;
}

std::string FourF::binaryToString(const std::string& binary)
{
    std::string result;
    std::string mutableBinary = binary;
    size_t length = mutableBinary.length();

    while (length % 8 != 0)
    {
        mutableBinary = mutableBinary.substr(1);
        --length;
    }

    for (size_t i = 0; i < length; i += 8)
    {
        std::string byte = mutableBinary.substr(i, 8);
        char c = static_cast<char>(std::bitset<8>(byte).to_ulong());
        result += c;
    }
    std::cout << "Decoded Text: " << result << std::endl;
    return result;
}

std::string FourF::hexToBase36(const std::string& hex)
{
    const std::string base36Chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string base36Result;

    for (size_t i = 0; i < hex.length(); i += 4)
    {
        std::string chunk = hex.substr(i, 4);
        unsigned long long decimal = 0;

        for (char c : chunk)
        {
            decimal = decimal * 16 + (std::isdigit(c) ? (c - '0') : (std::toupper(c) - 'A' + 10));
        }

        std::string base36Chunk;
        if (decimal == 0)
        {
            base36Chunk = "0";
        }
        else
        {
            while (decimal > 0)
            {
                base36Chunk = base36Chars[decimal % 36] + base36Chunk;
                decimal /= 36;
            }
        }

        base36Result += base36Chunk;
    }
    std::cout << "Base36: " << base36Result << std::endl;
    return base36Result;
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
    while (hex.length() % 2 != 0)
    {
        hex = "0" + hex;
    }
    std::cout << "Hex from Base36: " << hex << std::endl;
    return hex;
}

std::string FourF::encryptWithSuffix(const std::string& input)
{
    std::string binaryString = stringToBinary(input);
    size_t originalLength = binaryString.length();

    while (binaryString.length() % 4 != 0)
    {
        binaryString += '+';
    }

    std::string hexResult;
    for (size_t i = 0; i < binaryString.length(); i += 4)
    {
        std::string fourBits = binaryString.substr(i, 4);
        unsigned long value = 0;

        if (fourBits.find_first_not_of("01") == std::string::npos)
        {
            value = std::bitset<4>(fourBits).to_ulong();
        }
        else
        {
            value = 0;
        }

        char hexChar = (value < 10) ? ('0' + value) : ('A' + value - 10);
        hexResult += hexChar;
    }
    std::cout << "Hex: " << hexResult << std::endl;

    std::string compressedResult = hexToBase36(hexResult);

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

    while ((compressedResult.length() + suffix.length()) % 4 != 0)
    {
        suffix += '=';
    }
    std::cout << "Suffix: " << suffix << std::endl;

    return compressedResult + suffix + "|" + std::to_string(originalLength);
}

std::string FourF::decrypt(const std::string& input)
{
    size_t delimiterPos = input.find('|');
    if (delimiterPos == std::string::npos)
    {
        throw std::invalid_argument("Invalid encrypted format: missing length delimiter.");
    }

    std::string base36Input = input.substr(0, delimiterPos);
    std::string lengthStr = input.substr(delimiterPos + 1);
    size_t originalLength = std::stoi(lengthStr);

    size_t suffixStart = base36Input.length() - 2;
    std::string suffix = base36Input.substr(suffixStart);
    suffix.erase(std::remove(suffix.begin(), suffix.end(), '='), suffix.end());

    std::string hexInput = base36ToHex(base36Input);

    std::string binaryString;
    for (size_t i = 0; i < hexInput.length(); i += 2)
    {
        std::string twoChars = hexInput.substr(i, 2);
        unsigned long value = 0;

        for (char c : twoChars)
        {
            value = value * 16 + (std::isdigit(c) ? (c - '0') : (std::toupper(c) - 'A' + 10));
        }

        binaryString += std::bitset<8>(value).to_string();
    }
    std::cout << "Binary from Hex: " << binaryString << std::endl;

    binaryString = binaryString.substr(0, originalLength);

    std::string result = binaryToString(binaryString);

    return result;
}

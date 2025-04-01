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
    return hex;
}

std::string FourF::encryptWithSuffix(const std::string& input)
{
    std::string binaryString = stringToBinary(input);

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

    return compressedResult + suffix;
}

std::string FourF::decrypt(const std::string& input)
{
    size_t suffixStart = input.length() - 2;
    std::string base36Input = input.substr(0, suffixStart);
    std::string suffix = input.substr(suffixStart);

    suffix.erase(std::remove(suffix.begin(), suffix.end(), '='), suffix.end());

    std::string hexInput = base36ToHex(base36Input);

    std::string binaryString;
    for (char c : hexInput)
    {
        int value = std::isdigit(c) ? (c - '0') : (std::toupper(c) - 'A' + 10);
        binaryString += std::bitset<4>(value).to_string();
    }

    while (!binaryString.empty() && (binaryString.back() == '+' || binaryString.back() == '-'))
    {
        binaryString.pop_back();
    }

    std::string result = binaryToString(binaryString);

    return result;
}

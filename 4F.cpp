#include "4F.h"
#include <bitset>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

std::string FourF::stringToBinary(const std::string& input, bool verbose)
{
    std::string binaryString;
    for (unsigned char c : input)
    {
        binaryString += std::bitset<8>(c).to_string();
    }
    if (verbose) std::cout << "Binary: " << binaryString << std::endl;
    return binaryString;
}

std::string FourF::hexToBase36(const std::string& hex, bool verbose)
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
    if (verbose) std::cout << "Base36: " << base36Result << std::endl;
    return base36Result;
}

std::string FourF::compressBase36(const std::string& base36, bool verbose)
{
    std::string compressedResult;
    size_t i = 0;

    while (i < base36.length())
    {
        size_t groupSize = (i + 3 <= base36.length()) ? 3 : (i + 2 <= base36.length()) ? 2 : 1;
        std::string group = base36.substr(i, groupSize);

        unsigned long long decimalValue = 0;
        for (char c : group)
        {
            decimalValue = decimalValue * 36 + (std::isdigit(c) ? (c - '0') : (std::toupper(c) - 'A' + 10));
        }

        decimalValue /= 4;
        compressedResult += static_cast<char>(decimalValue % 256);

        i += groupSize;
    }

    if (verbose) std::cout << "Compressed Result: " << compressedResult << std::endl;
    return compressedResult;
}

std::string FourF::encryptWithSuffix(const std::string& input, bool verbose)
{
    std::string binaryString = stringToBinary(input, verbose);

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
    if (verbose) std::cout << "Hex: " << hexResult << std::endl;

    std::string base36Result = hexToBase36(hexResult, verbose);
    std::string compressedResult = compressBase36(base36Result, verbose);

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

    if (verbose) std::cout << "Suffix: " << suffix << std::endl;

    return compressedResult + suffix;
}
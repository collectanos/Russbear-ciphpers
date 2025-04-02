#ifndef FOURF_H
#define FOURF_H

#include <string>

class FourF
{
public:
    static std::string encryptWithSuffix(const std::string& input, bool verbose);
private:
    static std::string stringToBinary(const std::string& input, bool verbose);
    static std::string hexToBase35(const std::string& hex, bool verbose);
};

#endifФС
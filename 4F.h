#ifndef _4F_H_
#define _4F_H_

#include <string>

class FourF 
{
public:
    static std::string stringToBinary(const std::string& input);
    static std::string encrypt(const std::string& binaryString);
};

#endif
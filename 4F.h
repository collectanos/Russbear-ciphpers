#ifndef _4F_H_
#define _4F_H_

#include <string>

class FourF
{
public:
    static std::string stringToBinary(const std::string& input);
    static std::string binaryToString(const std::string& binary);
    static std::string encryptWithSuffix(const std::string& input);
    static std::string decrypt(const std::string& input);
};

#endif
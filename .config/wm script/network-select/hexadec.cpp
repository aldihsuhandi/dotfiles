#ifndef _IOSTREAM_
#include <iostream>
#define _IOSTREAM_
#endif

#ifndef _SSTREAM_
#include <sstream>
#define _SSTREAM_
#endif

#ifndef _IOMANIP_
#include <iomanip>
#define _IOMANIP_
#endif

class HexaUtil
{
public:
    static std::string string_to_hex(std::string str)
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        for (const auto &it : str)
        {
            ss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(it));
        }

        return ss.str();
    }

    static std::string hex_to_string(std::string hex_string)
    {
        std::string result = "";
        for (int i = 0; i < (int)hex_string.length(); i += 2)
        {
            std::string byte_str = hex_string.substr(i, 2);
            char chr = static_cast<char>(std::stoi(byte_str, nullptr, 16));
            result.push_back(chr);
        }

        return result;
    }
};

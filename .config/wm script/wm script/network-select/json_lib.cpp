#ifndef _IOSTREAM_
#include <iostream>
#define _IOSTREAM_
#endif

#ifndef _STRING_
#include <string>
#define _STRING_
#endif

#ifndef _VECTOR_
#include <vector>
#define _VECTOR_
#endif

#ifndef _SSTREAM_
#include <sstream>
#define _SSTREAM_
#endif

#ifndef _MAP_
#include <map>
#define _MAP_
#endif

class JsonUtil
{
private:
    static std::string trim(const std::string &str)
    {
        const std::string whitespace = " \t\n\r\f\v";
        int start = (int)str.find_first_not_of(whitespace);
        int end = (int)str.find_last_not_of(whitespace);

        if (start == std::string::npos || end == std::string::npos)
        {
            return "";
        }
        return str.substr(start, end - start + 1);
    }

    static std::string remove_quotes(const std::string &str)
    {
        if (str.front() == '"' && str.back() == '"')
        {
            return str.substr(1, str.size() - 2);
        }
        return str;
    }

public:
    static std::map<std::string, std::string> parse_json_to_map(const std::string &json_str)
    {
        std::map<std::string, std::string> json_map;

        std::string content = json_str.substr(1, json_str.size() - 2);

        std::stringstream ss(content);
        std::string item;

        while (std::getline(ss, item, ','))
        {
            int delimiter_pos = (int)item.find(':');
            std::string key = trim(item.substr(0, delimiter_pos));
            std::string value = trim(item.substr(delimiter_pos + 1));

            key = remove_quotes(key);
            value = remove_quotes(value);

            json_map[key] = value;
        }

        return json_map;
    }
};
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace utils::string
{
    // Trim whitespace from left
    inline std::string TrimLeft(const std::string& str)
    {
        const auto it = std::find_if(str.begin(), str.end(), [](const unsigned char ch)
        {
            return !std::isspace(ch);
        });

        return {it, str.end()};
    }

    // Trim whitespace from right
    inline std::string TrimRight(const std::string& str)
    {
        const auto it = std::find_if(str.rbegin(), str.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base();

        return {str.begin(), it};
    }

    // Trim whitespace from both sides
    inline std::string Trim(const std::string& str)
    {
        return TrimLeft(TrimRight(str));
    }

    // Convert to lowercase
    inline std::string ToLower(const std::string& str)
    {
        std::string result = str;

        std::transform(result.begin(), result.end(), result.begin(), [](const unsigned char c)
        {
            return std::tolower(c);
        });

        return result;
    }

    // Convert to uppercase
    inline std::string ToUpper(const std::string& str)
    {
        std::string result = str;

        std::transform(result.begin(), result.end(), result.begin(), [](const unsigned char c)
        {
            return std::toupper(c);
        });

        return result;
    }

    // Split string by delimiter
    inline std::vector<std::string> Split(const std::string& str, const char delimiter)
    {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter))
        {
            tokens.push_back(token);
        }

        return tokens;
    }

    // Join strings with a delimiter
    inline std::string Join(const std::vector<std::string>& strings, const std::string& delimiter)
    {
        if (strings.empty()) return "";

        std::string result = strings[0];

        for (size_t i = 1; i < strings.size(); ++i)
        {
            result += delimiter + strings[i];
        }

        return result;
    }

    // Check if string starts with prefix
    inline bool StartsWith(const std::string& str, const std::string& prefix)
    {
        return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
    }

    // Check if string ends with suffix
    inline bool EndsWith(const std::string& str, const std::string& suffix)
    {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    // Replace all occurrences of substring
    inline std::string ReplaceAll(std::string str, const std::string& from, const std::string& to)
    {
        size_t pos = 0;

        while ((pos = str.find(from, pos)) != std::string::npos)
        {
            str.replace(pos, from.length(), to);

            pos += to.length();
        }

        return str;
    }

    // Check if string contains substring
    inline bool Contains(const std::string& str, const std::string& substr)
    {
        return str.find(substr) != std::string::npos;
    }
}

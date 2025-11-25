#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace utils::file
{
    // Read the entire file into string
    inline std::string ReadFile(const std::string& filepath)
    {
        std::ifstream file(filepath);

        if (!file.is_open())
        {
            return "";
        }

        std::stringstream buffer;

        buffer << file.rdbuf();

        return buffer.str();
    }

    // Read file lines into a vector
    inline std::vector<std::string> ReadLines(const std::string& filepath)
    {
        std::vector<std::string> lines;
        std::ifstream file(filepath);

        if (!file.is_open())
        {
            return lines;
        }

        std::string line;

        while (std::getline(file, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    // Write string to file
    inline bool WriteFile(const std::string& filepath, const std::string& content)
    {
        std::ofstream file(filepath);

        if (!file.is_open())
        {
            return false;
        }

        file << content;

        return true;
    }

    // Check if a file exists
    inline bool FileExists(const std::string& filepath)
    {
        const std::ifstream file(filepath);

        return file.good();
    }

    // Get file extension
    inline std::string GetExtension(const std::string& filepath)
    {
        const size_t dotPos = filepath.find_last_of('.');

        if (dotPos == std::string::npos)
        {
            return "";
        }

        return filepath.substr(dotPos + 1);
    }

    // Get filename without extension
    inline std::string GetFilenameWithoutExtension(const std::string& filepath)
    {
        const size_t lastSlash = filepath.find_last_of("/\\");
        const size_t start = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

        const size_t dotPos = filepath.find_last_of('.');
        const size_t end = (dotPos == std::string::npos) ? filepath.length() : dotPos;

        if (end <= start) return "";

        return filepath.substr(start, end - start);
    }

    // Get directory from a path
    inline std::string GetDirectory(const std::string& filepath)
    {
        const size_t lastSlash = filepath.find_last_of("/\\");

        if (lastSlash == std::string::npos)
        {
            return "";
        }

        return filepath.substr(0, lastSlash);
    }
}

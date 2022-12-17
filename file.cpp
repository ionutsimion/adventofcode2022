#include <filesystem>
#include <iostream>

#include "file.hpp"

std::optional<std::ifstream> file::open(std::string &&file_path)
{
    auto input_path = std::filesystem::current_path() / file_path;
    std::ifstream input_stream{ input_path };
    if (!input_stream.is_open())
    {
        std::cout << "File not found: " << input_path.c_str() << std::endl;
        return {};
    }

    return input_stream;
}

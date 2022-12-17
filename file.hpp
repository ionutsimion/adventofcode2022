#pragma once

#include <fstream>
#include <optional>

namespace file
{
    std::optional<std::ifstream> open(std::string &&file_path);
}

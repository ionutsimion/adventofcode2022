#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>

using namespace std::literals;

namespace aoc
{
    void day01_calorie_counting()
    {
        std::filesystem::path input_path{ "../day01-calories.txt" };
        std::ifstream input_stream{ input_path };
        if (!input_stream.is_open())
            std::cout << "File not found: " << input_path.c_str() << std::endl;

        std::map<std::uint32_t, std::uint64_t> elf_calories{};
        std::uint32_t elf_id{ 0 };
        for (std::string line; std::getline(input_stream, line);)
        {
            elf_id += line.empty();
            try
            {
                elf_calories[elf_id] += std::stoull(line);
            }
            catch (...) {};
        }

        std::array<std::uint64_t, 3uz> top_three{};
        for (auto const &[id, calories] : elf_calories)
        {
            std::cout << "Elf " << id << " carries " << calories << " calories" << std::endl;
            auto *min = std::min_element(top_three.begin(), top_three.end());
            *min = std::max(*min, calories);
        }

        std::cout << "Part 1) Maximum calories: " << std::ranges::max(top_three) << std::endl;
        std::cout << "Part 2) Top three calories: " << std::reduce(top_three.cbegin(), top_three.cend()) << std::endl;
    }
}

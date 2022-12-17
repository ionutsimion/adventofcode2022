#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>

#include "file.hpp"

using namespace std::literals;

namespace aoc
{
    void day01_calorie_counting()
    {
        auto input_stream = file::open("data/day01-calories.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 1:" << std::endl;

        std::map<std::uint32_t, std::uint64_t> elf_calories{};
        std::uint32_t elf_id{ 0 };
        for (std::string line; std::getline(*input_stream, line);)
        {
            if (line.empty())
                ++elf_id;
            else
                elf_calories[elf_id] += std::stoull(line);
        }

        std::array<std::uint64_t, 3uz> top_three{};
        for (auto const &[id, calories] : elf_calories)
        {
            auto *min = std::min_element(top_three.begin(), top_three.end());
            *min = std::max(*min, calories);
        }

        std::cout << "\tPart 1) Maximum calories carried by an elf: " << std::ranges::max(top_three) << std::endl;
        std::cout << "\tPart 2) Total calories carried by the top three elves: " << std::reduce(top_three.cbegin(), top_three.cend()) << std::endl;
    }
}

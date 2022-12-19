#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <queue>

#include "file.hpp"

namespace
{
    size_t priority(char c);
    std::string intersect(std::string &&lhs, std::string &&rhs);
    std::string intersect(std::string &&first, std::string &&second, std::string &&third);
}

namespace aoc
{
    void day03_rucksack_organization()
    {
        auto input_stream = file::open("data/day03-rucksack-organization.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 3:" << std::endl;

        size_t sum_of_priorities{};
        size_t sum_of_badge_priorities{};
        try
        {
            std::vector<std::string> elf_group{};
            for (std::string line; std::getline(*input_stream, line);)
            {
                sum_of_priorities += priority(intersect(line.substr(0, line.size() / 2), line.substr(line.size() / 2)).at(0));
                elf_group.push_back(line);
                if (elf_group.size() == 3)
                {
                    sum_of_badge_priorities += priority(intersect(std::move(elf_group.at(0)), std::move(elf_group.at(1)), std::move(elf_group.at(2))).at(0));
                    elf_group.clear();
                }
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) The sum of misplaced item priorities is: " << sum_of_priorities << std::endl;
        std::cout << "\tPart 1) The sum of elf group badge priorities is: " << sum_of_badge_priorities << std::endl;
    }
}

namespace
{
    size_t priority(char const c)
    {
        if (!std::isalpha(static_cast<int>(c)))
            return 0;

        if (std::islower(static_cast<int>(c)))
            return static_cast<size_t>(c - 'a') + 1u;

        return static_cast<size_t>(c - 'A') + 27u;
    }

    std::string intersect(std::string &&lhs, std::string &&rhs)
    {
        std::string intersection{};
        std::ranges::sort(lhs);
        std::ranges::sort(rhs);
        std::ranges::set_intersection(lhs, rhs, std::back_inserter(intersection));
        return intersection;
    }

    std::string intersect(std::string &&first, std::string &&second, std::string &&third)
    {
        return intersect(std::move(first), intersect(std::move(second), std::move(third)));
    }
}

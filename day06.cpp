#include <algorithm>
#include <iostream>
#include <string>

#include "file.hpp"

namespace aoc
{
    void day06_tuning_trouble()
    {
        auto input_stream = file::open("data/day06-tuning-trouble.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 6:" << std::endl;

        size_t number_of_processed_characters{};
        try
        {
            std::string line;
            std::getline(*input_stream, line);
            for (auto from = line.begin(), up_to = std::next(from, 4); up_to != line.end(); from = std::next(from), up_to = std::next(up_to))
            {
                std::string group(from, up_to);
                std::ranges::sort(group);
                if (auto [one_past_last_unique, one_past_last] = std::ranges::unique(group); one_past_last_unique == one_past_last)
                {
                    number_of_processed_characters = std::distance(line.begin(), up_to);
                    break;
                }
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) There were " << number_of_processed_characters << " processed characters" << std::endl;
        std::cout << "\tPart 2)" << std::endl;
    }
}

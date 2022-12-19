#include <iostream>
#include <sstream>
#include <string>

#include "file.hpp"

namespace aoc
{
    void day04_camp_cleanup()
    {
        auto input_stream = file::open("data/day04-camp-cleanup.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 4:" << std::endl;

        size_t number_of_overlapping_pairs{};
        size_t number_of_partly_overlapping_pairs{};
        try
        {
            for (std::string line; std::getline(*input_stream, line);)
            {
                std::stringstream ss{ line };
                int elf1_from, elf1_to, elf2_from, elf2_to;
                [[maybe_unused]] char _;
                ss >> elf1_from >> _ >> elf1_to >> _ >> elf2_from >> _ >> elf2_to;
                number_of_overlapping_pairs += (elf1_from >= elf2_from && elf1_to <= elf2_to) || (elf1_from <= elf2_from && elf1_to >= elf2_to);
                number_of_partly_overlapping_pairs += std::max(elf1_from, elf2_from) <= std::min(elf1_to, elf2_to);
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) There are " << number_of_overlapping_pairs << " overlapping pairs" << std::endl;
        std::cout << "\tPart 2) There are " << number_of_partly_overlapping_pairs << " pairs that partly overlap" << std::endl;
    }
}

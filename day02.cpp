#include <iostream>

#include "file.hpp"

namespace aoc
{
    void day02_rock_paper_scissors_strategy()
    {
        auto input_stream = file::open("data/day02-rps-strategy.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 2:" << std::endl;
    }
};

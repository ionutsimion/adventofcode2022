#include <iostream>
#include <map>

#include "file.hpp"

namespace
{
    auto evaluate_my_score(char const opponent_shape, char const my_shape)
    {
        switch (opponent_shape)
        {
        case 'A': return (my_shape == 'X') * 3uz + (my_shape == 'Y') * 6uz;
        case 'B': return (my_shape == 'Y') * 3uz + (my_shape == 'Z') * 6uz;
        case 'C': return (my_shape == 'Z') * 3uz + (my_shape == 'X') * 6uz;
        default: return 0uz;
        }
    }
}

namespace aoc
{
    void day02_rock_paper_scissors_strategy()
    {
        auto input_stream = file::open("data/day02-rps-strategy.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 2:" << std::endl;

        std::map<char, size_t> const shape_points{
            { 'X', 1uz }
          , { 'Y', 2uz }
          , { 'Z', 3uz }
        };

        size_t score{};
        try
        {
            for (std::string line; std::getline(*input_stream, line);)
            {
                auto const opponent_shape = line.at(0);
                auto const my_shape = line.at(2);
                score += shape_points.at(my_shape) + evaluate_my_score(opponent_shape, my_shape);
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) I will have " << score << " points" << std::endl;
    }
}

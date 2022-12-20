#include <algorithm>
#include <iostream>
#include <string>

#include "file.hpp"

namespace
{
    bool is_sequence_unique(std::string::const_iterator const &from, long long const sequence_length)
    {
        std::string sequence(from, from + sequence_length);
        std::ranges::sort(sequence);
        if (auto [one_past_last_unique, one_past_last] = std::ranges::unique(sequence); one_past_last_unique == one_past_last)
            return true;

        return false;
    }
}

namespace aoc
{
    void day06_tuning_trouble()
    {
        auto input_stream = file::open("data/day06-tuning-trouble.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 6:" << std::endl;

        size_t number_of_processed_characters_for_marker{};
        size_t number_of_processed_characters_for_message{};
        try
        {
            std::string line;
            std::getline(*input_stream, line);
            for (auto from = line.cbegin(); std::next(from, 4ll) != line.cend(); ++from)
                if (is_sequence_unique(from, 4ll))
                {
                    number_of_processed_characters_for_marker = std::distance(line.cbegin(), from) + 4ll;
                    break;
                }
            for (auto from = line.cbegin(); std::next(from, 14ll) != line.cend(); ++from)
                if (is_sequence_unique(from, 14ll))
                {
                    number_of_processed_characters_for_message = std::distance(line.cbegin(), from) + 14ll;
                    break;
                }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) There were " << number_of_processed_characters_for_marker << " processed characters until the first marker was found" << std::endl;
        std::cout << "\tPart 2) There were " << number_of_processed_characters_for_message << " processed characters until the first message was found" << std::endl;
    }
}

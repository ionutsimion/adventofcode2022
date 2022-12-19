#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "file.hpp"

namespace
{
    template <typename T>
    void move(size_t number_of_moves, std::stack<T> &from, std::stack<T> &to)
    {
        for (; number_of_moves--;)
            to.push(from.top()), from.pop();
    }

    void move(size_t number_of_moves, std::string &from, std::string &to)
    {
        std::copy(from.end() - static_cast<long long>(number_of_moves), from.end(), std::back_inserter(to));
        from.erase(from.size() - static_cast<long long>(number_of_moves));
    }
}

namespace aoc
{
    void day05_supply_stacks()
    {
        auto input_stream = file::open("data/day05-supply-stacks.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 5:" << std::endl;

        std::string crate_sequence_9000{};
        std::string crate_sequence_9001{};
        try
        {
            std::stack<std::string> drawing{};
            for (std::string line; std::getline(*input_stream, line), !line.empty();)
                drawing.emplace(line);

            std::map<size_t, size_t> label_indices{};
            std::string labels_line = drawing.top();
            drawing.pop();
            std::stringstream labels_stream{ labels_line };
            for (int label; labels_stream >> label;)
                label_indices.emplace(label, labels_line.find(std::to_string(label)));

            std::map<size_t, std::stack<char>> stacks{};
            std::map<size_t, std::string> strings{};
            while (!drawing.empty())
            {
                auto line = drawing.top();
                drawing.pop();
                for (auto const [label, index] : label_indices)
                    if (auto const c = line.at(index); isalpha(static_cast<int>(c)))
                        stacks[label].emplace(c), strings[label] += c;
            }

            for (std::string line, _; std::getline(*input_stream, line);)
            {
                std::stringstream ss{ line };
                size_t number_of_crates, from_stack, to_stack;
                ss >> _ >> number_of_crates >> _ >> from_stack >> _ >> to_stack;
                move(number_of_crates, stacks.at(from_stack), stacks.at(to_stack));
                move(number_of_crates, strings.at(from_stack), strings.at(to_stack));
            }

            for (auto const &[label, stack] : stacks)
                crate_sequence_9000 += stack.top();
            for (auto const &[label, string] : strings)
                crate_sequence_9001 += string.back();
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) The crate sequence (using CrateMover 9000) is " << crate_sequence_9000 << std::endl;
        std::cout << "\tPart 2) The crate sequence (using CrateMover 9001) is " << crate_sequence_9001 << std::endl;
    }
}

#include <iostream>
#include <map>
#include <numeric>
#include <string>

#include "file.hpp"

namespace
{
    class strategy
    {
    public:
        [[nodiscard]] virtual size_t round_score(char column1, char column2) const = 0;

    protected:
        [[nodiscard]] virtual size_t shape_score(char shape_code) const = 0;
        [[nodiscard]] virtual size_t outcome_score(char column1, char column2) const = 0;
    };

    class second_column_is_shape
        : public strategy
    {
    public:
        [[nodiscard]] size_t round_score(char column1, char column2) const override;

    protected:
        [[nodiscard]] size_t shape_score(char shape_code) const override;
        [[nodiscard]] size_t outcome_score(char column1, char column2) const override;

    private:
        std::map<char, size_t> const shape_points{ { 'X', 1u }, { 'Y', 2u }, { 'Z', 3u } };
    };

    class second_column_is_outcome
        : public strategy
    {
    public:
        [[nodiscard]] size_t round_score(char column1, char column2) const override;

    protected:
        [[nodiscard]] size_t shape_score(char shape_code) const override;
        [[nodiscard]] size_t outcome_score(char column1, char column2) const override;

    private:
        std::map<char, size_t> const shape_points{ { 'A', 1u }, { 'B', 2u }, { 'C', 3u } };
        std::map<char, char> const shape_trumped_by{ { 'A', 'B' }, { 'B', 'C' }, { 'C', 'A' } };
        std::map<char, char> const shape_trumps{ { 'A', 'C' }, { 'B', 'A' }, { 'C', 'B' } };
    };
}

namespace aoc
{
    void day02_rock_paper_scissors_strategy()
    {
        auto input_stream = file::open("data/day02-rps-strategy.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 2:" << std::endl;

        second_column_is_shape second_column_is_shape_strategy{};
        second_column_is_outcome second_column_is_outcome_strategy{};
        size_t score_for_strategy_1{};
        size_t score_for_strategy_2{};
        try
        {
            for (std::string line; std::getline(*input_stream, line);)
            {
                auto const first_column = line.at(0);
                auto const second_column = line.at(2);
                score_for_strategy_1 += second_column_is_shape_strategy.round_score(first_column, second_column);
                score_for_strategy_2 += second_column_is_outcome_strategy.round_score(first_column, second_column);
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) I think I would have " << score_for_strategy_1 << " points" << std::endl;
        std::cout << "\tPart 2) I will actually have " << score_for_strategy_2<< " points" << std::endl;
    }
}

namespace
{
    size_t second_column_is_shape::round_score(char const column1, char const column2) const
    {
        return shape_score(column2) + outcome_score(column1, column2);
    }

    size_t second_column_is_shape::shape_score(char const shape_code) const
    {
        return shape_points.at(shape_code);
    }

    size_t second_column_is_shape::outcome_score(char const column1, char const column2) const
    {
        switch (column1)
        {
        case 'A': return (column2 == 'X') * 3u + (column2 == 'Y') * 6u;
        case 'B': return (column2 == 'Y') * 3u + (column2 == 'Z') * 6u;
        case 'C': return (column2 == 'Z') * 3u + (column2 == 'X') * 6u;
        default: return 0u;
        }
    }

    size_t second_column_is_outcome::round_score(char const column1, char const column2) const
    {
        char my_shape;
        switch (column2)
        {
        case 'X': my_shape = shape_trumps.at(column1); break;
        case 'Y': my_shape = column1; break;
        case 'Z': my_shape = shape_trumped_by.at(column1); break;
        default: my_shape = '\0'; break;
        }
        return shape_score(my_shape) + outcome_score(column1, my_shape);
    }

    size_t second_column_is_outcome::shape_score(char const shape_code) const
    {
        return shape_points.at(shape_code);
    }

    size_t second_column_is_outcome::outcome_score(char const column1, char const column2) const
    {
        return (shape_trumped_by.at(column1) == column2) * 6u + (column1 == column2) * 3u;
    }
}

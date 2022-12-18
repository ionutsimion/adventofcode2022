#include <iostream>
#include <map>

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
        std::map<char, size_t> const shape_points{ { 'X', 1uz }, { 'Y', 2uz }, { 'Z', 3uz } };
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
        std::map<char, size_t> const shape_points{ { 'A', 1uz }, { 'B', 2uz }, { 'C', 3uz } };
    };

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
                score += shape_points.at(second_column) + evaluate_my_score(first_column, second_column);
                score_for_strategy_1 += second_column_is_shape_strategy.round_score(first_column, second_column);
                score_for_strategy_2 += second_column_is_outcome_strategy.round_score(first_column, second_column);
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) I will have " << score << " points" << std::endl;
        std::cout << "\tscore 1: " << score_for_strategy_1 << std::endl;
        std::cout << "\tscore 2: " << score_for_strategy_2 << std::endl;
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
        return 0uz;
    }

    size_t second_column_is_outcome::round_score(char const column1, char const column2) const
    {
        return shape_score(column1) + outcome_score(column1, column2);
    }

    size_t second_column_is_outcome::shape_score(char const shape_code) const
    {
        return shape_points.at(shape_code);
    }

    size_t second_column_is_outcome::outcome_score(char const column1, char const column2) const
    {
        return 0uz;
    }
}

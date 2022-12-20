#include <algorithm>

namespace aoc
{
    extern void day01_calorie_counting();
    extern void day02_rock_paper_scissors_strategy();
    extern void day03_rucksack_organization();
    extern void day04_camp_cleanup();
    extern void day05_supply_stacks();
    extern void day06_tuning_trouble();
    extern void day07_no_space_left_on_device();
}

int main(int const number_of_arguments, char *arguments[])
{
    auto all_challenges = {
        aoc::day01_calorie_counting
      , aoc::day02_rock_paper_scissors_strategy
      , aoc::day03_rucksack_organization
      , aoc::day04_camp_cleanup
      , aoc::day05_supply_stacks
      , aoc::day06_tuning_trouble
      , aoc::day07_no_space_left_on_device
    };

    if (auto const run_last_challenge_only = number_of_arguments > 1 && strcmp(arguments[1], "last_only") == 0; run_last_challenge_only)
        std::invoke(*rbegin(all_challenges));
    else
        std::for_each(all_challenges.begin(), all_challenges.end(), [](auto const &f){ f(); });

    return 0;
}

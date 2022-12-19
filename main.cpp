#include <algorithm>

namespace aoc
{
    [[maybe_unused]] extern void day01_calorie_counting();
    [[maybe_unused]] extern void day02_rock_paper_scissors_strategy();
    [[maybe_unused]] extern void day03_rucksack_organization();
    [[maybe_unused]] extern void day04_camp_cleanup();
    [[maybe_unused]] extern void day05_supply_stacks();
}

int main(int const number_of_arguments, char *arguments[])
{
    auto all_challenges = {
        aoc::day01_calorie_counting
      , aoc::day02_rock_paper_scissors_strategy
      , aoc::day03_rucksack_organization
      , aoc::day04_camp_cleanup
      , aoc::day05_supply_stacks
    };

    if (auto const run_last_challenge_only = number_of_arguments > 1 && strcmp(arguments[1], "last_only") == 0; run_last_challenge_only)
        std::invoke(*rbegin(all_challenges));
    else
        std::for_each(all_challenges.begin(), all_challenges.end(), [](auto const &f){ f(); });

    return 0;
}

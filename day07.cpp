#include <iostream>
#include <string>

#include "file.hpp"

namespace
{
    enum class item_type
    {
        folder
      , file
    };

    class item
    {
    public:
        size_t size() const;

    private:
        std::unique_ptr<item> parent{};
        std::unique_ptr<item> children{};
        std::string name{};
        item_type type{};
    };

    class file_system
    {
        std::unique_ptr<item> root{};
    };
}

namespace aoc
{
    void day07_no_space_left_on_device()
    {
        auto input_stream = file::open("data/day07-no-space-left.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 7:" << std::endl;

        auto fs = std::make_unique<file_system>();
        try
        {
            for (std::string line; std::getline(*input_stream, line);)
            {
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1)" << std::endl;
        std::cout << "\tPart 2)" << std::endl;
    }
}

namespace
{
    size_t item::size() const
    {
        return 0ull;
    }
}

#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>
#include <sstream>

#include "file.hpp"

using namespace std::string_literals;

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
        item() = default;
        item(item &&) = default;
        item(item const &) = default;
        ~item() = default;

        item(std::shared_ptr<item> const &parent, std::string name, item_type const type)
        : parent_{ parent }
        , name_{ std::move(name) }
        , type_{ type }
        {
        }

        item(std::shared_ptr<item> const &parent, std::string name, size_t const size, item_type const type)
        : parent_{ parent }
        , name_{ std::move(name) }
        , type_{ type }
        , size_{ size }
        {
        }

        [[nodiscard]] auto const &name() const { return name_; }
        [[nodiscard]] auto &parent() const { return parent_; }

        [[nodiscard]] size_t size() const
        {
            if (type_ == item_type::file)
                return size_;

            return std::accumulate(children_.cbegin(), children_.cend(), 0ull,
                               [](size_t const sum, std::shared_ptr<item> const &child){ return sum + child->size(); });
        }

    private:
        friend class file_system;

        std::shared_ptr<item> parent_{};
        std::vector<std::shared_ptr<item>> children_{};
        std::string name_{};
        item_type type_{ item_type::folder };
        size_t size_{};
    };

    class file_system
    {
    public:
        void change_directory(std::string const &new_directory);
        void add_folder(std::string const &folder_name);
        void add_file(std::string const &file_name, size_t file_size);

        [[nodiscard]] size_t size() const
        {
            for (; cwt->parent(); cwt = cwt->parent());
            return cwt->size();
        }

    private:
        mutable std::shared_ptr<item> cwt = std::make_shared<item>(nullptr, "/"s, item_type::folder);
    };

    std::vector<std::string> split(std::string const &line);
    bool is_command(std::vector<std::string> const &tokens);
    bool is_cd(std::vector<std::string> const &tokens);
    bool is_folder(std::vector<std::string> const &tokens);
}

namespace aoc
{
    void day07_no_space_left_on_device()
    {
        auto input_stream = file::open("data/day07-no-space-left.txt");
        if (!input_stream.has_value())
            return;

        std::cout << "Day 7:" << std::endl;

        file_system fs{};
        try
        {
            for (std::string line; std::getline(*input_stream, line);)
            {
                auto tokens = split(line);
                if (is_command(tokens))
                {
                    if (is_cd(tokens))
                        fs.change_directory(tokens.back());
                }
                else if (is_folder(tokens))
                    fs.add_folder(tokens.back());
                else
                    fs.add_file(tokens.back(), std::stoull(tokens.front()));
            }
        }
        catch (std::exception const &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

        std::cout << "\tPart 1) Space occupied on device: " << fs.size() << std::endl;
        std::cout << "\tPart 2)" << std::endl;
    }
}

namespace
{
    void file_system::change_directory(std::string const &new_directory)
    {
        if (new_directory == "."s)
            return;

        if (new_directory == "/"s)
            for (; cwt->parent() != nullptr; cwt = cwt->parent());
        else if (new_directory == ".."s)
            cwt = cwt->parent();

        auto found = std::find_if(cwt->children_.cbegin(), cwt->children_.cend(),
                                  [&new_directory](std::shared_ptr<item> const &child){ return child->name() == new_directory; });
        if (found != cwt->children_.cend())
            cwt = *found;
    }

    void file_system::add_folder(std::string const &folder_name)
    {
        cwt->children_.push_back(std::make_shared<item>(cwt, folder_name, item_type::folder));
    }
    void file_system::add_file(std::string const &file_name, size_t file_size)
    {
        cwt->children_.push_back(std::make_shared<item>(cwt, file_name, file_size, item_type::file));
    }

    std::vector<std::string> split(std::string const &line)
    {
        std::vector<std::string> tokens;

        std::istringstream ss{ line };
        for (std::string token; ss >> token;)
            tokens.emplace_back(token);

        return tokens;
    }

    bool is_command(std::vector<std::string> const &tokens)
    {
        return tokens.front() == "$"s;
    }

    bool is_cd(std::vector<std::string> const &tokens)
    {
        return tokens.at(1ull) == "cd"s;
    }

    bool is_folder(std::vector<std::string> const &tokens)
    {
        return tokens.front() == "dir"s;
    }
}

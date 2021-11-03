#pragma once

#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <functional>
#include <numeric>

#include "../misc/vec2.h"

#define BOARD_INVALID_POS \
    vec2 { -1, -1 }

template <class Item, int BHeight, int BWidth>
class Board
{
public:
    using value_type = std::pair<vec2, Item>;

    using Iterator = typename std::array<value_type, BHeight * BWidth>::const_iterator;

    constexpr Board(Item default_item)
        : default_item(default_item)
    {
        auto gen_pair_indices = [&, i = 0]() mutable
        {
            int r = i / BWidth;
            int c = i % BWidth;
            i++;
            return std::make_pair(vec2{r, c}, default_item);
        };
        std::generate(buffer.begin(), buffer.end(), gen_pair_indices);
    }

    constexpr Iterator begin() const
    {
        return this->buffer.cbegin();
    }

    constexpr Iterator end() const
    {
        return this->buffer.cend();
    }

    constexpr Item get(vec2 v) const
    {
        return this->buffer[v.r * BWidth + v.c].second;
    }

    constexpr bool occupied(vec2 v) const
    {
        return !(this->get(v) == this->default_item);
    }

    constexpr void place(Item item, vec2 v)
    {
        this->buffer[v.r * BWidth + v.c].second = item;
    }

    constexpr Item take(vec2 v)
    {
        Item item = this->get(v);
        this->place(this->default_item, v);
        return item;
    }

    constexpr vec2 find(const Item &item) const
    {
        auto is_item = [&](const auto &pr)
        {
            return pr.second == item;
        };
        auto it = std::find_if(this->begin(), this->end(), is_item);
        if (it == this->end())
            return BOARD_INVALID_POS;
        return it->first;
    }

    // Needed for hashing.
    constexpr bool operator==(const Board &other) const
    {
        return this->buffer == other.buffer;
    }

    static constexpr inline int Height()
    {
        return BHeight;
    }

    static constexpr inline int Width()
    {
        return BWidth;
    }

    static constexpr inline bool in_bounds(vec2 v)
    {
        return v.r >= 0 && v.r < Height() && v.c >= 0 && v.c < Width();
    }

private:
    std::array<value_type, Height() * Width()> buffer;
    Item default_item;
};

namespace std
{
    template <class Item, int Width, int Height>
    struct hash<Board<Item, Width, Height>>
    {
        constexpr std::size_t operator()(const Board<Item, Height, Width> &b) const
        {
            auto acc = [](const std::size_t &a, const std::pair<vec2, Item> &b)
            {
                std::size_t h = std::hash<Item>()(b.second);
                return sal(a, 1) ^ h;
            };
            return std::accumulate(b.begin(), b.end(), std::size_t{0}, acc);
        }

    private:
        // shift arithmetic left
        static constexpr std::size_t sal(size_t s, unsigned int c)
        {
            const std::size_t mask = (CHAR_BIT * sizeof(s) - 1);
            c &= mask;
            return (s << c) | (s >> ((-c) & mask));
        }
    };
} // namespace std

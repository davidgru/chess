#pragma once

#include <cstddef>
#include <functional>

#include <array>
#include <algorithm>

#include <iostream>

#include <iterator>

#include "../misc/vec2.h"

#define BOARD_INVALID_POS \
    vec2 { -1, -1 }

template <class Item, int BHeight, int BWidth>
class Board
{
public:
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

    struct Iterator
    {

        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::size_t;
        using value_type = const std::pair<vec2, Item>;
        using pointer = value_type *;
        using reference = value_type &;

        constexpr Iterator(value_type *p) : p(p) {}

        constexpr value_type &operator*() const
        {
            return *p;
        };
        constexpr value_type *operator->()
        {
            return p;
        };

        constexpr Iterator &operator++()
        {
            p++;
            return *this;
        }

        constexpr Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr bool operator==(const Iterator &other) const
        {
            return this->p == other.p;
        }

        constexpr bool operator!=(const Iterator &other) const
        {
            return this->p != other.p;
        }

    private:
        value_type *p;
    };

    constexpr Iterator begin() const
    {
        return Iterator(&this->buffer[0]);
    }

    constexpr Iterator end() const
    {
        return Iterator(&this->buffer[BHeight * BWidth]);
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
        this->get_ref(v) = item;
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

    constexpr const std::pair<vec2, Item> &get_array_ref(vec2 v) const
    {
        return this->buffer[v.r * BWidth + v.c];
    }

    constexpr Item &get_ref(vec2 v)
    {
        return this->buffer[v.r * BWidth + v.c].second;
    }

private:
    std::array<std::pair<vec2, Item>, BHeight * BWidth> buffer;
    Item default_item;
};

namespace std
{
    template <class Item, int Width, int Height>
    struct hash<Board<Item, Width, Height>>
    {
        constexpr size_t operator()(const Board<Item, Height, Width> &b) const
        {
            size_t h = 0;
            for (int i = 0; i < Height; i++)
            {
                for (int j = 0; j < Width; j++)
                {
                    size_t ih = std::hash<Item>()(b.get({i, j}));
                    h = sal(h, 1) ^ ih;
                }
            }
            return h;
        }

    private:
        // shift arithmetic left
        static constexpr size_t sal(size_t s, unsigned int c)
        {
            const size_t mask = (CHAR_BIT * sizeof(s) - 1);
            c &= mask;
            return (s << c) | (s >> ((-c) & mask));
        }
    };
} // namespace std

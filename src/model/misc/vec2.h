#pragma once

#include <cstdint>

struct vec2
{
    int r;
    int c;

    bool operator==(const vec2 &other) const
    {
        return r == other.r && c == other.c;
    }

    void operator+=(const vec2 &other)
    {
        r += other.r;
        c += other.c;
    }

    vec2 operator+(const vec2 &other) const
    {
        vec2 new_vec2 = vec2{*this};
        new_vec2 += other;
        return new_vec2;
    }
};

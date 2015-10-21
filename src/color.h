#ifndef COMMON_H_X2AOOYW9
#define COMMON_H_X2AOOYW9

#include <vector>
#include "matrix.h"

class Color{
    public:
        unsigned char r, g, b;
        Color() :
            r(0), g(0), b(0) {}
        Color(unsigned char r, unsigned char g, unsigned char b) :
            r(r), g(g), b(b) {}
        bool operator==(const Color &c) const
        {
            return c.r == r && c.g == g && c.b == b;
        }
        bool operator!=(const Color &c) const { return !(c == *this); }
        bool operator<(const Color &c) const
        {
            return
                (static_cast<unsigned>(r) << 16) +
                (static_cast<unsigned>(g) << 8) +
                static_cast<unsigned>(b)
                <
                (static_cast<unsigned>(c.r) << 16) +
                (static_cast<unsigned>(c.g) << 8) +
                static_cast<unsigned>(c.b);
        }
        static const Color
            white,
            black;
};

#endif /* end of include guard: COMMON_H_X2AOOYW9 */

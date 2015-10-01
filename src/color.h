#ifndef COMMON_H_X2AOOYW9
#define COMMON_H_X2AOOYW9

#include <vector>

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
};

typedef std::vector<Color> ColorVector;
typedef std::vector<ColorVector> ColorMatrix;

#endif /* end of include guard: COMMON_H_X2AOOYW9 */

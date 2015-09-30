#ifndef COMMON_H_X2AOOYW9
#define COMMON_H_X2AOOYW9

#include <vector>

class Color{
    public:
        int r, g, b;
        Color() : r(0), g(0), b(0) {}
        Color(int r, int g, int b) : r(r), g(g), b(b) {}
        bool operator==(const Color &c)
        {
            return c.r == r && c.g == g && c.b == b;
        }
};

typedef std::vector<Color> ColorVector;
typedef std::vector<ColorVector> ColorMatrix;

#endif /* end of include guard: COMMON_H_X2AOOYW9 */

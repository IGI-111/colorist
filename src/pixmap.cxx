#include <fstream>
#include <limits>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "pixmap.h"

namespace {
    unsigned readValue(std::ifstream &stream)
    {
        std::string buf;
        stream >> buf;
        while(buf[0] == '#'){
            // ignore rest of line since it's a comment
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            stream >> buf;
        }
        return std::stoul(buf);
    }

    unsigned maxDepth(const ColorMatrix &matrix)
    {
        unsigned max = 0;
        for(auto line : matrix)
            for(auto col : line){
                if(col.r > max)
                    max = col.r;
                if(col.g > max)
                    max = col.g;
                if(col.b > max)
                    max = col.b;
            }
        return max;
    }
}

ColorMatrix readMonochrome(const std::string &filename)
{
    std::ifstream file(filename);

    std::string buf;
    file >> buf;
    if(buf != "P1")
        throw std::runtime_error(
                "Trying to read PBM file with wrong magic identifier: " + buf);

    auto width = readValue(file);
    auto height = readValue(file);

    ColorMatrix lines;
    for (unsigned i = 0; i < height; ++i) {
        ColorVector line;
        for (unsigned i = 0; i < width; ++i)
            if(readValue(file))
                line.push_back(Color(0,0,0));
            else
                line.push_back(Color(255,255,255));
        lines.push_back(line);
    }

    return lines;
}



void writeColored(const ColorMatrix &bitmap, const std::string &filename)
{
    auto depth = maxDepth(bitmap);
    auto height = bitmap.size();

    if(height == 0)
        throw std::logic_error("Trying to write empty bitmap");

    auto width = bitmap[0].size();
    for (std::size_t i = 1; i < bitmap.size(); ++i)
        if(bitmap[i].size() != width)
            throw std::logic_error("Trying to write nonrectangular bitmap");

    std::ofstream file(filename);
    file << "P3" << std::endl
        << width << std::endl
        << height << std::endl
        << depth << std::endl;

    for(auto line : bitmap){
        for(auto val : line)
            file << static_cast<unsigned>(val.r) << ' '
                << static_cast<unsigned>(val.g) << ' '
                << static_cast<unsigned>(val.b) << ' ';
        file << std::endl;
    }
}

ColorMatrix randomMonochrome(const unsigned width, const unsigned height)
{
    ColorMatrix bitmap;
    for(unsigned j = 0; j < height; ++j){
        ColorVector row;
        for(unsigned i = 0; i < width; ++i)
            row.push_back(rand() % 2 ? Color::black : Color::white);
        bitmap.push_back(row);
    }
    return bitmap;
}

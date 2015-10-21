#include <fstream>
#include <limits>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <random>
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

    unsigned maxDepth(const Matrix<Color> &matrix)
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

Matrix<Color> readMonochrome(const std::string &filename)
{
    std::ifstream file(filename);

    std::string buf;
    file >> buf;
    if(buf != "P1")
        throw std::runtime_error(
                "Trying to read PBM file with wrong magic identifier: " + buf);

    auto width = readValue(file);
    auto height = readValue(file);

    Matrix<Color> lines;
    for (unsigned i = 0; i < height; ++i) {
        std::vector<Color> line;
        for (unsigned i = 0; i < width; ++i){
            auto val = readValue(file);
            if(val == 1)
                line.push_back(Color(0,0,0));
            else if(val == 0)
                line.push_back(Color(255,255,255));
            else
                throw std::runtime_error("Invalid color descriptor: " +
                        std::to_string(val));
        }
        lines.push_back(line);
    }

    return lines;
}



void writeColored(const Matrix<Color> &bitmap, const std::string &filename)
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
        // counting line length to avoid going over the 70 chars limit
        unsigned lineLength = 0;
        for(auto val : line){
            std::stringstream valToAdd;

            valToAdd << static_cast<unsigned>(val.r) << ' '
                << static_cast<unsigned>(val.g) << ' '
                << static_cast<unsigned>(val.b) << ' ';

            lineLength += valToAdd.str().size();
            if(lineLength > 70){
                file << std::endl;
                lineLength = valToAdd.str().size();
            }

            file << valToAdd.str();
        }
        file << std::endl;
    }
}

Matrix<Color> randomMonochrome(const unsigned width, const unsigned height)
{

    static std::random_device rd;
    static std::default_random_engine eng(rd());
    static std::uniform_int_distribution<unsigned> dis(0, 1);

    Matrix<Color> bitmap;
    for(unsigned j = 0; j < height; ++j){
        std::vector<Color> row;
        for(unsigned i = 0; i < width; ++i)
            row.push_back(dis(eng) ? Color::black : Color::white);
        bitmap.push_back(row);
    }
    return bitmap;
}

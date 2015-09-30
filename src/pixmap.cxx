#include "pixmap.h"
#include <fstream>
#include <limits>
#include <vector>
#include <iostream>

int readValue(std::ifstream &stream)
{
    std::string buf;
    while(true){
        stream >> buf;
        if(buf[0] == '#'){
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore rest of line
            buf.clear();
            continue;
        }
        break;
    }
    return std::stoi(buf);
}

ColorMatrix readMonochrome(const std::string &filename)
{
    std::ifstream file(filename);

    std::string buf;
    file >> buf;
    if(buf != "P1")
        throw std::runtime_error("Trying to read PBM file with wrong magic identifier: " + buf);

    auto length = readValue(file);
    auto height = readValue(file);

    ColorMatrix lines;
    for (std::size_t i = 0; i < height; ++i) {
        ColorVector line;
        for (std::size_t i = 0; i < length; ++i)
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

}

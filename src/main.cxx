#include <iostream>
#include <random>
#include <list>
#include "pixmap.h"
#include "disjoint.h"


void colorize(Matrix<Node> &nodes)
{
    static std::random_device rd;
    static std::mt19937 eng(rd());
    static std::uniform_int_distribution<unsigned char> dis(0, 255);

    for (std::size_t y = 0; y < nodes.size(); ++y)
        for (std::size_t x = 0; x < nodes[y].size(); ++x)
            if(nodes.at(x,y).content != Color::black)
                nodes.at(x,y).content = Color(dis(eng), dis(eng), dis(eng));
}

void unionize(const Matrix<Node> &nodes)
{
    for (std::size_t y = 0; y < nodes.size(); ++y)
        for (std::size_t x = 0; x < nodes[y].size(); ++x){
            if(nodes.at(x,y).content != Color::black){
                auto here = nodes.at(x,y).parent;

                auto onRight = nodes.at(x+1,y).parent;
                if(x+1 < nodes[y].size() &&
                        nodes.at(x+1, y).content != Color::black){
                    Disjoint::unite(here, onRight);
                }

                auto onBottom = nodes.at(x,y+1).parent;
                if(y+1 < nodes.size() &&
                        nodes.at(x, y+1).content != Color::black){
                    Disjoint::unite(here, onBottom);
                }
            }
        }
}

int main(int argc, char *argv[])
{
    try{
        if(argc < 3 || argc > 4){
            std::cerr << "Usage:" << std::endl
                << "\tcolourist input.pbm output.ppm"<< std::endl
                << "\tcolourist width height output.ppm"<< std::endl;
            return 1;
        }

        ColorMatrix bitmap;
        if(argc == 3)
            bitmap = readMonochrome(argv[1]);
        else
            bitmap = randomMonochrome(
                    std::stoul(argv[1]),
                    std::stoul(argv[2]));

        // construct disjoint sets matrix
        Matrix<Node> nodes(bitmap.size());
        for (std::size_t y = 0; y < bitmap.size(); ++y)
            for (std::size_t x = 0; x < bitmap[y].size(); ++x)
                nodes[y].emplace_back(bitmap.at(x,y));

        std::list<Disjoint> sets;
        for (std::size_t y = 0; y < nodes.size(); ++y)
            for (std::size_t x = 0; x < nodes[y].size(); ++x)
                sets.emplace_back(&nodes.at(x,y));

        // add random color for every white pixel
        colorize(nodes);

        // unions
        unionize(nodes);

        for (std::size_t y = 0; y < nodes.size(); ++y)
            for (std::size_t x = 0; x < nodes[y].size(); ++x)
                bitmap.at(x,y) = nodes.at(x,y).content;

        writeColored(bitmap, argv[argc-1]);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

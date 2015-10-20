#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
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

void unite(
        const Coord &c1,
        const Coord &c2,
        const Matrix<Node> &nodes)
{
    auto set1 = nodes.at(c1).parent;
    auto set2 = nodes.at(c2).parent;

    // let's do less operations if we can
    if(set1->size() < set2->size())
        Disjoint::unite(set2, set1);
    else
        Disjoint::unite(set1, set2);
}

void unionize(const Matrix<Node> &nodes)
{
    for (std::size_t y = 0; y < nodes.size(); ++y)
        for (std::size_t x = 0; x < nodes[y].size(); ++x){
            if(nodes.at(x,y).content != Color::black){
                auto here = Coord(x,y);

                auto onRight = Coord(x+1,y);
                if(x+1 < nodes[y].size() &&
                        nodes.at(onRight).content != Color::black){
                    unite(here, onRight, nodes);
                }

                auto onBottom = Coord(x,y+1);
                if(y+1 < nodes.size() &&
                        nodes.at(onBottom).content != Color::black){
                    unite(here, onBottom, nodes);
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

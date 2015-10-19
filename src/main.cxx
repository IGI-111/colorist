#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include "pixmap.h"
#include "disjoint.h"


void colorize(ColorMatrix &bitmap)
{
    static std::random_device rd;
    static std::mt19937 eng(rd());
    static std::uniform_int_distribution<unsigned char> dis(0, 255);

    for (std::size_t y = 0; y < bitmap.size(); ++y)
        for (std::size_t x = 0; x < bitmap[y].size(); ++x)
            if(bitmap.at(x,y) != Color::black)
                bitmap.at(x,y) = Color(dis(eng), dis(eng), dis(eng));
}

void unite(const Coord &c1, const Coord &c2, ColorMatrix &bitmap, std::list<Disjoint> &sets, const std::map<Coord, Node> &nodes)
{
    auto repr1 = nodes.at(c1).head;
    auto set1 = std::find_if(sets.begin(), sets.end(),
            [repr1](auto dis){ return dis.repr() == repr1; });

    auto repr2 = nodes.at(c2).head;
    auto set2 = std::find_if(sets.begin(), sets.end(),
            [repr2](auto dis){ return dis.repr() == repr2; });

    for(auto set : sets){
        std::cout << set.size() << ' ';
        for(auto ptr: set)
            std::cout << ptr << ' ';
        std::cout << std::endl;
    }
        std::cout << std::endl;

    Disjoint::unite(set1, set2, sets, bitmap);


}

void unionize(ColorMatrix &bitmap, std::list<Disjoint> &sets, const std::map<Coord, Node> &nodes)
{
    for(auto val : nodes){
            auto here = val.first;
            auto x = here.first;
            auto y = here.second;
            auto onRight = Coord(x+1,y);
            //auto onLeft = Coord(x-1,y);
            auto onBottom = Coord(x,y+1);
            //auto onTop = Coord(x,y-1);

            if(nodes.count(onRight) > 0)
                unite(here, onRight, bitmap, sets, nodes);
            //if(sets.count(onLeft) > 0)
            //unite(here, onLeft, bitmap, sets);
            if(nodes.count(onBottom) > 0)
                unite(here, onBottom, bitmap, sets, nodes);
            //if(sets.count(onTop) > 0)
            //unite(here, onTop, bitmap, sets);
        }
}

int main(int argc, char *argv[])
{
    try{
        if(argc != 3){
            std::cerr << "Usage: colourist input.pbm output.ppm"<< std::endl;
            return 1;
        }

        auto bitmap = readMonochrome(argv[1]);
        //auto bitmap = randomMonochrome(7,7);

        // construct disjoint sets matrix
        std::map<Coord, Node> nodes;
        for (std::size_t y = 0; y < bitmap.size(); ++y)
            for (std::size_t x = 0; x < bitmap[y].size(); ++x)
                if(bitmap.at(x,y) != Color::black)
                    nodes[Coord(x,y)] = Node(Coord(x,y));

        std::list<Disjoint> sets;
        for(auto val : nodes)
            sets.emplace_back(&nodes[val.first]);

        // add random color for every white pixel
        colorize(bitmap);

        // unions
        unionize(bitmap, sets, nodes);

        writeColored(bitmap, argv[2]);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

#include <iostream>
#include <random>
#include <list>
#include "pixmap.h"
#include "disjoint.h"


void colorize(Matrix<Node<Color>*> &nodes)
{
    static std::random_device rd;
    static std::mt19937 eng(rd());
    static std::uniform_int_distribution<unsigned char> dis(0, 255);

    for (std::size_t y = 0; y < nodes.size(); ++y)
        for (std::size_t x = 0; x < nodes[y].size(); ++x)
            if(nodes.at(x,y)->content != Color::black)
                nodes.at(x,y)->content = Color(dis(eng), dis(eng), dis(eng));
}

void unionize(const Matrix<Node<Color>*> &nodes)
{
    for (std::size_t y = 0; y < nodes.size(); ++y)
        for (std::size_t x = 0; x < nodes[y].size(); ++x){
            if(nodes.at(x,y)->content != Color::black){
                auto here = nodes.at(x,y)->parent;
                if(x+1 < nodes[y].size() &&
                        nodes.at(x+1, y)->content != Color::black){
                    auto onRight = nodes.at(x+1,y)->parent;
                    Disjoint<Color>::unite(here, onRight);
                }
                if(y+1 < nodes.size() &&
                        nodes.at(x, y+1)->content != Color::black){
                    auto onBottom = nodes.at(x,y+1)->parent;
                    Disjoint<Color>::unite(here, onBottom);
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

        Matrix<Color> bitmap;
        if(argc == 3)
            bitmap = readMonochrome(argv[1]);
        else
            bitmap = randomMonochrome(
                    std::stoul(argv[1]),
                    std::stoul(argv[2]));

        // construct disjoint sets matrix
        Matrix<Node<Color>*> nodes(bitmap.size());
        std::list<Disjoint<Color>> sets;
        for (std::size_t y = 0; y < bitmap.size(); ++y)
            for (std::size_t x = 0; x < bitmap[y].size(); ++x){
                sets.emplace_back(bitmap.at(x,y));
                nodes[y].push_back(sets.back().repr());
            }

        colorize(nodes);
        unionize(nodes);

        for (std::size_t y = 0; y < nodes.size(); ++y)
            for (std::size_t x = 0; x < nodes[y].size(); ++x)
                bitmap.at(x,y) = nodes.at(x,y)->content;

        writeColored(bitmap, argv[argc-1]);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

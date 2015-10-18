#include <iostream>
#include <algorithm>
#include "pixmap.h"
#include "disjoint.h"

int main(int argc, char *argv[])
{
    try{
        if(argc != 3){
            std::cerr << "Usage: colourist input.pbm output.ppm"<< std::endl;
            return 1;
        }

        auto bitmap = readMonochrome(argv[1]);

        DisjointMatrix sets(bitmap.size());

        for (std::size_t y = 0; y < bitmap.size(); ++y)
            for (std::size_t x = 0; x < bitmap[y].size(); ++x)
                sets[y].push_back(std::make_shared<Disjoint>(Coord(x,y)));
        
        //TODO: set unions

        writeColored(bitmap, argv[2]);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

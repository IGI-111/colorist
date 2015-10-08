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

        auto input = readMonochrome(argv[1]);

        DisjointMatrix<Color> sets(input.size());

        // transform all pixels into Disjoint sets
        for(std::size_t i = 0; i < input.size(); ++i)
            std::transform(
                    input[i].begin(), input[i].end(),
                    std::back_inserter(sets[i]),
                    [](const Color &c){ return Disjoint<Color>(c); });

        ColorMatrix output(sets.size());

        // transform all Disjoint sets into colors
        for(std::size_t i = 0; i < sets.size(); ++i)
            std::transform(
                    sets[i].begin(), sets[i].end(),
                    std::back_inserter(output[i]),
                    [](const Disjoint<Color> &c){ return c.find(); });

        writeColored(output, argv[2]);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

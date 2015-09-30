#include <iostream>
#include "pixmap.h"

int main(int argc, char *argv[])
{
    try{
        if(argc != 2){
            std::cerr << "Usage: colourist input.pbm output.ppm"<< std::endl;
            return 1;
        }

        auto matrix = readMonochrome(argv[1]);
        for(auto line : matrix){
            for(auto val : line)
                if(val == Color(0,0,0))
                    std::cout << "█";
                else if(val == Color(255,255,255))
                    std::cout << ' ';
                else
                    std::cout << '?';
            std::cout << std::endl;
        }

    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

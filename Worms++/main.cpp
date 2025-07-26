// The main function of the program that calls all the other code. 

// g++ main.cpp worms++.hpp game.cpp worm.cpp to_cli.cpp to_board.cpp to_file.cpp -o Worms++.x86_64 -lncurses

// x86_64-w64-mingw32-g++-posix main.cpp worms++.hpp game.cpp worm.cpp to_cli.cpp to_board.cpp to_file.cpp -I./PDCurses -L./PDCurses/wincon -l:pdcurses.a -o Worms++.exe -static

#include"worms++.hpp"

#include<vector>
#include<string>

using namespace Worms; 
using namespace std; 

int main(int argc, char *argv[]) { // + 1 to skip program name
    const vector<string> args = {argv + 1, argv + argc}; 
    
    if (print_help(args))
        return 0;
    
    Game(make_worms(args), get_yx(args), get_time_step(args)).play(); 
    
    return 0;
}


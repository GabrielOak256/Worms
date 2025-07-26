// The functions that support drawing to the screen. 
    
#include"worms++.hpp"

#include <curses.h>

#include<iostream>
#include<vector>
#include<string>
    
namespace Worms {
    using std::vector;
    using std::pair;    
    using std::make_pair;
    
    
void open_board() {                                         
    initscr();   // start ncurses
    if (!has_colors()) {
        endwin();
        std::cerr << "This terminal does not support color.\n";
        exit(1); // terminate the program 
    }
    curs_set(0);          // Make cursor tranparent.
    noecho();             // Don't display keyboard input. 
    intrflush(stdscr, FALSE); // Prepare to enable keypad input. 
    keypad(stdscr, TRUE);     //            Enable keypad input. 
    start_color();        // Enable colored text. 
    if (COLOR_PAIRS < 10)  // For all 8 worm colors, and the highlight and the blackout for ask_path(). 
        std::cerr << "This terminal only supports " << COLOR_PAIRS-1 << " worms.\n";
}
    
void close_board() {
    char c = '\0';
    while (!isalpha(c = getch())) // Await 'press any letter'. 
        ;    
    curs_set(1); // Return cursor to normal. 
    endwin();    // Exit ncurses. 
}
    
// Converts worm's point coordinates to ncurses' screen coordinates. 
pair<int,int> point_to_board(const int y, const int x) { 
    // Every other row of points '*' is offset. 
    if (y % 2) // odd y
        return make_pair(2*y, 4*x + 2);
    else       // even y
        return make_pair(2*y, 4*x);   
}
pair<int,int> point_to_board(const pair<int,int>& pos) { return point_to_board(pos.first, pos.second); }
    
    
// Converts board's paths' coordinates to ncurses' screen coordinates. 
pair<int,int> path_to_board(const int y, const int x) { 
    // All characters' positions in odd rows are the same as other odd rows. 
    if (y % 2) {   // y = 4n + 1, 4n + 3
        return make_pair(y, 2*x + 1);
    } else {       
    // Even (flat) rows alternate in starting offset or not. 
        if (y % 4) // y = 4n + 2
            return make_pair(y, 4*x);
        else       // y = 4n 
            return make_pair(y, 4*x + 2);
    }
}
pair<int,int> path_to_board(const pair<int,int>& pos) { return path_to_board(pos.first, pos.second); }


// What character should be printed according to the grid location of the path?
char text_by_loc(const int y, const int x) {   
    
    // All even height paths are flat.     
    if (!(y % 2)) 
        return '-'; 
     
    // Odd rows alternate / and \, switching which comes first. 
    if ((y % 4) == 1) {
        if (x % 2) 
            return '/';  
        else       
            return '\\'; 
    } else { // y % 4 == 3
        if (x % 2) 
            return '\\'; 
        else       
            return '/';  
    }
}
char text_by_loc(const pair<int,int>& pos) { return text_by_loc(pos.first, pos.second); }


// What character should be printed according to the slope of the path? 
char text_by_dir(const int path) {       
    if (!(path % 3))               // path = 3n 
        return '-';
    else if (!((path % 3) - 1))    // path = 3n + 1
        return '/';
    else // if (!((path % 3) - 2)) // path = 3n + 2
        return '\\';
}


} // namespace Worms 

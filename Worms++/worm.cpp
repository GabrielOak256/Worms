// This file defines the members and helpers of the Worm class. 

#include"worms++.hpp"

#include <curses.h>

#include<cmath>     // pow()
#include<chrono>    // microseconds()
#include<thread>    // sleep_for() 

namespace Worms {
    
Worm::Worm(const int color, const vector<int>& code, const pair<int,int>& pos): color{color}, code{code}, pos{pos} {}
    
    
int Worm::step(const vector<int>& paths, const pair<int,int>& bounds) {
    
    const int paths_bits = paths_to_int(paths);
    
    if (paths_bits == 0) { return -1; } // If all paths are deactivated, the worm dies. 
    
    if (code[paths_bits] == -1) // If the code signals to ask for player input,
        code[paths_bits] = ask_path(paths, bounds); // use player input. 
    else if (code[paths_bits] == -2) // If the code signals to randomly choose, 
        code[paths_bits] = gen_path(paths);         // then randomly choose. 
    
    set_pos(interpret_code(code[paths_bits]), bounds); // Take the step. 
    
    return (code[paths_bits] + 3) % 6; // Return the path it just traversed. 
} // step


int Worm::get_color() const { return color; }

vector<int> Worm::get_code() const { return code; }

pair<int,int> Worm::get_pos() const { return pos; }

void Worm::set_pos(const int y, const int x, const pair<int,int> bounds) {
    pos.first  = (y + (bounds.first/2) ) % (bounds.first/2); 
    pos.second = (x + (bounds.second/4)) % (bounds.second/4); 
}
void Worm::set_pos(const pair<int,int> position, const pair<int,int> bounds) {
    set_pos(position.first, position.second, bounds); 
}

// C++ still doesn't default construct equality conditions for classes. 
bool Worm::operator==(Worm const& worm) { 
    return (color == worm.get_color()) && (pos == worm.pos) && (code == worm.code);
}

// A convenient place to write out how the worm's rectangular (y,x) transforms map onto a triangular grid. 
pair<int,int> Worm::interpret_code(const int dir) { 
    
    // Make below more readable. 
    const int y = pos.first;
    const int x = pos.second; 
    
    if (y % 2) { // y is odd 
        //  * *       * *
        // * * * -> * * *
        //  * *       * * 
        switch (dir % 6) { 
        case 0: return make_pair(y,     x + 1); // In trig, angle 0 is right
        case 1: return make_pair(y - 1, x + 1); // up-right  
        case 2: return make_pair(y - 1, x);     // up-left 
        case 3: return make_pair(y,     x - 1); // left    
        case 4: return make_pair(y + 1, x);     // down-left  
        case 5: return make_pair(y + 1, x + 1); // down-right 
        } 
    } else {     // y is even
        //  * *     * *
        // * * * -> * * *
        //  * *     * * 
        switch (dir % 6) { 
        case 0: return make_pair(y,     x + 1); // right
        case 1: return make_pair(y - 1, x);     // up-right  
        case 2: return make_pair(y - 1, x - 1); // up-left 
        case 3: return make_pair(y,     x - 1); // left    
        case 4: return make_pair(y + 1, x - 1); // down-left  
        case 5: return make_pair(y + 1, x);     // down-right 
        }
    }
    
// The above generates a compiler warning about control falling off without a 
// return statement. However, by the nature of modulus, every case is covered. 
    
} // interpret_code 


// Ask the player which path to encode. 
int Worm::ask_path(const vector<int>& open_paths, const pair<int,int>& bounds) {
    
    // Prepare the highlight color pair. 
    if (color == COLOR_BLACK || color == COLOR_WHITE) 
        init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
    else 
        init_pair(8, COLOR_WHITE, color);
    
    // Windows CMD produces light grey when a space is drawn by COLOR_PAIR(0). 
    init_pair(9, COLOR_BLACK, COLOR_BLACK); 
    
    // Make the following characters we place blink. 
    attron(A_BLINK);
    
    int choice = 0;
    int input = 0; 
    pair<int,int> cursor = make_pair(-1,-1); 
    
    do { // A "do" rather than "while" so that the player doesn't need to press a key to see the highlights. 
        mvaddch(cursor.first, cursor.second, ' ' | COLOR_PAIR(9)); // Clear the last highlight.  
        
        // A simple rolling wheel for an interface. 
        if (input == KEY_UP) 
            choice = (choice + 1) % open_paths.size(); 
        else if (input == KEY_DOWN) 
            choice = (choice + (open_paths.size() - 1)) % open_paths.size(); 
        
        // Display the result of the keypress. 
        cursor = path_to_board(point_to_path(pos, open_paths[choice], bounds)); 
        mvaddch(cursor.first, cursor.second, text_by_dir(open_paths[choice]) | COLOR_PAIR(8));
    } while ((input = getch()) != '\n'); // "Enter" will be used to signal a decision. 
    mvaddch(cursor.first, cursor.second, ' ' | COLOR_PAIR(9)); // Remove the last (chosen) highlight. 
	
	// The characters we place from now on should no longer blink. 
    attroff(A_BLINK);
	    
    return open_paths[choice];
} // ask_path


// Choose a random path from the available options. 
int gen_path(const vector<int>& open_paths) {               
    std::srand(std::time(nullptr)); // Seed RNG with current time. 
    return open_paths[std::rand() % open_paths.size()]; // Choose an option. 
} // gen_path 


// Activate the bits at the given indexes. 
int paths_to_int(const vector<int> paths) {
    int result = 0;
    for (const int i : paths) 
        result += pow(2,i); 
    return result; 
} 
    
    
} // namespace Worms


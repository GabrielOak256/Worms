// This file defines the members and helpers of the Game class. 

#include"worms++.hpp"

#include <curses.h>

#include<vector> 
#include<algorithm> // find()
#include<chrono>    // microseconds()
#include<thread>    // sleep_for() 

namespace Worms {
    using std::vector;
    using std::pair;
    using std::make_pair;
    

// Class Constructor for Game                                                           // Round down to a multiple of 4 for both axes. 
Game::Game(const vector<Worm>& input_worms, const int y, const int x, const double time_step): worms{input_worms}, bounds{make_pair( ((y/4)*4) , ((x/4)*4) )}, time_step{time_step} {
    
     // Set the worms' starting positions. 
    if (worms.size() > 6) {         // If there are more than 6, 
        for (int i = 0; i < 4; ++i) // Start half on opposite sides. 
            worms[i].set_pos((y/2)/2, (x/4)/4, bounds); 
        for (int i = 4; i < worms.size(); ++i)
            worms[i].set_pos((y/2)/2, 3*(x/4)/4, bounds);
    } else {                        // If there are less than 6,
        for (auto& worm : worms)    // Start them all at the middle. 
            worm.set_pos((y/2)/2, (x/4)/2, bounds);
    }
    
    // The scores of all present worms should be initialized to 0, not -1 for absent. 
    for (const auto& worm : worms)
        scores[worm.get_color()] = 0;
    
    // Set the paths vectors to the appropriate size. 
    paths.resize(y); 
    for (int i = 0; i < y; ++i)
        paths[i].assign(row_length(i,bounds.second), 1); 
}
Game::Game(const vector<Worm>& input_worms, const pair<int,int>& bounds, const double time_step): Game(input_worms, bounds.first, bounds.second, time_step) {}


void Game::play() {
    open_board();
    while (!worms.empty())
        step(); 
    close_board();
    print_scores(scores); 
    save_worms(finished_worms, "worms.txt"); 
}
    
void Game::step() {            
    for (auto worm_iter = worms.begin(); worm_iter < worms.end(); ++worm_iter) { 
        
        // Store the worm's position before moving it. 
        const pair<int,int> old_pos = worm_iter->get_pos();
        
        // Store the available paths around the current position.
        const vector<int> open_paths = get_paths(old_pos); 
        
        // Get the worm's position in terms of terminal coordinates. 
        pair<int,int> cursor = point_to_board(old_pos);
        
        // Prepare ncurses with the worm's color. 
        // In ncurses, COLOR_PAIR(0) is hardcoded to WHITE (7) on BLACK (0).
        // So I inverted the color values to define the indexes. 
        //        index,                    text color,             background color
        init_pair(7-worm_iter->get_color(), worm_iter->get_color(), (worm_iter->get_color() ? COLOR_BLACK : COLOR_WHITE)); 
        
        // If there are no paths left, the worm dies. 
        if (open_paths.empty()) {
            mvaddch(cursor.first, cursor.second, 'X' | COLOR_PAIR(7-worm_iter->get_color()));
            finished_worms.push_back(*worm_iter); 
            worms.erase(worm_iter); 
            continue; 
        }
        
        // The worm takes its step. 
        const int taken_path = worm_iter->step(open_paths, bounds);
        
        // Deactivate the taken path. 
        const pair<int,int> path_index = point_to_path(worm_iter->get_pos(), taken_path, bounds); 
        paths[path_index.first][path_index.second] = false; 
        
        // Draw the taken path to the board. 
        cursor = path_to_board(path_index);
        mvaddch(cursor.first, cursor.second, text_by_dir(taken_path) | COLOR_PAIR(7-worm_iter->get_color()));
        
        // Draw the new point to the board. 
        cursor = point_to_board(worm_iter->get_pos());
        mvaddch(cursor.first, cursor.second, '*' | COLOR_PAIR(7-worm_iter->get_color()));
        
        // If the worm took the last path out of a space, score and draw it. 
        if (get_paths(old_pos).empty()) {
            ++scores[worm_iter->get_color()];
            cursor = point_to_board(old_pos);
            mvaddch(cursor.first, cursor.second, '0' | COLOR_PAIR(7-worm_iter->get_color())); 
        }
        
    }
    refresh();
    std::this_thread::sleep_for(std::chrono::microseconds(int(time_step*1000000)));
}


// Returns how many paths are there according to the y coordinate. 
int row_length(const int y, const int width) {                 
    // There are twice as many slanted as flat. 
    if (y % 2) { return (width/4)*2; } // odd rows 
    else       { return  width/4; }    // even rows 
}


// Returns indexes of active paths around a point. 
vector<int> Game::get_paths(const int y, const int x) {
    vector<int> result = {};
    for (int i = 0; i < 6; ++i) {
        pair<int,int> yx = point_to_path(y,x,i,bounds);
        if (paths[yx.first][yx.second])
            result.push_back(i);
    }
    return result; 
}
vector<int> Game::get_paths(const pair<int,int>& pos) { return get_paths(pos.first, pos.second); }


// Converts worm's point coordinates to board's paths' coordinates. 
pair<int,int> point_to_path(const int y, const int x, const int path, const pair<int,int>& bounds) {
    pair<int,int> result = make_pair(0,0);
    
    if (y % 2) { // y is odd
        switch (path % 6) {        // In trig, angle 0 is right.
            case 0: result = make_pair(2*y,       x + 1); break; // right
            case 1: result = make_pair(2*y - 1, 2*x + 1); break; // up-right  
            case 2: result = make_pair(2*y - 1, 2*x);     break; // up-left 
            case 3: result = make_pair(2*y,       x);     break; // left    
            case 4: result = make_pair(2*y + 1, 2*x);     break; // down-left  
            case 5: result = make_pair(2*y + 1, 2*x + 1); break; // down-right  
        }
    } else {     // y is even: 
        switch (path % 6) {        // In trig, angle 0 is right.
            case 0: result = make_pair(2*y,       x);     break; // right
            case 1: result = make_pair(2*y - 1, 2*x);     break; // up-right  
            case 2: result = make_pair(2*y - 1, 2*x - 1); break; // up-left 
            case 3: result = make_pair(2*y,       x - 1); break; // left    
            case 4: result = make_pair(2*y + 1, 2*x - 1); break; // down-left  
            case 5: result = make_pair(2*y + 1, 2*x);     break; // down-right  
        }
    }
    
    return make_pair((result.first + bounds.first) % bounds.first, (result.second + row_length(result.first,bounds.second)) % row_length(result.first,bounds.second));
} 
pair<int,int> point_to_path(const pair<int,int>& pos, const int path, const pair<int,int>& bounds) { return point_to_path(pos.first, pos.second, path, bounds); } 

    
} // namespace Worms


// The header providing declarations for the entire Worms namespace. 

#ifndef WORMS_07_24_2025
#define WORMS_07_24_2025

#include<vector>
#include<string>
#include<array>

namespace Worms {
    using std::vector;
    using std::string;
    using std::array; 
    using std::pair;
    using std::make_pair;


#ifdef _WIN32 // pdcurses 
const vector<string> color_name = {"black", "blue", "green", "cyan", "red", "magenta", "yellow", "white"};
#else         // ncurses 
const vector<string> color_name = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};
#endif 

// Worm 
class Worm {
public:
        
    Worm(const int color = 0, const vector<int>& code = vector<int>(64), const pair<int,int>& pos = make_pair(0,0));
    
    int step(const vector<int>& paths, const pair<int,int>& bounds); 
    
    int get_color() const; 
    vector<int> get_code() const;                       
    pair<int,int> get_pos() const;
    void set_pos(const pair<int,int> position, const pair<int,int> bounds); 
    void set_pos(const int y, const int x, const pair<int,int> bounds);
    
    bool operator==(Worm const& worm); 
    
private: 
    
    pair<int,int> interpret_code(const int paths);      
    
    int ask_path(const vector<int>& paths, const pair<int,int>& bounds); 
                                                        
    int color = 0; 
    vector<int> code = {};
    pair<int,int> pos = make_pair(0,0); // (y,x)
    
}; // class Worm 

int gen_path(const vector<int>& open_paths); 
int paths_to_int(const vector<int> paths); 

// Game 
class Game {
public:
     
    Game(const vector<Worm>& input_worms, const int y = 20, const int x = 80, const double time_step = 0.25); 
    Game(const vector<Worm>& input_worms, const pair<int,int>& bounds = make_pair(20,80), const double time_step = 0.25); 
    
    void play();                                        
    
    const pair<int,int> bounds = make_pair(20,80); // (y,x) 
    
private:
    
    void step();                     
    
    vector<int> get_paths(const int y, const int x);     
    vector<int> get_paths(const pair<int,int>& pos);
    
    vector<Worm> worms = {};
    vector<Worm> finished_worms = {};
    vector<int> scores = vector<int>(8,-1); // {-1,-1,-1,-1,-1,-1,-1,-1}
    
    vector<vector<bool>> paths = {}; // paths[y][x]  
    
    const double time_step = 0.25; 
    
}; // class Game 

int row_length(const int y, const int width);
pair<int,int> point_to_path(const int y, const int x, const int path, const pair<int,int>& bounds); 
pair<int,int> point_to_path(const pair<int,int>& pos, const int path, const pair<int,int>& bounds); 
                                                        
    
// CLI Interface 
pair<int,int> get_yx(const vector<string>& args);       
vector<Worm> make_worms(const vector<string>& args);    
double get_time_step(const vector<string>& args); 
bool print_help(const vector<string>& args); 
void print_scores(const vector<int>& scores); 
    
// Save and Load
void save_worms(vector<Worm> worms, const string& filepath); 
vector<vector<int>> load_codes(const string& filepath);      
    
// Board Text 
void open_board();
void close_board(); 
pair<int,int> point_to_board(const int y, const int x); 
pair<int,int> point_to_board(const pair<int,int>& pos); 
pair<int,int> path_to_board(const int y, const int x);  
pair<int,int> path_to_board(const pair<int,int>& pos);  
char text_by_loc(const int y, const int x); 
char text_by_loc(const pair<int,int>& pos); 
char text_by_dir(const int path); 
    
} // namespace Worms

#endif

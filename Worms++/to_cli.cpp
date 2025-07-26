// The functions that process CLI arguments and write to stdout. 

#include"worms++.hpp"

#include<iostream>
#include<vector>
#include<string>
#include<algorithm> 

namespace Worms {
    using std::vector;
    using std::string;
    using std::array; 
    using std::pair;
    using std::make_pair;
    using std::count;
    using std::fill;


// Read in the specified x and y values. 
pair<int,int> get_yx(const vector<string>& args) { 
    
    // sensible defaults         
    int y = 20; 
    int x = 80; 
    
    // If "y" can be found among the arguments, 
    // and there is an argument in front of it, 
    // convert that argument to an int and use that for y. 
    auto iter = find(args.begin(), args.end(), "y");
    if (iter != (args.end()-1) && iter != args.end())
        try { y = stoi(*(iter+1)); } catch (const std::invalid_argument&) {}
            
    // Duplicate code for x. 
    iter = find(args.begin(), args.end(), "x");
    if (iter != (args.end()-1) && iter != args.end())
        try { x = stoi(*(iter+1)); } catch (const std::invalid_argument&) {}
        
    return make_pair(y,x);
}


vector<Worm> make_worms(const vector<string>& args) {    
    
    // Load codes for the worms. 
    vector<vector<int>> codes = load_codes("worms.txt");  
    
    vector<Worm> playable = {};
    vector<Worm> rand_and_file = {};
    
    // For each argument, 
    for (int i = 0; i < args.size(); ++i) { 
        
        // If this argument isn't the name of a color, move on. 
        const auto color_iter = find(color_name.begin(), color_name.end(), args[i]); 
        if (color_iter == color_name.end())  
            continue; 
        
        // Store the mentioned color. 
        const int color = color_iter - color_name.begin();
        
        // Use the first mode argument found after this argument. Default to random.
        bool is_playable = false;
        vector<int> code(64); 
        for (int j = i+1; j < args.size() + 1; ++j) {
            if (j == args.size()) { 
                fill(code.begin(), code.end(), -2);
            } else if (args[j] == "FILE") {
                code = codes[color];
                if (count(code.begin(), code.end(), -1))
                    is_playable = true;    
                break; 
            } else if (args[j] == "PLAY") {
                fill(code.begin(), code.end(), -1);
                is_playable = true; 
                break;
            } else if (args[j] == "RAND") { 
                fill(code.begin(), code.end(), -2);
                break;
            }  
        }
        
        // Make a worm and add it to the vector. 
        Worm worm(color, code);  
        if (is_playable) { playable.push_back(worm); }
        else        { rand_and_file.push_back(worm); }
    }
    
    // Sort the worms according to color, with priority given to playable ones.  
    sort(playable.begin(),      playable.end(),      [](const auto& a, const auto& b){return a.get_color() < b.get_color();}); 
    sort(rand_and_file.begin(), rand_and_file.end(), [](const auto& a, const auto& b){return a.get_color() < b.get_color();}); 
    
    // Combine and return the vector<Worm>s. 
    playable.insert(playable.end(), rand_and_file.begin(), rand_and_file.end());
    return playable; 
}


double get_time_step(const vector<string>& args) {
    // If "speed" can be found among the arguments, 
    // and there is an argument in front of it, 
    // convert that argument to a double and use that for time_step. 
    double result = 0.25;
    auto iter = find(args.begin(), args.end(), "speed");
    if (iter != (args.end()-1) && iter != args.end())
        try { result = stod(*(iter+1)); } catch (const std::invalid_argument&) {}
    return result; 
}


// Print the "-h" help menu. 
bool print_help(const vector<string>& args) {
    if (count(args.begin(), args.end(), "-h") || count(args.begin(), args.end(), "--help")  || count(args.begin(), args.end(), "h") || count(args.begin(), args.end(), "help")) {
        
        std::cout << "Worms++ [worm color] [worm mode]\n";
        std::cout << "y [integer value for screen height]\n";
        std::cout << "x [integer value for screen width]\n";
        std::cout << "speed [decimal value for seconds per step]\n";
        std::cout << "Example:    Worms++ white FILE\n";
        std::cout << "Example:    Worms++ y 40 x 160 speed 0.03125 white black FILE cyan yellow magenta RAND red green blue PLAY\n";
        
        return true; 
    }
    return false; 
}


// A helper function to display scores after gameplay. 
void print_scores(const vector<int>& scores) { 
    if (scores.size() != 8) {
        return;  
    }
    for (int i = 0; i < 8; ++i)
        if (scores[i] != -1) 
            std::cout << "\n" << color_name[i] << "\t" << scores[i];
        else
            std::cout << "\n" << color_name[i] << "\t" << '-';
    std::cout << "\n";
}

} // namespace Worms 

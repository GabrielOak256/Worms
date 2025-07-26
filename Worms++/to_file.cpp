// The functions that support writing to a file, to persist data between games. 

#include"worms++.hpp"

#include<iostream>
#include<fstream>   // ifstream, ofstream 
#include<sstream>   // stringstream
#include<vector>
#include<string>
#include<algorithm> // find()
#include<bitset>
#include<string.h>  // strtok() 

namespace Worms {
    using std::vector;
    using std::string; 
    using std::array; 
    using std::bitset; 
    using std::ifstream;
    using std::ofstream; 
    using std::stringstream;
    using std::stoi; 
                                                         
void save_worms(vector<Worm> worms, const string& filepath) { // pass by value
    if (worms.empty()) 
        return; 
    
    // Store the worms in a consistent ordering (ascending color). This is the reason for pass by value. 
    sort(worms.begin(), worms.end(), [](const auto& a, const auto& b){return a.get_color() < b.get_color();}); 
    
    // Open the file for writing. 
    ofstream output(filepath, std::ofstream::out);
    
    // Write the worm data. 
    for (const auto& worm : worms) {
        output << color_name[worm.get_color()] << "\n";
        for (int i = 0; i < 64; ++i) // Write the encodings as 6 booleans referring to the activation of surrounding paths. 
            output << bitset<6>(i) << " " << worm.get_code()[i] << "\n";
        output << "\n\n";
    }
    
    output.close();
} // save_worms 

vector<vector<int>> load_codes(const string& filepath) { 
    
    // Set aside space for all 8 colors' codes. 
    vector<vector<int>> result(8); 
    
    // Set each code to 64 -2s. 
    for (auto& worm_code : result) 
        worm_code.assign(64, -2);
    
    // Open the filepath. 
    ifstream file(filepath, std::ifstream::in);
    
    // If there is no file or empty file to read from, return defaults.
    if (!(file && file.peek() != EOF)) 
        return result; 
    
    int color = 0; 
    string line = "";
    while (!file.eof()) {
        getline(file, line); 
        
        // If the line is a color label, store the color value and go to next line. 
        const auto next_color = find(color_name.begin(), color_name.end(), line); 
        if (next_color != color_name.end()) {
            color = next_color - color_name.begin(); 
            continue;
        }
        
        // Get the contents of the line. 
        stringstream line_stream(line);   // Treat line as a stream for getline(). 
        string key = "";                  // Set aside memory.
        string value = "";                // Set aside memory. 
        getline(line_stream, key, ' ');   // Read line into key until a ' ', 
        getline(line_stream, value, ' '); // Continue reading line into value until a ' '.
        
        int index = 0;
        int choice = 0;
        try {     // If possible, convert those strings to usable values. 
            index = stoi(key, nullptr, 2); // read binary 
            choice = stoi(value);
        } catch (const std::invalid_argument&) {
            continue;
        }
        
        // Add the code.  
        if (0 <= index && index < 64 && -2 <= choice && choice < 6) 
            result[color][index] = choice; 
    }
    
    file.close(); 
    
    return result;
} // load_codes


} // namespace Worms 



#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

// struct DataPoint {
//     int bx;
//     double time;
// };

int get_min_max_BX() {
    std::string filename = "BX_time_distribution.txt";  // Your file name
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    // Store data grouped by BX
    std::map<int, std::vector<double>> bxData;
    int bx;
    double time;
    
    // Read file
    while (file >> bx >> time) {
        bxData[bx].push_back(time);
    }
    file.close();
    
    // Find min and max for BX 19, 20, 21
    std::vector<int> targetBX = {18, 19, 20, 21, 22};
    
    for (int target : targetBX) {
        auto it = bxData.find(target);
        
        if (it != bxData.end() && !it->second.empty()) {
            auto& times = it->second;
            auto minTime = *std::min_element(times.begin(), times.end());
            auto maxTime = *std::max_element(times.begin(), times.end());
            
            std::cout << "BX " << target << ":" << std::endl;
            std::cout << "  Min time: " << minTime << std::endl;
            std::cout << "  Max time: " << maxTime << std::endl;
            std::cout << "  Count: " << times.size() << std::endl << std::endl;
        } else {
            std::cout << "BX " << target << ": No data found" << std::endl << std::endl;
        }
    }
    
    return 0;
}
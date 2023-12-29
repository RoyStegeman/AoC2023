#include <algorithm>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <limits>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>

int main () {
  std::ifstream file("input.txt");
  // check if the file is opened succesfully (let's not make that mistake again)
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open the file for reading and writing." << std::endl;
  }

  // get the seed ids
  std::string line;
  std::getline(file, line);
  std::istringstream iss(line);
  iss >> line; // remove seeds:
  size_t seed;
  std::vector<size_t> seeds;
  while(iss >> seed) {
    seeds.push_back(seed);
  }

  // parse info on all the mappings from the file
  std::getline(file,line); // skip the empty line after the seeds
  size_t dest, source, range;
  std::vector<std::vector<std::vector<size_t>>> allmaps;
  while(std::getline(file,line)){
    std::vector<std::vector<size_t>> maps_bewtween_two_types;
    std::getline(file,line); // skip the line with the "source-to-dest:" string
    // loop over all lines insde a given mapping, the mapping ends with an empty line
    while(line.size()!=0){
      std::istringstream iss(line);
      iss >> dest >> source >> range;
      maps_bewtween_two_types.push_back({dest, source, range});
      std::getline(file,line);
    }
    allmaps.push_back(maps_bewtween_two_types);
  }

  size_t score = std::numeric_limits<size_t>::max();
  for(const auto& seed: seeds) {
    size_t val = seed;
    for(const auto& maps2t: allmaps) {
      for(size_t i=0; i<maps2t.size(); i++){ // can't break out of a range-based for loop
        size_t dest = maps2t[i][0];
        size_t source = maps2t[i][1];
        size_t range = maps2t[i][2];
        if(val >= source && val <= source+range){
          val += dest - source;
          break; // found the (unique) mapping so no need to check the rest of the mappings
        }
      }
    }
    score=std::min(score,val);
  }
  std::cout << score << std::endl;
}

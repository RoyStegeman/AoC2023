#include <algorithm>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <limits>
#include <ostream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>


// NEW IDEA: only keep track of the outer values of the ranges affected by the mappings

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

  // we don't want double counting so store a new object with begina and end of ranges with the
  // double counting accounted for
  std::vector<std::pair<size_t, size_t>> seedinfo;
  for(size_t i=0; i<seeds.size(); i+=2) {
    seedinfo.push_back({seeds[i],seeds[i+1]});
  }
  // sort based on the starting point of each range of seeds
  std::sort(seedinfo.begin(), seedinfo.end(), [](const auto& a, const auto& b) {
    return a.first < b.first;
  });

  // parse info on all the mappings from the file
  std::getline(file,line); // skip the empty line after the seeds
  size_t dest, source, range;
  std::vector<std::vector<std::vector<size_t>>> allmaps;
  while(std::getline(file,line)){
    std::vector<std::vector<size_t>> maps_between_two_types;
    std::getline(file,line); // skip the line with the "source-to-dest:" string
    // loop over all lines insde a given mapping, the mapping ends with an empty line
    while(line.size()!=0){
      std::istringstream iss(line);
      iss >> dest >> source >> range;
      maps_between_two_types.push_back({dest, source, range});
      std::getline(file,line);
    }
    allmaps.push_back(maps_between_two_types);
  }

  size_t score = std::numeric_limits<size_t>::max();
  size_t val=0;
  for(const auto& infopair: seedinfo) {
    size_t start = infopair.first;
    size_t end = start + infopair.second;
    if(val>=end){ // if val is already larger than or euqal to the end of the new domain, we can
      // skip it since the correponding value was already passed through all the maps
      continue;
    } else if (val>start) { // if val is larger than the start of the domain, but smaller than the
      // end of the previous domain we can move the starting point
      start = val;
    }
    std::cout << val << std::endl;
    for (size_t i=start; i<=end; i++) {
      val = i;
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
  }
  std::cout << score << std::endl;
}


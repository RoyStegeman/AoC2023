#include<iostream>
#include<fstream>
#include <ostream>
#include<vector>
#include<string>
#include <sstream>

int main () {
  std::ifstream file("input.txt");

  size_t score = 0;

  std::string line;
  while (std::getline(file,line)) {

    // remove the info before the colon since we don't need it
    size_t colon_pos = line.find(':');
    line.erase(0,colon_pos+1);

    // get string with numbers before and after pipe symbol
    size_t pipe_pos = line.find('|');
    std::string winning_str = line.substr(0,pipe_pos);
    std::string my_str = line.substr(pipe_pos+1);

    // parse integers from the strings above and store them in two vectors of ints
    std::vector<int> winning_nrs;
    int number;
    std::istringstream winning_iss(winning_str);
    while(winning_iss >> number) {
      winning_nrs.push_back(number);
    }
    std::vector<int> my_nrs;
    std::istringstream my_iss(my_str);
    while(my_iss >> number) {
      my_nrs.push_back(number);
    }
    size_t card_score = 0;
    for (size_t i=0; i<my_nrs.size(); i++ ) {
      for (size_t j=0; j<winning_nrs.size(); j++ ) {
        if(my_nrs[i]==winning_nrs[j]) {
          if(card_score==0){card_score=1;}
          else{card_score *= 2;}
        }
      }
    }
    score += card_score;
  }
  std::cout << score << std::endl;
}

#include <cstddef>
#include<iostream>
#include<fstream>
#include <ostream>
#include<vector>
#include<string>
#include <sstream>

// keep track of the score with a global variable
size_t score = 0;

// recursively go through all cards collected when starting from a given point
void number_of_new_cards(size_t start, const std::vector<size_t> &n_matching_numbers) {
  size_t new_cards = n_matching_numbers[start];
  score += new_cards;
  if(new_cards!=0) {
    for(size_t i=1; i<=new_cards; i++) {
      int cardnr = start+i;
      number_of_new_cards(cardnr, n_matching_numbers);
    }
  }
}

int main () {
  std::ifstream file("input.txt");

  // get number of matching nubmer (and thus new scratschards) for each scratchcard
  // and put them in a vector for later use
  std::vector<size_t> n_matching_numbers;
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

    // loop over the vectors to get the amount of matching numbers in each scratchcard
    size_t n_match_per_card = 0;
    for (size_t i=0; i<my_nrs.size(); i++ ) {
      for (size_t j=0; j<winning_nrs.size(); j++ ) {
        if(my_nrs[i]==winning_nrs[j]) {
          n_match_per_card += 1;
        }
      }
    }
    n_matching_numbers.push_back(n_match_per_card);
  }

  for(size_t i=0; i<n_matching_numbers.size(); i++) {
    // since we start by scratching the original card we have in the beginning, we should already 
    // count that one here
    score += 1;
    // compute number of new scratchcards won from the original starting card 
    number_of_new_cards(i, n_matching_numbers);
  }

  std::cout << score << std::endl;
}

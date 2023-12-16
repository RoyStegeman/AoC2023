#include <fstream>
#include <iostream>
#include <list>
#include <regex>



int main() {
  std::vector<std::string> reference_vec  {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  std::ifstream file("input.txt");

  // loop over all the rows of the provided input
  std::string line;
  int totalsum=0;
  while (std::getline(file, line)) {
    // to keep track of all the numbers we encouter
    std::vector<int> numbers;

    // loop over every character in every line
    for(int i=0; i<line.size(); i++){
      char c = line[i];

      // check if the character is a digit from '0' to 9'
      if (c>= '0' && c <='9') {
        numbers.push_back(c- '0');
      }

      // check if the character is the start of a word present in `reference_vec`
      for(int j=0; j<reference_vec.size(); j++){
        std::string word = reference_vec[j];
        if (line.size() >= i + word.size()) {
          if (line.substr(i, word.size()) == word) {
            numbers.push_back(j+1);
          }
        }
      }
    }

    totalsum += 10*numbers[0]+numbers.back();
  }

  file.close();

  return 0;
}

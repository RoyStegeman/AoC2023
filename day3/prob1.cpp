#include<iostream>
#include<fstream>
#include<vector>
#include<string>


bool look_around(int row, int col, const std::vector<std::string>& filecontent) {
  // checks around the coordinates to see there is a symbol that's not a dot or integer
  bool has_symbol = false;
  size_t ncols = filecontent[0].length();
  size_t nrows = filecontent.size();

  // loop over neighbouring coordinates
  for(int i =-1; i <2; i++) {
    for(int j =-1; j <2; j++) {
      // only check existing coordinates
      if(-1<row+i && row+i<nrows && -1<col+j && col+j<nrows ){
        if(col+j == 139) {
        }
        char neighbour = filecontent[row+i][col+j];
        if(!isdigit(neighbour) && neighbour != '.') {
          has_symbol = true;
        }
      }
    }
  }
  return has_symbol;
}

int main() {

  // get linelength
  std::ifstream file("input.txt");
  std::string line;

  // store file content in vector for easy accessing based on coordinates later
  std::vector<std::string> filecontent;
  while(std::getline(file, line)) { 
    filecontent.push_back(line);
  }
  file.close();

  int row = 0;
  int sum = 0;
  // loop over lines and collect location and value of all integers
  for(const auto& line: filecontent) {
    // has symbol denotes whether the number has a symbol next to it and should count towards the sum
    // the digit string is used to instruct how long digits should be kept in memory to be able to 
    // construct the full number fromt the individual digits
    std::string digit = "reset";
    bool has_symbol = false;
    for(size_t col = 0; col < line.length()+1; col++) {
      char c = line[col];
      if (col == line.length()+1) {
          if(isdigit(digit[0])) {
            // if it has a symbol, add it to the sum
            if(has_symbol) {
              sum += std::stoi(digit);
            }
          }
      } else {
        if(isdigit(c)) {
          // if one of the digits has  symbol, it should be kept as true
          if(!has_symbol) {has_symbol=look_around(row, col, filecontent);}
          if(digit=="reset") {
            digit = c;
          } else {
            digit.push_back(c);
          }
        } else {
          // finish handling the last digit
          if(isdigit(digit[0])) {
            // if it has a symbol, add it to the sum
            if(has_symbol) {
              sum += std::stoi(digit);
            }
            // reset these to signify that the previous character was not a digit
            has_symbol = false;
            digit = "reset";
          }
        }
      }
    }
    row += 1;
  }

  std::cout << sum << std::endl;

  return 0;
}

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<utility>

bool check_two_numbers(int row, int col, const std::vector<std::string> &filecontent) {
  size_t nrows = filecontent.size();
  size_t ncols = filecontent[0].length();
  std::vector<std::pair<int, int>> digitcoords;
  bool is_a_gear = false;

  for(int i=-1; i<=1; i++) {
    for(int j=-1; j<=1; j++) {
      if(row+i>=0 && col+j>=0 && row+i<nrows && col+j<ncols) {
        if(isdigit(filecontent[row+i][col+j])) {
          digitcoords.push_back(std::make_pair(row+i, col+j));
        }
      }
    }
  }
  if(digitcoords.size()>=2) {
    for(int i=0; i<digitcoords.size(); i++) {
      for(int j=0; j<digitcoords.size(); j++) {
        if(digitcoords[i].first != digitcoords[j].first){
          // if the digits are on different rows, they are not part of the same number
          is_a_gear = true;
        } else if (std::abs(digitcoords[i].second-digitcoords[j].second)>=1 &&
          !isdigit(
            filecontent[digitcoords[i].first][(digitcoords[i].second+digitcoords[j].second)/2]
          )
        ) {
          // if the coordinates are on the same row but not next to eachother and 
          // inbetween is also not a digit, they are two separete numbers
          is_a_gear = true;
        }
      }
    }
  }
  if (is_a_gear) {std::cout << col << ' ' << row << std::endl;}
  return is_a_gear;
}

int compute_gear_value(int row, int col, const std::vector<std::string> &filecontent) {
  size_t nrows = filecontent.size();
  size_t ncols = filecontent[0].length();
  for (size_t i=row-1; i<=row+1 ; i++) {
    for (size_t j=col-1; j<=col+1; j++) {
      if (j>=0 && i>=0 && i<nrows && j<ncols) {
        
      }
    }
  }
}

int check_gear_value(int row, int col, const std::vector<std::string> &filecontent) {
  int val = 0;
  bool is_a_gear = check_two_numbers(row, col, filecontent);
  // if the position corresponds to a star indicating a gear, we want to compute
  // it's value
  if(is_a_gear) {
    val = compute_gear_value(row, col, filecontent);
  }
  return val;
}

int main () {
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
    for(size_t col = 0; col < line.length()+1; col++) {
      const char c = line[col];
      if(c=='*'){
        sum += check_gear_value(row, col, filecontent);
      }
    }
    row += 1;
  }
  std::cout << sum << std::endl;
}


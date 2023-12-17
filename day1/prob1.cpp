#include <fstream>
#include <iostream>

int main() {
  // Open the text file
  std::ifstream file("input.txt");

  std::string firstnumber;
  std::string lastnumber;
  int totalsum = 0;
  std::string line;
  // loop over all the rows of the provided input
  while (std::getline(file, line)) {
    firstnumber = lastnumber = "reset";
    for (int i = 0; i < line.size(); i++) {
      if (isdigit(line[i])) {
        if (firstnumber == "reset") {
          firstnumber = line[i];
        } else {
          lastnumber = line[i];
        }
      }
    }
    // if there is only a single integer in the line
    if (lastnumber == "reset") {
      lastnumber = firstnumber;
    }
    totalsum += std::stoi(firstnumber + lastnumber);
  }

  std::cout << "The answer is: " << totalsum << std::endl;

  // Close the file
  file.close();

  return 0;
}

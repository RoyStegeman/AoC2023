#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

int main() {

  std::ifstream file("input.txt");

  // to keep track of the accumulative power of the cubes in each of the games
  int gamesum = 0;

  std::string line;
  int gamenr = 0;
  while (std::getline(file, line)) {
    gamenr++;

    // remove the "Game [nr]:" from the string
    size_t colonpos = line.find(':');
    line.erase(0, colonpos + 1);

    // use stringstream to split the input string
    std::istringstream iss(line);
    std::string token;
    int cubespower = 1;
    std::map<std::string, int> colorcounts {
      {"red",0}, { "green",0}, {"blue",0}
    };
    while (std::getline(iss, token, ';')) {
      std::istringstream gamestream(token);
      std::string color;
      int count;

      // parse each color and count in a game
      while (gamestream >> count >> color) {
        // if the colostring contains a trailing comma, remove it
        if (color.back() == ',') {
          color.pop_back();
        }
        // keep track of the largest number of cubes of a given color drawn in a 
        // game
        if (colorcounts[color] < count) {
          colorcounts[color] = count;
        }
      }
    }

    // compute the power of a set of cubes
    for (const auto& entry : colorcounts) {
      cubespower *= entry.second;
    }
    gamesum += cubespower;
  }

  // print final answer
  std::cout << gamesum << std::endl;

  return 0;
}
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

int main() {

  std::ifstream file("input.txt");

  // keep track of the sum of the IDs of games that are possible given the 
  // limited number of cubes for each color
  int gamesum = 0;

  std::string line;
  int gamenr = 0;
  while (std::getline(file, line)) {
    gamenr++;

    // remove the "Game [nr]:" from the string
    size_t colonpos = line.find(':');
    line.erase(0, colonpos + 1);

    // create a map from color to number of cubes available of that color
    std::map<std::string,int> cubespercolor {
      {"red",12}, { "green",13}, {"blue",14}
    };

    // use stringstream to split the input string
    std::istringstream iss(line);
    std::string token;
    bool gameispossible = true;
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
        if(cubespercolor[color] < count) {
          gameispossible = false;
        }
      }
    }
    if (gameispossible) {
      gamesum += gamenr;
    }
  }

  // print final answer
  std::cout << gamesum << std::endl;

  return 0;
}
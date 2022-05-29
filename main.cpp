#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdio.h>
// #include "engine/objects/AbstractObjects.cpp"
// #include "engine/objects/Eats.cpp"
// #include "engine/objects/Player.cpp"
// #include "engine/objects/Scene.cpp"
// #include "engine/objects/ScorePoints.cpp"
// #include "engine/objects/Timer.cpp"
// #include "engine/objects/Walls.cpp"
// #include "engine/Render.cpp"
// #include "engine/Games.cpp"
// #include "menu.cpp"

using namespace std;

int main() {
  
  while () {
     cout << ch;
  }
  return 0;
}

int main(void) {
    setlocale(LC_ALL, "");
    char ch;
    while(true) {
        if ((ch = std::cin.get()) != 27) {
            break;
        }
        Menu menu;
        menu.showMenu(ch);
    }
    return 0;
}
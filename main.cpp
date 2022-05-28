#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "engine/objects/AbstractObjects.cpp"
#include "engine/objects/Eats.cpp"
#include "engine/objects/Player.cpp"
#include "engine/objects/Scene.cpp"
#include "engine/objects/ScorePoints.cpp"
#include "engine/objects/Timer.cpp"
#include "engine/objects/Walls.cpp"
#include "engine/Render.cpp"
#include "engine/Games.cpp"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");
    Games game;
    game.play();
    return 0;
}
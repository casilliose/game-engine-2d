#include <iostream>
#include <string>
#include <vector>
#include "engine/objects/AbstractObjects.cpp"
#include "engine/objects/Eats.cpp"
#include "engine/objects/Empty.cpp"
#include "engine/objects/Player.cpp"
#include "engine/objects/Scene.cpp"
#include "engine/objects/ScorePoints.cpp"
#include "engine/objects/Timer.cpp"
#include "engine/objects/Walls.cpp"
#include "engine/Render.cpp"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");
    // std::cout << "\033[36m Hello World ! \033[0m" << std::endl;
    Scene scene(100, 100);
    Empty empty(1, 1, false, " ");
    AbstractObjects* p;
    p = &empty;
    scene.setItemMap(1, 1, p);
    Render render(scene);
    render.Write();
    return 0;
}
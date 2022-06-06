#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <fcntl.h>
#include <algorithm>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define CLEAR u8"\033[2J\033[1;1H" /* clear console */

#include "engine/objects/AbstractObjects.cpp"
#include "engine/objects/Eats.cpp"
#include "engine/objects/Player.cpp"
#include "engine/objects/Scene.cpp"
#include "engine/objects/ScorePoints.cpp"
#include "engine/objects/Timer.cpp"
#include "engine/objects/Walls.cpp"
#include "engine/objects/Inedible.cpp"
#include "engine/Render.cpp"
#include "engine/Menu.cpp"
#include "engine/Games.cpp"

using namespace std;

struct termios saved_attributes;

void reset_input_mode (void)
{
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode (void)
{
    struct termios tattr;
    char *name;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO))
    {
        fprintf (stderr, "Not a terminal.\n");
        exit (EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 2;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

int main(void) {
    setlocale(LC_ALL, "");
    Games game;
    set_input_mode();
    while(true) {
        game.play();
    }
    return EXIT_SUCCESS;
}

# game-engine-2d

Name Game "LionFeeding"

Engine Developer by Igor Branitsky

Procces game
You are playing as a lion, you can moving with keypress
up, down, left, right in room, you target collect more eats,
if your lion wiil be hungret you game over.
Eats will random add on scene, then you deal with food
game added score points in check
Then time is over game also over
and you score points show you

# Technical details

The App Graphic in ANSI art
because i use only linux OC and clear C++

2D game engine for writen in CLI
coordinate system, X and Y axes

We have in game, scene with games objects: timer countdown,
score points, walls, player, eats, menu

We have in game functions:
New Game
End Game
Move player in room
Add points to score point
Timer countdown
Random add eats in scene
Render Objects on Scene
Add time to time countdown

# How build App

for compiler in gcc
you need run this command
g++ -o main main.cpp

for run app you need run this command
./main

# This is block with ANSI ART CODE AND UNICODE SYMBOLS

for color out put in console and size fonts
//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
> #define RESET   "\033[0m" \n
> #define BLACK   "\033[30m"      /* Black */ \n
> #define RED     "\033[31m"      /* Red */ \n
> #define GREEN   "\033[32m"      /* Green */ \n
> #define YELLOW  "\033[33m"      /* Yellow */ \n
> #define BLUE    "\033[34m"      /* Blue */ \n
> #define MAGENTA "\033[35m"      /* Magenta */ \n
> #define CYAN    "\033[36m"      /* Cyan */ \n
> #define WHITE   "\033[37m"      /* White */ \n
> #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */ \n
> #define BOLDRED     "\033[1m\033[31m"      /* Bold Red */ \n
> #define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */ \n
> #define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */ \n
> #define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */ \n
> #define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */ \n
> #define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */ \n
> #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */ \n


I used this icon from Unicode for games
eats
🍅
🍓
🍐
🍒
🍍
🥩
player
🐆
walls
⬜ ⬛
timer
⏳
score
🏁
🍄
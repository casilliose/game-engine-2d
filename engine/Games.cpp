class Games
{
    private:
        bool startGame = false;
        int difficulty = 1;
    public:
        Games(int difficulty)
        {
            this->difficulty = difficulty;
        }

        void play()
        {
            if (!this->startGame) {
                this->newGame();
                this->startGame = true;
                return;
            }
        }

        void newGame()
        {
            Scene scene(25, 50);
            Walls wallWhite(1, 1, true, "⬜");
            AbstractObjects* wh;
            wh = &wallWhite;
            Walls wallBlack(1, 1, true, "⬛");
            AbstractObjects* wb;
            wb = &wallBlack;
            int xMax = scene.getSizeX() - 1;
            int yMax = scene.getSizeY() - 1;
            for (int y = 0; y < yMax; y++)
            {
                scene.setItemMap(0, y, wb);
                scene.setItemMap(xMax, y, wb);
            }
            for (int x = 0; x <= xMax; x++)
            {
                scene.setItemMap(x, 0, wh);
                scene.setItemMap(x, yMax, wh);
            }

            Player player(xMax / 2, yMax / 2, true, "🐆");
            AbstractObjects* p;
            p = &player;
            scene.setItemMap(player.getCoordinatX(), player.getCoordinatY(), p);

            Eats eatCherry(1, 1, false, "🍒");
            AbstractObjects* eatC;
            eatC = &eatCherry;
            scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatC);

            Eats eatTomato(1, 1, false, "🍅");
            AbstractObjects* eatT;
            eatT = &eatTomato;
            scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatT);

            Eats eatStrawberry(1, 1, false, "🍓");
            AbstractObjects* eatS;
            eatS = &eatStrawberry;
            scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatS);

            Eats eatPear(1, 1, false, "🍐");
            AbstractObjects* eatP;
            eatP = &eatPear;
            scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatP);

            Eats eatPineapple(1, 1, false, "🍍");
            AbstractObjects* eatPin;
            eatPin = &eatPineapple;
            scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatPin);

            Eats eatMeat(1, 1, false, "🥩");
            AbstractObjects* eatM;
            eatM = &eatMeat;
            scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatM);

            Render render(scene);
            render.Write();
        }
        
        int getRandomCoordinatsX(int sizeX)
        {
            std::random_device random_device; // Источник энтропии.
            std::mt19937 generator(random_device()); // Генератор случайных чисел.
            // (Здесь берется одно инициализирующее значение, можно брать больше)
            std::uniform_int_distribution<> distribution(2, sizeX - 2); // Равномерное распределение [10, 20]
            return distribution(generator); // Случайное число.
        }

        int getRandomCoordinatsY(int sizeY)
        {
            std::random_device random_device; // Источник энтропии.
            std::mt19937 generator(random_device()); // Генератор случайных чисел.
            // (Здесь берется одно инициализирующее значение, можно брать больше)
            std::uniform_int_distribution<> distribution(2, sizeY - 2); // Равномерное распределение [10, 20]
            return distribution(generator); // Случайное число.
        }
};
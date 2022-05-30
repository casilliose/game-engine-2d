class Games
{
    private:
        bool isStartGame = false;
        int difficulty = 0;
        Scene scene;
        Player player;
        Timer timer;
        ScorePoints scorePoint;
        time_t currentTime;
        int previewTime = 0;

    public:
        void play()
        {
            char c;
            if (!this->isStartGame) {
                Menu menu;
                menu.showMenu();
                read (STDIN_FILENO, &c, 1);
                switch (c) {
                    case '1':
                        menu.showDifficulty();
                        read (STDIN_FILENO, &c, 1);
                        switch (c) {
                            case '1':
                                this->difficulty = 1;
                            break;
                            case '2':
                                this->difficulty = 2;
                            break;
                            case '3':
                                this->difficulty = 3;
                            break;
                            case '4':
                                cout << CLEAR;
                                return;
                            break;
                            default:
                                cout << BOLDRED << "You enter number is mistake, try to enter" << RESET << endl;
                                return;
                            break;
                        }
                        menu.showRules();
                        read (STDIN_FILENO, &c, 1);
                        this->newGame();
                        this->isStartGame = true;
                    break;
                    case '2':
                        exit(0);
                    break;
                    default:
                        cout << BOLDRED << "You enter number is mistake, try to enter" << RESET << endl;
                    break;
                }
                return;
            }

            this->nextStep();
        }

        void nextStep()
        {
            char c;
            read (STDIN_FILENO, &c, 1);
            int newCoordinatY = this->player.getCoordinatY();
            int newCoordinatX = this->player.getCoordinatX();
            switch (c)
            {
                case 'w':
                    newCoordinatY++;
                break;
                case 's':
                    newCoordinatY--;
                break;
                case 'd':
                    newCoordinatX--;
                break;
                case 'a':
                    newCoordinatX++;
                break;
            }
            int delTime = time(0) - this->currentTime - this->previewTime;
            this->timer.setTime(this->timer.getTimeGame() - delTime);
            if (this->timer.getTimeGame() <= 0) {
                cout << CLEAR;
                cout << "Game is Over \n You score point : " << BOLDYELLOW << this->scorePoint.getPoints();
                this->isStartGame = false;
                return;
            }
            this->previewTime = delTime;
            cout << CLEAR;
            this->timer.print();
            cout << "     ";
            this->scorePoint.print();
            cout << endl << endl;
            Render render(this->scene);
            render.Write();
        }

        void newGame()
        {
            cout << CLEAR;
            int sceneX = 25;
            int sceneY = 50;
            int countEats = 10;
            int countInedible = 2;
            int timeCnock = 120;
            int factor = 3;
            switch (this->difficulty) {
                case 2:
                    sceneX = 35;
                    sceneY = 75;
                    countEats = 7;
                    countInedible = 2;
                    timeCnock = 60;
                    factor = 2;
                break;
                case 3:
                    sceneX = 50;
                    sceneY = 100;
                    countEats = 5;
                    countInedible = 10;
                    timeCnock = 30;
                    factor = 1;
                break;
            }
            
            Scene scene(sceneX, sceneY);
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
            this->player = player;

            for (int i = 0; i <= countEats; i++) {
                int rendEat = this->getRandomEatType(countEats);
                switch (rendEat)
                {
                    case 1:
                    {
                        Eats* cherry = new Eats(1, 1, false, "🍒");
                        cherry->setScorePoints(factor * 1);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), cherry);
                    }
                    break;
                    case 2:
                    {
                        Eats* eatTomato = new Eats(1, 1, false, "🍅");
                        eatTomato->setScorePoints(factor * 2);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatTomato);
                    }
                    break;
                    case 3:
                    {
                        Eats* eatStrawberry = new Eats(1, 1, false, "🍓");
                        eatStrawberry->setScorePoints(factor * 3);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatStrawberry);
                    }
                    break;
                    case 4:
                    {
                        Eats* eatPear = new Eats(1, 1, false, "🍐");
                        eatPear->setScorePoints(factor * 4);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatPear);
                    }
                    break;
                    case 5:
                    {
                        Eats* eatPineapple = new Eats(1, 1, false, "🍍");
                        eatPineapple->setScorePoints(factor * 5);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatPineapple);
                    }
                    break;
                    case 6:
                    {
                        Eats* eatMeat = new Eats(1, 1, false, "🥩");
                        eatMeat->setScorePoints(factor * 1);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatMeat);
                    }   
                    break;
                    default:
                    {
                        Eats* eatCherry = new Eats(1, 1, false, "🍒");
                        eatCherry->setScorePoints(factor * 1);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatCherry);
                    }
                    break;
                }
            }

            for (int i = 1; i <= countInedible; i++) {
                AbstractObjects* amanita = new Inedible(1, 1, false, "🍄");
                scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), amanita);
            }
            
            this->scene = scene;

            Timer timer;
            timer.setTime(timeCnock);
            timer.setView("⏳");
            this->timer = timer;
            timer.print();

            cout << "     ";

            ScorePoints scorePoints;
            scorePoint.setView("🏁");
            this->scorePoint = scorePoint;
            scorePoint.print();
            
            cout << endl << endl;

            Render render(this->scene);
            render.Write();
            sleep(1);
            this->currentTime = time(0);
        }

        int getRandomEatType(int countEats)
        {
            std::random_device random_device; // Источник энтропии.
            std::mt19937 generator(random_device()); // Генератор случайных чисел.
            // (Здесь берется одно инициализирующее значение, можно брать больше)
            if (countEats >= 10) {
                std::uniform_int_distribution<> distribution(3, 6);
            } else if (countEats >= 7) {
                std::uniform_int_distribution<> distribution(2, 5);
            } else {
                std::uniform_int_distribution<> distribution(1, 3);
            }
            std::uniform_int_distribution<> distribution(1, 6); // Равномерное распределение [10, 20]
            return distribution(generator); // Случайное число.
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
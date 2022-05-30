class Games
{
    private:
        bool isStartGame = false;
        int difficulty = 0;
        Scene scene;
        Player* player;
        Timer timer;
        ScorePoints scorePoint;
        time_t startTime;
        time_t currentTime;
        int factor;

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
            this->currentTime = time(0);
            int delTime = (this->currentTime - this->startTime);
            this->timer.setTime(this->timer.getTimeGame() - delTime);
            if (this->timer.getTimeGame() <= 0) {
                cout << CLEAR;
                cout << "Game is Over \n You score point : " << BOLDYELLOW << this->scorePoint.getPoints() << endl;
                this->isStartGame = false;
                cout << "Try to now, please press key Enter for exit cntr+z" << endl;
                read (STDIN_FILENO, &c, 1);
                return;
            }

            read (STDIN_FILENO, &c, 1);
            int newCoordinatY = this->player->getCoordinatY();
            int newCoordinatX = this->player->getCoordinatX();
            int previewY = this->player->getCoordinatY();
            int previewX = this->player->getCoordinatX();
            switch (c)
            {
                case 'd':
                    if ((newCoordinatY + 1) < this->scene.getSizeY() - 1) {
                        newCoordinatY++;
                    } else {
                        return;
                    }
                break;
                case 'a':
                    if ((newCoordinatY - 1) > 0) {
                        newCoordinatY--;
                    } else {
                        return;
                    }
                break;
                case 's':
                    if ((newCoordinatX + 1) < this->scene.getSizeX() - 1) {
                        newCoordinatX++;
                    } else {
                        return;
                    }
                break;
                case 'w':
                    if ((newCoordinatX - 1) > 0) {
                        newCoordinatX--;
                    } else {
                        return;
                    }
                break;
            }
            auto item = this->scene.getByCoordinat(newCoordinatX, newCoordinatY);
            if ((bool)item) {
                if (item->getTypeObject() == 3) {
                    this->scorePoint.addPoints(item->getScorePoints());
                    for(int i = 1; i < 3; i++) {
                        this->scene.setItemMap(
                            this->getRandomCoordinatsX(this->scene.getSizeX()), 
                            this->getRandomCoordinatsY(this->scene.getSizeY()), 
                            this->getRandomEats(10)
                        );
                    }
                } else if (this->scorePoint.getPoints() > 0 && item->getTypeObject() == 5) {
                    this->scorePoint.rmPoints(10);
                    if (this->scorePoint.getPoints() > 10) {
                        AbstractObjects* amanita = new Inedible(1, 1, false, "🍄");
                        scene.setItemMap(
                            this->getRandomCoordinatsX(this->scene.getSizeX() - 1),
                            this->getRandomCoordinatsY(this->scene.getSizeY() - 1), 
                            amanita
                        );
                    }
                }
            }
            this->scene.removeItemMap(previewX, previewY);
            this->player->setCoordinats(newCoordinatX, newCoordinatY);
            this->scene.setItemMap(newCoordinatX, newCoordinatY, this->player);
            cout << CLEAR;
            this->timer.print();
            cout << "     ";
            this->scorePoint.print();
            cout << endl << endl;
            Render render(this->scene);
            render.Write();
            this->startTime = time(0);
        }

        void newGame()
        {
            cout << CLEAR;
            int sceneX = 25;
            int sceneY = 50;
            int countEats = 10;
            int countInedible = 2;
            int timeCnock = 120;
            this->factor = 3;
            switch (this->difficulty) {
                case 2:
                    sceneX = 35;
                    sceneY = 75;
                    countEats = 7;
                    countInedible = 2;
                    timeCnock = 60;
                    this->factor = 2;
                break;
                case 3:
                    sceneX = 50;
                    sceneY = 100;
                    countEats = 5;
                    countInedible = 10;
                    timeCnock = 30;
                    this->factor = 1;
                break;
            }
            
            Scene scene(sceneX, sceneY);
            Walls* wallWhite = new Walls(1, 1, true, "⬜");
            Walls* wallBlack = new Walls(1, 1, true, "⬛");
            int xMax = scene.getSizeX() - 1;
            int yMax = scene.getSizeY() - 1;
            for (int y = 0; y < yMax; y++)
            {
                scene.setItemMap(0, y, wallBlack);
                scene.setItemMap(xMax, y, wallBlack);
            }
            for (int x = 0; x <= xMax; x++)
            {
                scene.setItemMap(x, 0, wallWhite);
                scene.setItemMap(x, yMax, wallWhite);
            }

            Player* player = new Player(xMax / 2, yMax / 2, true, "🐆");
            scene.setItemMap(player->getCoordinatX(), player->getCoordinatY(), player);
            this->player = player;

            for (int i = 0; i <= countEats; i++) {
                int rendEat = this->getRandomEatType(countEats);
                switch (rendEat)
                {
                    case 1:
                    {
                        Eats* cherry = new Eats(1, 1, false, "🍒");
                        cherry->setScorePoints(this->factor * 1);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), cherry);
                    }
                    break;
                    case 2:
                    {
                        Eats* eatTomato = new Eats(1, 1, false, "🍅");
                        eatTomato->setScorePoints(this->factor * 2);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatTomato);
                    }
                    break;
                    case 3:
                    {
                        Eats* eatStrawberry = new Eats(1, 1, false, "🍓");
                        eatStrawberry->setScorePoints(this->factor * 3);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatStrawberry);
                    }
                    break;
                    case 4:
                    {
                        Eats* eatPear = new Eats(1, 1, false, "🍐");
                        eatPear->setScorePoints(this->factor * 4);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatPear);
                    }
                    break;
                    case 5:
                    {
                        Eats* eatPineapple = new Eats(1, 1, false, "🍍");
                        eatPineapple->setScorePoints(this->factor * 5);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatPineapple);
                    }
                    break;
                    case 6:
                    {
                        Eats* eatMeat = new Eats(1, 1, false, "🥩");
                        eatMeat->setScorePoints(this->factor * 1);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), this->getRandomCoordinatsY(yMax), eatMeat);
                    }   
                    break;
                    default:
                    {
                        Eats* eatCherry = new Eats(1, 1, false, "🍒");
                        eatCherry->setScorePoints(this->factor * 1);
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
            this->startTime = time(0);
        }

        Eats* getRandomEats(int countEats)
        {
            int rendEat = this->getRandomEatType(countEats);
            switch (rendEat)
            {
                case 1:
                {
                    Eats* eat = new Eats(1, 1, false, "🍒");
                    eat->setScorePoints(this->factor * 1);
                    return eat;
                }
                break;
                case 2:
                {
                    Eats* eat = new Eats(1, 1, false, "🍅");
                    eat->setScorePoints(this->factor * 2);
                    return eat;
                }
                break;
                case 3:
                {
                    Eats* eat = new Eats(1, 1, false, "🍓");
                    eat->setScorePoints(this->factor * 3);
                    return eat;
                }
                break;
                case 4:
                {
                    Eats* eat = new Eats(1, 1, false, "🍐");
                    eat->setScorePoints(this->factor * 4);
                    return eat;
                }
                break;
                case 5:
                {
                    Eats* eat = new Eats(1, 1, false, "🍍");
                    eat->setScorePoints(this->factor * 5);
                    return eat;
                }
                break;
                case 6:
                {
                    Eats* eat = new Eats(1, 1, false, "🥩");
                    eat->setScorePoints(this->factor * 1);
                    return eat;
                }   
                break;
                default:
                {
                    Eats* eat = new Eats(1, 1, false, "🍒");
                    eat->setScorePoints(this->factor * 1);
                    return eat;
                }
                break;
            }
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
class Games
{
    private:
        bool isStartGame = false;
        uint8_t difficulty = {0};
        Scene scene;
        Player* player;
        Player* player2;
        Timer timer;
        ScorePoints scorePoint;
        ScorePoints scorePointRival;
        time_t startTime;
        time_t currentTime;
        uint8_t factor;
        bool isPC;
        uint16_t countEats {10};
        uint16_t countInedible {2};
        uint16_t currentCountEats {0};
        uint16_t currentCountInedible {0};
        uint16_t countBomd {0};

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
                        isPC = true;
                        this->newGame();
                        this->isStartGame = true;
                    break;
                    case '2':
                        isPC = false;
                        this->newGame();
                        this->isStartGame = true;
                    break;
                    case '3':
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
            const uint8_t readByte {1};

            currentTime = time(0);
            uint16_t delTime = (currentTime - startTime);
            timer.setTime(timer.getTimeGame() - delTime);
            startTime = time(0);

            if (timer.getTimeGame() <= 0) {
                cout << CLEAR;
                if (scorePoint.getPoints() > scorePointRival.getPoints()) {
                    cout << "You Win !!!" << endl;
                } else if (scorePoint.getPoints() == scorePointRival.getPoints()) {
                    cout << "Draw" << endl;
                } else {
                    cout << "You is lost (((" << endl;
                }
                cout << "You score point : " << BOLDYELLOW << scorePoint.getPoints() << endl;
                cout << "Player 2 score point : " << BOLDBLUE << scorePointRival.getPoints() << endl;
                isStartGame = false;
                cout << "Press Enter for back to Menu or exit cntr+z" << endl;
                sleep(10);
                read (STDIN_FILENO, &c, readByte);
                return;
            }

            read (STDIN_FILENO, &c, readByte);

            uint16_t newCoordinatY = player->getCoordinatY();
            uint16_t newCoordinatX = player->getCoordinatX();
            uint16_t previewY = player->getCoordinatY();
            uint16_t previewX = player->getCoordinatX();

            switch (c)
            {
                case 'd':
                    if ((newCoordinatY + 1) < scene.getSizeY() - 1) {
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
                    if ((newCoordinatX + 1) < scene.getSizeX() - 1) {
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
             
            auto item = scene.getByCoordinat(newCoordinatX, newCoordinatY);
            bool canNextStep = true;
            if ((bool)item) {
                if (item->getTypeObject() == 2) {
                    canNextStep = false;
                }
                if (item->getTypeObject() == 7) {
                    countBomd--;
                    scorePointRival.rmPoints(item->getScorePoints());
                }
                if (item->getTypeObject() == 3) {
                    currentCountEats--;
                    scorePoint.addPoints(item->getScorePoints());
                    if (isPC) {
                        scene.removeEatForBot(newCoordinatX, newCoordinatY);
                    }
                } else if (scorePoint.getPoints() > 0 && item->getTypeObject() == 5) {
                    currentCountInedible--;
                    scorePoint.rmPoints(10);
                }
            }

            if (canNextStep) {
                scene.removeItemMap(previewX, previewY);
                player->setCoordinats(newCoordinatX, newCoordinatY);
                scene.setItemMap(newCoordinatX, newCoordinatY, player);
            }
            
            // player 2
            if (isPC) {
                uint16_t p2newCoordinatY = player2->getCoordinatY();
                uint16_t p2newCoordinatX = player2->getCoordinatX();
                uint16_t p2previewY = player2->getCoordinatY();
                uint16_t p2previewX = player2->getCoordinatX();
                std::tie(p2newCoordinatX, p2newCoordinatY) = scene.getNewCoordinatesForBot(p2previewX, p2previewY);
                auto item2 = scene.getByCoordinat(p2newCoordinatX, p2newCoordinatY);
                bool canNextStep2 = true;
                if ((bool)item2) {
                    if (item2->getTypeObject() == 2) {
                        canNextStep2 = false;
                    }
                    if (item2->getTypeObject() == 7) {
                        countBomd--;
                        scorePoint.rmPoints(item2->getScorePoints());
                    }
                    if (item2->getTypeObject() == 3) {
                        currentCountEats--;
                        scorePointRival.addPoints(item2->getScorePoints() * difficulty);
                        scene.removeEatForBot(p2newCoordinatX, p2newCoordinatY);
                    } else if (scorePointRival.getPoints() > 0 && item2->getTypeObject() == 5) {
                        currentCountInedible--;
                        scorePointRival.rmPoints(10);
                    }
                }
                if (canNextStep2) {
                    scene.removeItemMap(p2previewX, p2previewY);
                    player2->setCoordinats(p2newCoordinatX, p2newCoordinatY);
                    scene.setItemMap(p2newCoordinatX, p2newCoordinatY, player2);
                }
            } else {
                uint16_t p2newCoordinatY = player2->getCoordinatY();
                uint16_t p2newCoordinatX = player2->getCoordinatX();
                uint16_t p2previewY = player2->getCoordinatY();
                uint16_t p2previewX = player2->getCoordinatX();
                switch (c)
                {
                    case 'l':
                        if ((p2newCoordinatY + 1) < scene.getSizeY() - 1) {
                            p2newCoordinatY++;
                        } else {
                            return;
                        }
                    break;
                    case 'j':
                        if ((p2newCoordinatY - 1) > 0) {
                            p2newCoordinatY--;
                        } else {
                            return;
                        }
                    break;
                    case 'k':
                        if ((p2newCoordinatX + 1) < scene.getSizeX() - 1) {
                            p2newCoordinatX++;
                        } else {
                            return;
                        }
                    break;
                    case 'i':
                        if ((p2newCoordinatX - 1) > 0) {
                            p2newCoordinatX--;
                        } else {
                            return;
                        }
                    break;
                }
                auto item2 = scene.getByCoordinat(p2newCoordinatX, p2newCoordinatY);
                bool canNextStep2 = true;
                if ((bool)item2) {
                    if (item2->getTypeObject() == 2) {
                        canNextStep2 = false;
                    }
                    if (item2->getTypeObject() == 7) {
                        countBomd--;
                        scorePoint.rmPoints(item2->getScorePoints());
                    }
                    if (item2->getTypeObject() == 3) {
                        currentCountEats--;
                        scorePointRival.addPoints(item2->getScorePoints());
                    } else if (scorePointRival.getPoints() > 0 && item2->getTypeObject() == 5) {
                        currentCountInedible--;
                        scorePointRival.rmPoints(10);
                    }
                }
                if (canNextStep2) {
                    scene.removeItemMap(p2previewX, p2previewY);
                    player2->setCoordinats(p2newCoordinatX, p2newCoordinatY);
                    scene.setItemMap(p2newCoordinatX, p2newCoordinatY, player2);
                }
            }
            eatsAddToScene();
            // render
            cout << CLEAR;
            timer.print();
            cout << "     P1 ";
            scorePoint.print();
            cout << "     P2 ";
            scorePointRival.print();
            cout << endl << endl;
            Render render(scene);
            render.Write();
        }

        void eatsAddToScene()
        {
            if (currentCountEats < countEats) {
                for(size_t i = 1; i <= (countEats - currentCountEats); i++) {
                    scene.setItemMap(
                        getRandomCoordinatsX(scene.getSizeX()),
                        getRandomCoordinatsY(scene.getSizeY()),
                        getRandomEats(currentCountEats)
                    );
                }
                currentCountEats = countEats;
            }

            if (currentCountInedible < countInedible) {
                for(size_t i = 1; i <= (countInedible - currentCountInedible); i++) {
                    AbstractObjects* amanita = new Inedible(1, 1, false, "🍄");
                    scene.setItemMap(
                        getRandomCoordinatsX(scene.getSizeX() - 1),
                        getRandomCoordinatsY(scene.getSizeY() - 1), 
                        amanita
                    );
                }
                currentCountInedible = countInedible;
            }
            if (
                (!isPC && timer.getTimeGame() % 10 == 1) ||
                (isPC && difficulty > 1 && timer.getTimeGame() % 10 == 1)
            ) {
                if (countBomd <= 0) {
                    AbstractObjects* bomb = new Bomb(1, 1, false, "💣");
                    scene.setItemMap(
                        getRandomCoordinatsX(scene.getSizeX() - 1),
                        getRandomCoordinatsY(scene.getSizeY() - 1), 
                        bomb
                    );
                    countBomd = 1;
                }
            }
        }

        void newGame()
        {
            cout << CLEAR;
            uint16_t sceneX = 25;
            uint16_t sceneY = 50;
            
            uint16_t timeCnock = 120;
            factor = 3;
            if (!isPC) {
                difficulty = 2;
            }
            switch (difficulty) {
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
            currentCountEats = countEats;
            currentCountInedible = countInedible;

            Scene scene(sceneX, sceneY);
            Walls* wallWhite = new Walls(1, 1, true, "⬜");
            Walls* wallBlack = new Walls(1, 1, true, "⬛");
            uint16_t xMax = scene.getSizeX() - 1;
            uint16_t yMax = scene.getSizeY() - 1;
            for (size_t y = 0; y < yMax; y++)
            {
                scene.setItemMap(0, y, wallBlack);
                scene.setItemMap(xMax, y, wallBlack);
            }
            for (size_t x = 0; x <= xMax; x++)
            {
                scene.setItemMap(x, 0, wallWhite);
                scene.setItemMap(x, yMax, wallWhite);
            }

            Player* player = new Player(xMax / 2, yMax / 2, true, "🐆");
            scene.setItemMap(player->getCoordinatX(), player->getCoordinatY(), player);
            this->player = player;

            Player* player2 = new Player(xMax / 2, yMax / 2 + 1, true, "🦕");
            scene.setItemMap(player2->getCoordinatX(), player2->getCoordinatY(), player2);
            this->player2 = player2;

            for (size_t i = 0; i <= countEats; i++) {
                uint16_t rendEat = getRandomEatType(countEats);
                switch (rendEat)
                {
                    case 1:
                    {
                        Eats* cherry = new Eats(1, 1, false, "🍒");
                        cherry->setScorePoints(factor * 1);
                        scene.setItemMap(getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), cherry);
                    }
                    break;
                    case 2:
                    {
                        Eats* eatTomato = new Eats(1, 1, false, "🍅");
                        eatTomato->setScorePoints(factor * 2);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), eatTomato);
                    }
                    break;
                    case 3:
                    {
                        Eats* eatStrawberry = new Eats(1, 1, false, "🍓");
                        eatStrawberry->setScorePoints(this->factor * 3);
                        scene.setItemMap(getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), eatStrawberry);
                    }
                    break;
                    case 4:
                    {
                        Eats* eatPear = new Eats(1, 1, false, "🍐");
                        eatPear->setScorePoints(factor * 4);
                        scene.setItemMap(getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), eatPear);
                    }
                    break;
                    case 5:
                    {
                        Eats* eatPineapple = new Eats(1, 1, false, "🍍");
                        eatPineapple->setScorePoints(factor * 5);
                        scene.setItemMap(getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), eatPineapple);
                    }
                    break;
                    case 6:
                    {
                        Eats* eatMeat = new Eats(1, 1, false, "🥩");
                        eatMeat->setScorePoints(factor * 1);
                        scene.setItemMap(this->getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), eatMeat);
                    }   
                    break;
                    default:
                    {
                        Eats* eatCherry = new Eats(1, 1, false, "🍒");
                        eatCherry->setScorePoints(factor * 1);
                        scene.setItemMap(getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), eatCherry);
                    }
                    break;
                }
            }

            for (size_t i = 1; i <= countInedible; i++) {
                AbstractObjects* amanita = new Inedible(1, 1, false, "🍄");
                scene.setItemMap(getRandomCoordinatsX(xMax), getRandomCoordinatsY(yMax), amanita);
            }

            this->scene = scene;

            Timer timer;
            timer.setTime(timeCnock);
            timer.setView("⏳");
            this->timer = timer;
            timer.print();
            cout << "     P1 ";
            ScorePoints scorePoints;
            scorePoint.setView("🏁");
            this->scorePoint = scorePoint;
            scorePoint.print();
            cout << "     P2 ";
            ScorePoints scorePointRival;
            scorePointRival.setView("🏁");
            this->scorePointRival = scorePointRival;
            scorePointRival.print();
            cout << endl << endl;
            Render render(this->scene);
            render.Write();
            sleep(1);
            this->startTime = time(0);
        }

        Eats* getRandomEats(uint16_t countEats)
        {
            uint16_t rendEat = this->getRandomEatType(countEats);
            switch (rendEat)
            {
                case 1:
                {
                    Eats* eat = new Eats(1, 1, false, "🍒");
                    eat->setScorePoints(factor * 1);
                    return eat;
                }
                break;
                case 2:
                {
                    Eats* eat = new Eats(1, 1, false, "🍅");
                    eat->setScorePoints(factor * 2);
                    return eat;
                }
                break;
                case 3:
                {
                    Eats* eat = new Eats(1, 1, false, "🍓");
                    eat->setScorePoints(factor * 3);
                    return eat;
                }
                break;
                case 4:
                {
                    Eats* eat = new Eats(1, 1, false, "🍐");
                    eat->setScorePoints(factor * 4);
                    return eat;
                }
                break;
                case 5:
                {
                    Eats* eat = new Eats(1, 1, false, "🍍");
                    eat->setScorePoints(factor * 5);
                    return eat;
                }
                break;
                case 6:
                {
                    Eats* eat = new Eats(1, 1, false, "🥩");
                    eat->setScorePoints(factor * 1);
                    return eat;
                }   
                break;
                default:
                {
                    Eats* eat = new Eats(1, 1, false, "🍒");
                    eat->setScorePoints(factor * 1);
                    return eat;
                }
                break;
            }
        }

        uint16_t getRandomEatType(uint16_t countEats)
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
        
        uint16_t getRandomCoordinatsX(uint16_t sizeX)
        {
            std::random_device random_device; // Источник энтропии.
            std::mt19937 generator(random_device()); // Генератор случайных чисел.
            // (Здесь берется одно инициализирующее значение, можно брать больше)
            std::uniform_int_distribution<> distribution(2, sizeX - 2); // Равномерное распределение [10, 20]
            u_int16_t x;
            do {
                x = distribution(generator);
            } while(x == player->getCoordinatX() || x == player2->getCoordinatX());
            return x; // Случайное число.
        }

        uint16_t getRandomCoordinatsY(uint16_t sizeY)
        {
            std::random_device random_device; // Источник энтропии.
            std::mt19937 generator(random_device()); // Генератор случайных чисел.
            // (Здесь берется одно инициализирующее значение, можно брать больше)
            std::uniform_int_distribution<> distribution(2, sizeY - 2); // Равномерное распределение [10, 20]
            u_int16_t y;
            do {
                y = distribution(generator);
            } while (y == player->getCoordinatY() || y == player2->getCoordinatY());
            return y; // Случайное число.
        }
};

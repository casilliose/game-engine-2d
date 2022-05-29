class Menu
{
    public:
        int globalMenu = 0;
        int difficulty = 0;
        void showMenu(char ch)
        {
            cout<< u8"\033[2J\033[1;1H";
            cout << "\033[35mWelcom to \033[36mLionFeeding\033[0m" << endl;
            cout << "For selected input number on menu and press to enter" << endl;
            cout << "1. \033[36mStart New Game\033[0m" << endl;
            cout << "2. \033[32mLoad Game\033[0m" << endl;
            cout << "3. \033[31mExit\033[0m" << endl;
            cin >> this->globalMenu;
            switch (this->globalMenu) {
                case 1:
                    this->showDifficulty();
                break;
                case 2:
                    cout << "case2" << endl;
                break;
                case 3:
                    exit(0);
                break;
                default:
                    cout << "\033[1m\033[31mYou enter number is mistake, try to enter\033[0m" << endl;
                break;
            }
        }

        void showDifficulty()
        {
            cout<< u8"\033[2J\033[1;1H"; 
            cout << "Please option difficulty" << endl;
            cout << "1. \033[35mLow\033[0m" << endl;
            cout << "2. \033[35mMedium\033[0m" << endl;
            cout << "3. \033[35mHard\033[0m" << endl;
            cout << "4. \033[35mBack to Menu\033[0m" << endl;
            cin >> this->difficulty;
            switch (this->globalMenu) {
                case 1:
                    cout<< u8"\033[2J\033[1;1H"; 
                    cout << "case1" << endl;
                
                break;
                case 2:
                    cout<< u8"\033[2J\033[1;1H"; 
                    cout << "case2" << endl;
                break;
                case 3:
                    cout<< u8"\033[2J\033[1;1H"; 
                    cout << "case3" << endl;
                break;
                case 4:
                    cout<< u8"\033[2J\033[1;1H"; 
                    cout << "case4" << endl;
                break;
                default:
                    cout << "\033[1m\033[31mYou enter number is mistake, try to enter\033[0m" << endl;
                break;
            }
        }

        void showUploadFiles()
        {
            // std::string path = "path_to_directory";
            // for (auto & p : fs::directory_iterator(path))
            //     std::cout << p << std::endl;
        }
};
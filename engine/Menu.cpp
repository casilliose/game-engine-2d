class Menu
{
    public:
        Menu() = default;

        void showMenu()
        {
            cout << CLEAR;
            cout << MAGENTA << "Welcom to " << CYAN << "LionFeeding" << RESET << endl;
            cout << "For selected input number on menu and press to enter" << endl;
            cout << "1. " << CYAN << "Start Game" << RESET << endl;
            cout << "2. " << GREEN << "Exit" << RESET << endl;
        }

        void showDifficulty()
        {
            cout << CLEAR;
            cout << "Please option difficulty" << endl;
            cout << "1. " << GREEN << "Low" << RESET << endl;
            cout << "2. " << BLUE << "Medium" << RESET << endl;
            cout << "3. " << RED << "Hard" << RESET << endl;
            cout << "4. Back to Menu" << endl;
        }

        void showRules()
        {
            cout << CLEAR;
            cout << "You can moving with the help keypress w,a,d,s or arrow button and then keypress Enter button" << endl;
            cout << "You target collect as much as possible eats until the time is up" << endl;
            cout << "If you undestend rules, then keypress enter and start games" << endl;
        }
};

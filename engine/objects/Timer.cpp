class Timer
{
    private:
        int time {60};
        string view {""};

    public:
        Timer() = default;

        void print()
        {
            cout << view << " = " << time;
        }

        int getTimeGame()
        {
            return time;
        }

        void setTime(uint16_t time)
        {
            this->time = time;
        }

        void setView(string view)
        {
            this->view = view;
        }
};

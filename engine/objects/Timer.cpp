class Timer
{
    private:
        int time = 60;
        string view = "";

    public:
        Timer() = default;
        void print()
        {
            cout << this->view << " = " << this->time;
        }

        int getTimeGame()
        {
            return this->time;
        }

        void setTime(int time)
        {
            this->time = time;
        }

        void setView(string view)
        {
            this->view = view;
        }
};

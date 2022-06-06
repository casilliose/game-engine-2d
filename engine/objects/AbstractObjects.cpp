using namespace std;

class AbstractObjects
{   
    public:
        virtual void print() = 0;
        virtual uint16_t getScorePoints() = 0;

        void setCoordinats(uint16_t x, uint16_t y) {
            this->x = x;
            this->y = y;
        }

        uint16_t getCoordinatX() {
            return x;
        }

        uint16_t getCoordinatY() {
            return y;
        }

        void setView(string view) {
            this->view = view;
        }

        string getView() {
            return view;
        }

        void setSolid(bool solid) {
            this->solid = solid;
        }

        bool getSolid() {
            return solid;
        }

        uint16_t getTypeObject() {
            return type;
        }
        
    protected:
        uint16_t x;
        uint16_t y;
        bool solid;
        string view;
        uint16_t type;
};

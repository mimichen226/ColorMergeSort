// display.h 
#include <vector>
#include "color-rgb.h"

class DispBoard
{
    public:
        // Constructor
        DispBoard(int, int);
        // Destructor
        ~DispBoard();

        void set_depth_count(int, int, std::vector<Color>);
        int getsize();
        int getdepth();
        void print();
        void gfx_print();

    private:
        std::vector<std::vector<std::vector<Color>>> displayboard;
        int depth; 
        int size;
};

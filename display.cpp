// display.cpp

#include "display.h"
#include <iostream>
#include <math.h>
#include "gfx.h"
#include <unistd.h>

#define YSIZE 500
#define XSIZE 700

DispBoard::DispBoard(int d, int s)
{
    depth = d;
    size = s;

    std::vector<Color> c;


    // Depth
    for (int i = 0; i < depth; i++)
    {

    std::vector<std::vector<Color>> count;
        // Count
        for (int j = 0; j < pow(2,i); j++)
        {
            // Vector of colors
            count.push_back(c);;
        }
        displayboard.push_back(count);
    }
}

// Destructor
DispBoard::~DispBoard() { }

// Set color in display board given depth and count
void DispBoard::set_depth_count(int d, int c, std::vector<Color> v)
{
    displayboard[d][c] = v;
}

// Get size of originally vector of colors
int DispBoard::getsize()
{
    return size;
}

// Get depth of sorting
int DispBoard::getdepth()
{
    return depth;
}

// Print
void DispBoard::print()
{
    int i = 1, j;

    // Depth
    for (auto it = displayboard.begin(); it != displayboard.end(); it++)
    {
        j = 1;
        // Count for a depth
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {
            std::cout << "Depth: " << i << " Count: " << j << std::endl;

            // Vector of colors
            for (auto it3 = (*it2).begin(); it3 != (*it2).end(); it3++)
            {
                std::cout << (*it3).gethue() << " " ;
            }
            j++;
            std::cout << std::endl;
        }
        i++;
    }
}

void DispBoard::gfx_print()
{
    // Divide by depth + 1 so you have depth number of positions
    // ie. depth = 4: divide window height by 5 so first depth is on 
    // level 1/5, then 2/5, then 3/5, and then 4/5
    int y_position = YSIZE / (depth + 1);
    int i = 1, j;

    int x_pos = XSIZE / (size + 1);

    gfx_clear();

    gfx_color(255,255,255);
    gfx_text(XSIZE/8, YSIZE/10, "Merge Sort: O(n log(n))");
    char q[6] = "n = ";
    q[4] = size + '0';

    gfx_text(XSIZE/2, YSIZE/10, q);

    int x = x_pos;

    // Depth
    for (auto it = displayboard.begin(); it != displayboard.end(); it++)
    {
        j = 0;


        // Count for a depth
        for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++)
        {    
            // Check if vector of colors is empty
            if ((*it2).empty())
            {
                x +=x_pos;
            }
            // Not vector of colors is not empty
            else
            {
                // White separator bar
                gfx_color(255,255,255);
                gfx_line(x - x_pos/2, y_position * i - 10, x - x_pos/2, y_position * i + 10);

                // Vector of colors
                for (auto it3 = (*it2).begin(); it3 != (*it2).end(); it3++)
                {
                    Color blob = (*it3);
                    gfx_color(blob.getr(), blob.getg(), blob.getb());
                    gfx_circle( x, i * y_position, 10);
                    x += x_pos;
                }
                // White separator bar
                gfx_color(255,255,255);
                gfx_line(x - x_pos/2, y_position * i - 10, x - x_pos/2, y_position * i + 10);
            }
            j++;
        }
        i++;
        x =  x_pos;
    }
    gfx_flush();
    usleep(500000);
}

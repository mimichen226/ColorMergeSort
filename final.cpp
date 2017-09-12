#include <iostream>
#include <vector>
#include "gfx.h"
#include <unistd.h>
#include <math.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include "display.h"

#define XSIZE 700
#define YSIZE 500

using namespace std;


// ---------------------------------------------------------------------------
// ----------------------
// | FUNCTION PROTOTYPE | 
// ----------------------

void mergesort(vector<Color> &, int, vector<int> &, DispBoard &);
vector<Color>  merge(vector<Color> &, vector<Color> &, int, vector<int> &, DispBoard &);
int randomint(int);

// ---------------------------------------------------------------------------
// ----------------------
// |   MAIN FUNCTION    |
// ----------------------

int main()
{
    srand ( unsigned (time(0) ) );

    vector<Color> colordatabase = {
        Color(255,125,0),  // orange
        Color(0,0,255),    // blue
        Color(0,125,125),  // green blue
        Color(255,0,0),    // red
        Color(125,0,125),  // purple
        Color(255,255,0),  // yellow
        Color(125, 255,0), // green yellow
        Color(0, 255, 255), // light blue
        Color(255, 125, 239),
        Color(0,0,430)
    };

    char c = ' ';
    int size = 5; // default size

    gfx_open(XSIZE, YSIZE, "Merge Sort of Colors");

    while (c != 'q')
    {
        random_shuffle (colordatabase.begin(), colordatabase.end(), randomint);

        vector<Color> colors;

        // Put into the vector "colors" the number of elements chosen by user
        for (int i = 0; i < size; i++)
        {
            colors.push_back(colordatabase[i]);
        }

        // Determine depth
        int depth = 1;
        while (colors.size() > pow(2, depth - 1))
            depth++;

        DispBoard db(depth, colors.size());;

        db.set_depth_count(0,0,colors);
        db.gfx_print();
        
        // Vector whose index corresponds with the depth
        // Value of the element is the number of times the depth is called
        vector<int> count;

        // Call function merge sort
        mergesort(colors, -1, count, db);
        //db.print();

        // Display "DONE" to window
        gfx_color(255,255,255);
        gfx_text(XSIZE * 4 /5, YSIZE/10, "DONE!");
        gfx_flush();


        c = gfx_wait();
        if ( c == '2')
            size = 2;
        else if ( c == '3')
            size = 3;
        else if ( c== '4')
            size = 4;
        else if ( c == '5')
            size = 5;
        else if ( c == '6')
            size = 6;
        else if ( c == '7')
            size = 7;
        else if ( c == '8')
            size = 8;
        else if ( c == '9')
            size = 9;
    }
     
    return 0;
}

// ---------------------------------------------------------------------------
// -----------------------
// | FUNCTION DEFINITION |
// -----------------------

// Generate random number
int randomint(int i)
{ 
    return rand()%i;
}

// Mergesort divides vector into a two halves then calls merge sort on the new half vectors
// It then calls the function "merge" to merge the halves together 
void mergesort(vector<Color> &colors, int depth, vector<int> &count, DispBoard &db)
{
    depth++;
    cout << "Sorting: ";

    // Index of the vector "count" corresponds to the depth
    if (count.size() < depth + 1 ) // if index is less than depth, increase index
        count.push_back(0);


    bool first = false;
    if (count[depth] == 0)
        first = true;
    // To make the bottom stragglers in line with its upper parent
        // depth > 0 makes sure it's not the first row
        // count[depth] < count[depth - 1] -1 lines up circle to its upper parent
        // count[depth - 1] > 1 makes sure that this skips the first column
    // If this is the first time in depth
    while ((first) && (depth > 0) && (count[depth] < count[depth-1] -1 ) && (count[depth - 1] > 1))
        count[depth] += 1;

    // Not first time in depth (has to take into consideration that something is 
    // already in the depth)
     while ((!first) && (depth > 0) && (count[depth] <= count[depth-1] -1 ) && (count[depth - 1] > 1))
        count[depth] += 1;

    count[depth] += 1;

    cout << "times in depth " << depth << " : " << count[depth] << endl;

    db.set_depth_count(depth, count[depth] - 1, colors);

    db.gfx_print();

    /*gfx_line(XSIZE / (db.getsize() + 1) * count[depth], 
            YSIZE * (depth + 1) / (db.getdepth() + 1) + 10,
            XSIZE/ (db.getsize() + 1) * count[depth],
            YSIZE *( depth + 1) / (db.getdepth()  + 1) - 10);
    gfx_flush();*/


    // Base case: when the size of the vector is less than 2  
    if (colors.size() < 2)
        return;

    // Determine the middle index of old vector
    int middle;
    middle = colors.size() / 2;

    // Create two new vectors from old vector
    vector<Color> left;
    vector<Color> right;

    for (int i = 0; i < middle; i++)
    {
        left.push_back(colors[i]);
    }

    for (int i = middle; i < colors.size(); i++)
    {
        right.push_back(colors[i]);
    }

    // Recursively call the function "mergesort" on the two new vectors
    mergesort(left, depth, count, db);
    mergesort(right, depth, count, db);

    // Call the function "merge" to merge the halves
    colors = merge(left, right, depth, count, db);
}

// Returns a sorted vector given two sorted vectors 
vector<Color> merge(vector<Color> &l, vector<Color> &r, int depth, vector<int> &count, DispBoard &db)
{
    // i corresponds to the index of the left vector
    // j corresponds to the index of the right vector
    int i = 0, j = 0;

    vector<Color> sorted;

    // While not at the end of both vectors, compare values

    // COLOR SORTING ALGORITHM - USE HUES
    // http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/

    while ((i < l.size()) && (j < r.size()))
    {
       // Choose from the vector a lower hue
        if (r[j].gethue() <= l[i].gethue())
        {
            sorted.push_back(r[j]);
            j++;
        }
        else
        {
            sorted.push_back(l[i]);
            i++;
        }
    }

    // While there are still components in the "left" vector, append to 
    // vector "sorted"
    while (i < l.size())
    {
        sorted.push_back(l[i]);
        i++;
    }

    // While there are still components in the "right" vector, append to 
    // vector "sorted"
    while (j < r.size())
    {
        sorted.push_back(r[j]);
        j++;
    }

    cout << "Merged: ";

    cout << "times in depth " << depth << " : " << count[depth] << endl;

    db.set_depth_count(depth, count[depth] - 1, sorted);
    db.gfx_print();

    return sorted;
}

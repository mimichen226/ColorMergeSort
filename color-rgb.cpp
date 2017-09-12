// color-rgb.cpp
#include "color-rgb.h"
#include <iostream>

// Constructor
Color::Color()
{
    r = 255, g = 255, b = 255;
    hue = Color::gethue();
}

Color::Color(int red, int green, int blue)
{
    r = red, g = green, b = blue;
    hue = Color::gethue();
}

// Destructor
Color::~Color() { }

// Methods
void Color::setrgb(int red, int green, int blue)
{
    r = red, g = green, b = blue;
    hue = Color::gethue();
}

int Color::getr()
{
    return r;
}

int Color::getb()
{
    return b;
}
int Color::getg()
{
    return g;
}

int Color::getmaxrgb()
{
    // r is the max value
    if (( r >= g) && ( r >= b))
        return r;
    // g is the max value
    else if (( g >= b) && (g >= r))
        return g;
    else
        return b;
}

int Color::getminrgb()
{
    // r is the min value
    if (( r <= g) && ( r <=  b))
        return r;
    // g is the max value
    else if (( g <= b) && (g <= r))
        return g;
    else
        return b;
}

int Color::gethue()
{
    float R = r / 255. ;
    float G = g / 255. ;
    float B = b / 255. ;

    float  max, min;

    if (( R >= G) && (R >= B))
        max = R;
    else if (( G >= B ) && (G >= R))
        max = G;
    else
        max = B;

    if (( R <= G) && (R <= B))
        min = R;
    else if (( G <= B) && (G <= R))
        min = G;
    else
        min = B;

    int hue;

    if (R == max)
    {
        hue = ((G - B) / (max - min) )* 60;;
    }
    else if (G == max)
    {
        hue = (2 + (B - R) / (max - min) )* 60;
    }
    else
    {
        hue = (4 + (R - G) / (max - min) )* 60;
    }

    if (hue < 0)
    {
        hue += 360;
    }

    return hue;
}

void Color::print()
{
    std::cout << r << " " << g << " " << b << std::endl;
}


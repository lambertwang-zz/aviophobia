#pragma once
/*
 * Position class header
 *
 * Stores a position in the world
 */

#ifndef __POSITION_H__
#define __POSITION_H__

namespace av {

    class Position {
    private:
        // X position within the world
        int x;
        // Y position within the world
        int y; 

    public:
        // Create position at a specified location
        Position(int init_x, int init_y);

        // Default position at (0, 0)
        Position();

        // Sets the position's x value
        void setX(int new_x);
        // Return's the position's x value
        int getX() const;


        // Sets the position's y value
        void setY(int new_y);
        // Return's the position's y value
        int getY() const;

        // Sets the position's x and y values
        void setXY(int new_x, int new_y);
    };
} // End of namespace

#endif // __POSITION_H__

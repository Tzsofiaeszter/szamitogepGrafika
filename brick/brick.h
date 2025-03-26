#ifndef BRICK_H
#define BRICK_H

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Brick
{
	double a;
	double b;
	double zc;
} Brick;

/**
 * Set the data of the brick
 */
void set_brick_data(Brick* brick, double a, double b, double c);

/**
 * Calculate the area of the brick.
 */
double calc_brick_area(const Brick* brick);

#endif 

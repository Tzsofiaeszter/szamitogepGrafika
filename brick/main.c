#include "brick.h"
#include <math.h>

void set_circle_data(Brick* brick, double a, double b, double c)
{
	if (a > 0 && b > 0 && c > 0)
    {
        brick->a = a;
        brick->b = b;
        brick->c = c;
    }
    else{
        printf("Hibas adat!");
    }
}

double calc_volume(const Brick* brick)
{
	double vol =brick->a * brick->b * brick->c;
	return vol;
}

double calc_surface(const Brick* brick)
{
	double surface = brick->a * brick->b  + brick->a * brick->c +  brick->b * brick->c;
	return 2 * surface;
}

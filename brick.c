#include "brick.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Brick brick;
	
    set_brick_data(&brick, 5, 10, 8);
    double volume = calc_volume(&brick);
    double volume = calc_surface(&brick);
    
    
	printf("Brick volume: %lf\n", volume);
    printf("Brick surface: %lf\n", surface);

    if (brick.a == brick.b || brick.a == brick.c || brick.b == brick.c)
    {
       printf("A teglatestnek van negyzet alapu lapja.\n");
    }
    else{
        printf("A teglatestnek nincs negyzet alapu lapja.\n");
    }
    
	
	return 0;
}

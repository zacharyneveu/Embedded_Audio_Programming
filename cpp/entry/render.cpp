/*
 * Copyright (C) 2020 zach zachary.neveu@gmail.com
 */

#include <Bela.h>

// Return true if all goes well
bool setup(BelaContext *context, void *userData)
{
	int i = 2;
	float f = 0.1234;
	int values[5] = {5, 4, 3, 2, 1};

	for(int i=0; i<5; ++i)
	{
		rt_printf("Values[%d] is %d\n", i, values[i]);
	}

	return true;
}

// Triggered by audio interface interrupt
void render(BelaContext *context, void *userData)
{
}


void cleanup(BelaContext *context, void *userData)
{

}







#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "emokit.h"

int quit;
void cleanup(int i){
	fprintf(stdout,"Shutting down\n");
	quit=1; 
}

int main(int argc, char **argv)
{
	struct emokit_device* device;
	signal(SIGINT, cleanup); //trap cntrl c
    
	quit = 0;
    
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    fprintf(stdout, "%d\n", (int)time(NULL));

    return 0;
}

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "emokit.h"

int quit;

void cleanup(int i){
	fprintf(stdout,"Shutting down\n");
	quit=1;
}

void printToFile(FILE *file, struct emokit_frame data) {
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);

    if (size == 0) {
        fprintf(file, "counter, F3, FC6, P7, T8, F7, F8, T7, P8, AF4, F4, AF3, O2, O1, FC5, contact F3, contact FC6, contact P7, contact T8, contact F7, contact F8, contact T7, contact P8, contact AF4, contact F4, contact AF3, contact O2, contact O1, contact FC5, gyroX, gyroY\n");
    }

    fprintf(file, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", data.counter, data.F3, data.FC6, data.P7, data.T8, data.F7, data.F8, data.T7, data.P8, data.AF4, data.F4, data.AF3, data.O2, data.O1, data.FC5, data.cq.F3, data.cq.FC6, data.cq.P7, data.cq.T8, data.cq.F7, data.cq.F8, data.cq.T7, data.cq.P8, data.cq.AF4, data.cq.F4, data.cq.AF3, data.cq.O2, data.cq.O1, data.cq.FC5, data.gyroX, data.gyroY);
}

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(int argc, char **argv)
{
	struct emokit_device* device;
	signal(SIGINT, cleanup); //trap cntrl c

	quit = 0;

    FILE *file;
    file = fopen("log_emokit.csv", "a+");

	device     = emokit_create();
	int count  = emokit_get_count(device, EMOKIT_VID, EMOKIT_PID);

    printf("Current epoc devices connected: %d\n", count );

    int checker = emokit_open(device, EMOKIT_VID, EMOKIT_PID, 1);
	if (checker != 0) {
		emokit_close(device);
		emokit_delete(device);

        device    = emokit_create();
		checker   = emokit_open(device, EMOKIT_VID, EMOKIT_PID, 0);
		if (checker != 0) {
			printf("CANNOT CONNECT: %d\n", checker);
			return 1;
		}
	}
	printf("Connected to headset.\n");

	checker    = emokit_read_data_timeout(device, 1000);

    if (checker <= 0) {
		if (checker < 0) {
			fprintf(stderr, "Error reading from headset\n");
        } else {
			fprintf(stderr, "Headset Timeout...\n");
        }

        emokit_close(device);
		emokit_delete(device);
		return 1;
	}

	struct emokit_frame data;
	int counter    = 0;
    
    clock_t first   = clock();
    while ((counter / 129) < 2) {
		int err = emokit_read_data_timeout(device, 1000);
		if(err > 0) {
			data = emokit_get_next_frame(device);
			fprintf(stdout,"\033[H\033[2JPress CTRL+C to exit\n\nBattery : %5d\nCounter : %5d\n", data.battery, data.counter);
			fflush(stdout);

//            printToFile(file, data);
		} else if(err == 0) {
			fprintf(stderr, "Headset Timeout...\n");
		}
        
        counter++;
	}
    
    clock_t second  = clock();
    
    long elapsed    = timediff(first, second);
    printf("elapsed: %ld ms\n", elapsed);
    
    fclose(file);
	emokit_close(device);
	emokit_delete(device);
	return 0;
}

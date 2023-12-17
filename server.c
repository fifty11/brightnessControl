/*
 * OBS MUST BE RUN IN ADMIAN AND FOR INTEL CPUS ONLY!!!
 * licence: FOSS
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server_protocol.h"

// #define BRIGHTNESS_FILE_PATH "brightness"
// #define MAX_BRIGHTNESS_FILE_PATH "max_brightness"

int main(/*int argc, char** argv*/) {
	while(1) {
		int brightnessChange = 0;
		// wait for signal here
		/*if(argc>1) { // replace this part with a signal from a non sudo program.
						brightnessChange = atoi(argv[1]);
						printf("\n\nchange by: %d\n", brightnessChange);
		}
		else {
						fprintf(stderr, "missing comand line argument");
						return -3;
		}
		*/

		FILE *maxBrightnessFile;
		int maxBrightness;
		maxBrightnessFile = fopen(MAX_BRIGHTNESS_FILE_PATH, "r");
		if (maxBrightnessFile == NULL) {
			fprintf(stderr, "server has no read acess to the brightness file");
			// TODO send signal back to the callinng program that there is no acess 
			return -2;
		}
		fseek(maxBrightnessFile, 0L, SEEK_END);
		char tmpStr[ftell(maxBrightnessFile)];
		rewind(maxBrightnessFile);
		fscanf(maxBrightnessFile, "%s", tmpStr);
		maxBrightness = atoi(tmpStr);

		FILE *brightnessFile;

		brightnessFile = fopen(BRIGHTNESS_FILE_PATH, "r");
		if (brightnessFile == NULL) {
			fprintf(stderr, "server has no read acess to the brightness file or file dont exist");
			return -1;
		}
		fscanf(brightnessFile, "%s", tmpStr);
		printf("current in file: %s\n", tmpStr);
		int brightnessCurrent = atoi(tmpStr);
		printf("num current: %d\n", brightnessCurrent);
		fclose(brightnessFile);

		brightnessFile = fopen(BRIGHTNESS_FILE_PATH, "w");
		if (brightnessFile == NULL) {
			fprintf(stderr, "server has no write acess to the brightness file or file dont exist");
			return -1;
		}
		if (brightnessCurrent + brightnessChange > 0 &&	brightnessCurrent + brightnessChange < maxBrightness) {
			snprintf(tmpStr, strlen(tmpStr) + 1, "%d",
							 brightnessCurrent + brightnessChange);
			fprintf(brightnessFile, "%s", tmpStr);
		} else if (brightnessCurrent + brightnessChange > maxBrightness) {
			fprintf(stderr, "number to big auto correct to: %d", maxBrightness);
			snprintf(tmpStr, strlen(tmpStr) + 1, "%d", maxBrightness);
			fprintf(brightnessFile, "%s", tmpStr);
		} else {
			fprintf(stderr, "number to big auto correct to: %d", maxBrightness);
			fprintf(brightnessFile, "0");
		}
		fclose(brightnessFile);
		fclose(maxBrightnessFile);
	}
		return 0;
}

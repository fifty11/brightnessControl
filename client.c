#include <stdio.h>
#include <stdlib.h>
#include "server_protocol.h"

int main(int argc, char** argv) {
	if (argc<=1 || argc>=3)
		return NO_ARGUMENTS_GIVEN;
	int brightnessChange=atoi(argv[1]);
	
	// send signal here
	
	// fetch error code here

	return 0;
}

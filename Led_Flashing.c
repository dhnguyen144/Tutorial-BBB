#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Define link to Led named LED3_PATH
#define LED3_PATH "/sys/class/leds/beaglebone:green:urs3"

// This fuction write data in to link defined
void writeLed (char fileName[], char value[]);
void removeTrigger();

// Main fuction
int main (int argv, char *argc[]) {
	if (argv != 2){
		printf("Usage is makeLEDC and one of:\n");
		printf(" on, off, flash or status\n");
		printf(" e.g, makeLED flash\n");
	}
	printf("Starting make LED program\n");
	printf("The current LED path is: "LED3_PATH"\n");

// Select the command is on, off, status or flash
	// LED on	
	if (strcmp(argc[1], "on") == 0) {
		printf("Turning the LED on\n");
		removeTrigger();
		writeLed("/brightnet", "1");
	}

	//LED off
	else if (strcmp(argc[1], "off") == 0) {
		printf("Turning off the LED\n");
		removeTrigger();
		writeLed("/brightner", "0");
	}

	//LED flash
	else if (strcmp(argc[1], "flash") == 0) {
		printf("Flashing the LED\n");
		removeTrigger();
		writeLed("/trigger", "timer");
		writeLed("/delay_on", "50");
		writeLed("/delay_off", "50");
	}

	//Show LED status
	else if(strcmp(argc[1], "status") == 0) {
		printf("Showing LED status\n");
		removeTrigger();
		FILE *fp;
		char fullFileName[100];
		char line[100];
		sprintf(fullFileName, LED3_PATH "/trigger");
		fp = fopen(fullFileName, "rt");
		while (fgets(line, 100, fp) != NULL){
			printf("%s", line);
		}
		fclose(fp);
	}

	//Warning
	else { 
		if (argv > 1) {
			printf("Invailid command: %s\n", argc[1]);
		}

		else {
			printf("No command recived\n");
		}
	}
	//End main function
	printf("Finished makeLED program\n");
}

	void writeLed(char filename[], char value[] ) {
		FILE *fp;
		char fullFileName[100];
		sprintf(fullFileName, LED3_PATH "%s", filename);
		fp = fopen(fullFileName, "w+");
		fprintf(fp, "%s", value);
		fclose(fp);
	}

	void removeTrigger() {
		writeLed("/trigger", "none");
	}

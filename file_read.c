// import serious stuff
#include<stdio.h>
#include<stdlib.h>


// read data from file 
void read_from_file(char file_path[])
{
	// essential variables
	FILE *file_pointer;
	long file_length;
	char *buffer = 0;

	// open the file
	file_pointer = fopen(file_path, "r");

	//exit if file does not exist
	if(file_pointer == NULL) {
		printf("FATAL: The file %s does not exist, exiting...\n", file_path);
		exit(1);
	}

	// allocate memory to load the file
	fseek(file_pointer, 0, SEEK_END);
	file_length = ftell(file_pointer);
	fseek(file_pointer, 0, SEEK_SET);
	buffer = malloc(file_length);

	// exit if memory cannot be allocated
	if(buffer == NULL) {
		printf("FATAL: No memory left, exiting...\n");
		exit(1);
	}

	// read from file
	fread(buffer, sizeof(char), file_length, file_pointer);
	fclose(file_pointer);
	//buffer[file_length] = '\0';

	// debug
	printf("%s\n", buffer);
}


// the main function
int main()
{
	read_from_file("weather_url");
	return 0;
}

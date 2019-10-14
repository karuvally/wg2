// import serious stuff
#include<stdio.h>
#include<stdlib.h>


// read data from file 
void read_from_file(char file_path[])
{
	// essential variables
	FILE *file_pointer;
	long file_length;
	char buffer[100];

	// open the file
	file_pointer = fopen(file_path, "r");

	//exit if file does not exist
	if(file_pointer == NULL) {
		exit(1);
	}

	// get the file length
	fseek(file_pointer, 0, SEEK_END);
	file_length = ftell(file_pointer);
	fseek(file_pointer, 0, SEEK_SET);

	// read from file
	fread(buffer, sizeof(char), 50, file_pointer);
	buffer[50] = '\0';

	// debug
	printf("%s\n", buffer);
}


// the main function
int main()
{
	read_from_file("weather_url");
	return 0;
}

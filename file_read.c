// import serious stuff
#include<stdio.h>
#include<stdlib.h>


// read data from file 
void read_from_file(char input_file[])
{
	// essential variables
	FILE *file_pointer;
	char buffer[100];

	// open the file
	file_pointer = fopen(input_file, "r");

	//exit if file does not exist
	if(file_pointer == NULL) {
		exit(1);
	}

	// read from file
	fread(buffer, sizeof(char), 50, file_pointer);

	// debug
	printf("%s\n", buffer);
}


// the main function
int main()
{
	read_from_file("weather_url");
	return 0;
}

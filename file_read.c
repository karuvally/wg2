// import serious stuff
#include<stdio.h>
#include<stdlib.h>


// read data from file 
void read_from_file()
{
	// essential variables
	FILE *file_pointer;
	char buffer[100];

	// open the file
	file_pointer = fopen("weather_url", "r");

	//exit if file does not exist
	if(file_pointer == NULL) {
		exit(1);
	}

	// read from file
	fread(buffer, sizeof(char), 50, file_pointer);
}


// the main function
int main()
{
	read_from_file();
	return 0;
}

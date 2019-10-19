// Weather-Get2, rewrite of weather-get written for speed
// Copyright 2019, Aswin Babu Karuvally

// import the serious stuff
#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>


// read data from file 
char *read_from_file(char file_path[])
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
	
	// return stuff
	return buffer;
}


// initialize curl
char *get_url(char url[])
{
	//essential variables
	char *buffer = 0;

	// initialize CURL
	CURL *curl_handle;
	CURLcode result;
	curl_handle = curl_easy_init();

	// fetch the URL
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	result = curl_easy_perform(curl_handle);

	// return whatever is fetched
	return buffer;
}


// the main function
int main()
{
	// read weather API string from file
	char *weather_url = read_from_file("weather_url");

	// fetch the weather data
	char *weather_data = get_url(weather_url);

	// just quit :D
	return 0;
}

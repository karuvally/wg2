// import the serious stuff
#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>

// piece together weather URL from multiple strings
char *get_weather_url()
{
	// essential variables
	char *weather_url = 0;
	int length;

    // open the file
    FILE *url_file = fopen("weather_url", "r");
    
    // exit if the file does not exist
    if(url_file == NULL) {
        printf("FATAL: Cannot load weather_url, exiting...\n");
        exit(1);
	}

	// allocate memory to load the file 
	fseek(url_file, 0, SEEK_END);
	length = ftell(url_file);
	weather_url = malloc(length);

	// exit if memory cannot be allocated 
	if(weather_url == NULL) {
		printf("FATAL: No memory left, exiting...\n");
		exit(1);
	}

	// read the file and close it
	fread(weather_url, length, 1, url_file);
	fclose(url_file);

	return weather_url;
}


// the main function
int main()
{
	// read weather URL from file
    char *weather_url = get_weather_url();

	/*
    // initialize curl
	curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl_handle;
    CURLcode result;
    curl_handle = curl_easy_init();
	*/
    
	// just quit :D
	return 0;
}

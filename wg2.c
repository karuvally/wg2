// import the serious stuff
#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>

// piece together weather URL from multiple strings
char *get_weather_url()
{
	// essential variables
	char *buffer = 0;
	int length;

    // open the file
    FILE *url_file = fopen("weather_url", "r");
    
    // exit if the file does not exist
    if(url_file == NULL) {
        printf("cannot load weather_url, exiting...");
        exit(1);
	}

	// get the length of the file
	fseek(url_file, 0, SEEK_END);
	length = ftell(url_file);
    
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

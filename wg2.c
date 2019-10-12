// import the serious stuff
#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>

// piece together weather URL from multiple strings
def get_weather_url()
{
    // open the file
    FILE *url_file = fopen("weather_url", "r");
    
    // exit if the file does not exist
    if(url_file == NULL) {
        printf("cannot load weather_url, exiting...")
        exit(1)
    
    return weather_url;
}


// the main function
int main()
{
    // initialize curl
	curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl_handle;
    CURLcode result;
    curl_handle = curl_easy_init();
    
    // read weather URL from file
    weather_url = get_weather_url()
    
	return 0;
}

// import the serious stuff
#include<stdio.h>
#include<curl/curl.h>


// the main function
int main()
{
	// global variables
	char weather_url[] = "http://pro.openweathermap.org/data/2.5/forecast/hourly?q=Hyderabad,in";

	// global init stuff
	curl_global_init(CURL_GLOBAL_ALL);

	// curl handle
	CURL *curl_handle;
	CURLcode result;

	// initialize the easy interface
	curl_handle = curl_easy_init();

	// fetch a page
	curl_easy_setopt(curl_handle, CURLOPT_URL, weather_url);

	// return nothing
	return 0;
}

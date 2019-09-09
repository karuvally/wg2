// import the serious stuff
#include<stdio.h>
#include<curl/curl.h>


// the main function
int main()
{
	CURL *curl;
	CURLcode response;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
		response = curl_easy_perform(curl);

		if(response != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(response));

		curl_easy_cleanup(curl);
	}

	return 0;
}

// Weather-Get2, rewrite of weather-get written for speed
// Copyright 2019, Aswin Babu Karuvally

// import the serious stuff
#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>


// structure to store fetched data
struct data {
	char *memory;
	size_t size;
};


// allocate memory to store retrieved data 
int write_mem_callback(
	char *buffer,
	size_t size,
	size_t no_members,
	void *fetched_data
){
	// allocate required amount of memory
	size_t actual_size = size * no_members;
	struct data *data_ptr = (struct data *)fetched_data;

	char *allocated_mem = realloc(
		data_ptr->memory,
		data_ptr->size + actual_size + 1
	);

	data_ptr->memory = allocated_mem;
	memcpy(&(data_ptr->memory[data_ptr->size]), buffer, actual_size);
	data_ptr->size += actual_size;
	data_ptr->memory[data_ptr->size] = 0;
	
	// return actual_size if everything goes according to plan 
	return actual_size;
}


// read data from file 
char *read_from_file(char file_path[])
{
	// essential variables
	FILE *file_pointer;
	long file_length;
	char *buffer = NULL;

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
	buffer = malloc(file_length + 1);

	// exit if memory cannot be allocated
	if(buffer == NULL) {
		printf("FATAL: No memory left, exiting...\n");
		exit(1);
	}

	// read from file
	fgets(buffer, file_length, file_pointer);
	fclose(file_pointer);
	//buffer[file_length] = '\0';
	
	// return stuff
	return buffer;
}


// initialize curl
struct data get_url(char *url)
{
	// setup struct to store fetched data
	struct data fetched_data;
	fetched_data.memory = malloc(1);
	fetched_data.size = 0;

	// initialize curl 
	CURL *curl_handle;
	CURLcode result;
	curl_handle = curl_easy_init();

	// specify what we want curl to do 
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_mem_callback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&fetched_data);

	// fetch the data 
	result = curl_easy_perform(curl_handle);

	// print error if something went wrong
	if(result != CURLE_OK)
		printf("FATAL: CURL returned error %d\n", result);

	// return whatever is fetched
	return fetched_data;
}


// the main function
int main()
{
	// read weather API string from file
	char *weather_url = read_from_file("weather_url");

	// fetch the weather data
	struct data weather_data = get_url(weather_url);

	// just quit :D
	return 0;
}

// Weather-Get2, rewrite of weather-get written for speed
// Copyright 2019, Aswin Babu Karuvally

// import the serious stuff
#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
#include<jansson.h>
#include<string.h>


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

	// quit if memory can't be allocated
	if(allocated_mem == NULL) {
		printf("FATAL: No memory left, exiting...\n");
		exit(1);
	}

	// assign the reallocated memory,
	data_ptr->memory = allocated_mem;

	// copy newly fetched chunk to existing data
	memcpy(&(data_ptr->memory[data_ptr->size]), buffer, actual_size);
	data_ptr->size += actual_size;
	data_ptr->memory[data_ptr->size] = '\0';
	
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
	
	// return stuff
	return buffer;
}


// initialize curl
char *get_url(char *url)
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
	return fetched_data.memory;
}


// process the retrieved JSON
json_t *parse_json(char *data_string)
{
	// essential variables
	json_t *parsed_json;
	json_error_t error; 

	// parse JSON and deallocate data_string 
	parsed_json = json_loads(data_string, 0, &error);
	free(data_string);

	if(!parsed_json) {
		printf("FATAL: JSON cannot be parsed!");
		exit(1);
	}

	// return the parsed JSON
	return parsed_json;
}


// print the weather_info
int print_weather_info(json_t *weather_json)
{
	// essential variables
	json_t *data, *temperature;

	// retrieve data contained in JSON array
	data = json_object_get(weather_json, "data"); 

	// quit if there is something wrong 
	if(!json_is_object(data)) {
		printf("FATAL: Invalid JSON object\n");
		exit(1);
	}
	
	// return 0 if everything goes write
	return 0;
}


// the main function
int main()
{
	// essential variables
	const char *message_text;

	// read weather API string from file
	char *weather_url = read_from_file("weather_url");

	// fetch the weather data
	char *weather_string = get_url(weather_url);

	// create json object out of the retrieved data
	json_t *weather_json = parse_json(weather_string);

	// print weather info to stdout
	print_weather_info(weather_json);

	// just quit :D
	return 0;
}

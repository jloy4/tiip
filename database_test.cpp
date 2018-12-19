#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <iterator>

std::vector<double> push_sequence;

std::string vectorToString(std::vector<double> v) {
	if (!v.empty()) {
		std::ostringstream oss;
		std::copy(v.begin(), v.end()-1, std::ostream_iterator<double>(oss, ","));
		oss << v.back();

		std::cout << oss.str() << std::endl;
		return oss.str();
	}
	return std::string("n/a");
}

std::string getTime() {
	/*auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S %Z");
	auto str = oss.str();

	return str;*/
	time_t curr_time;
	tm * curr_tm;
	char date_time[100];

	time(&curr_time);
	curr_tm = localtime(&curr_time);

	std::strftime(date_time, 50, "%d-%m-%Y %H-%M-%S %Z", curr_tm);

	std::cout << date_time << std::endl;
	return date_time;
}

void saveData() {
	CURL *curl;
	CURLcode res;
	char data[200];
	snprintf(data, 200, "{\"session_end\":\"%s\",\"amount\":%.2f, \"sequence\":[%s]}",getTime().c_str(), 0.5, vectorToString(push_sequence).c_str());
printf("%s", data);

	curl_global_init(CURL_GLOBAL_ALL);
	struct curl_slist *list = NULL;

	curl = curl_easy_init();
	if(curl) {
		// url to database
		curl_easy_setopt(curl, CURLOPT_URL, "https://tiips-fr.firebaseio.com/bar.json");

		//request headers
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlenconded");

		//curl options
		curl_easy_setopt(curl, CURLOPT_VERBOSE, false);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		curl_easy_setopt(curl, CURLOPT_HEADER, true);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data));

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

int main() {
	push_sequence.push_back(0.5);
	push_sequence.push_back(2);
	push_sequence.push_back(1);

	saveData();
	return 0;
}

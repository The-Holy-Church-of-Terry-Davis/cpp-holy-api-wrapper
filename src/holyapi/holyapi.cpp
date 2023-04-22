#include "holyapi.h"

HolyAPI::HolyAPI() {
    // Initialize curl
    m_curl = curl_easy_init();
    if (!m_curl) {
        cerr << "Failed to initialize curl" << endl;
    }
}

HolyAPI::~HolyAPI() {
    // Clean up
    curl_easy_cleanup(m_curl);
}

json HolyAPI::callAPI(string endpoint, int amount) {
    CURLcode res;
    string url = "https://api.thcotd.repl.co/" + endpoint;

    if (amount > 0) {
        url += "?amount=" + to_string(amount);
    }

    string responseBody;

    if (!m_curl) {
        cerr << "Failed to initialize curl" << endl;
        return nullptr;
    }

    // Set the URL to perform the GET request on
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    // Specify the callback function to handle the received data
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, writeCallback);

    // Pass a pointer to responseBody to the callback function
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &responseBody);

    // Perform the GET request
    res = curl_easy_perform(m_curl);
    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return nullptr;
    }

    // Parse the JSON response
    json j = json::parse(responseBody);

    // Clean up
    curl_easy_reset(m_curl);

    // Return the JSON object
    return j;
}

string HolyAPI::getStatus(string what) {
    json response = callAPI("status");

    if (response == nullptr) {
        return "";
    }

    try {
        response = response[what];
        return response;
    }
    catch (const out_of_range& e) {
        return response;
    }
}

string HolyAPI::getInfo(string what) {
    json response = callAPI("info");

    if (response == nullptr) {
        return "";
    }
    size_t pos = what.find("."); // Find the position of the period
    if (pos != string::npos) { // If the period is present
        string s1 = what.substr(0, pos); // Get the substring before the period
        string s2 = what.substr(pos + 1); // Get the substring after the period
        return response[s1][s2];
    }

    try {
        response = response[what];
        return response;
    }
    catch (const out_of_range& e) {
        return response;   
    }
}

string HolyAPI::getGodsay(int amount) {
    json response = callAPI("godsay", amount);

    if (response == nullptr) {
        return "";
    }

    return response["godsay"];
}

vector<string> HolyAPI::getQuotes(int amount) {
    json response = callAPI("quote", amount);

    if (response == nullptr) {
        return {};
    }

    return response["quotes"];
}

string HolyAPI::getDivineIntellect(string what, bool return_as_string) {
    json response = callAPI("divineintellect");

    if (response == nullptr) {
        return "";
    }

    if (!return_as_string) {
        return response;
    }

    try {
        response = response[what];
        return response;
    }
    catch (const out_of_range& e) {
        return response;
    }
}

string HolyAPI::getAskTerry(bool return_as_string) {
    json response = callAPI("askterry");

    if (response == nullptr) {
        return "";
    }
    if (return_as_string) {
        return response["answer"];
    }
    return response;
}

size_t HolyAPI::writeCallback(char *ptr, size_t size, size_t nmemb, string *data) {
    size_t bytes = size * nmemb;
    data->append(ptr, bytes);
    return bytes;
}
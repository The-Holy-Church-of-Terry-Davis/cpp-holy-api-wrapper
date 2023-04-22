#ifndef HOLYAPI_H
#define HOLYAPI_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class HolyAPI {
public:
    HolyAPI();
    ~HolyAPI();
    json callAPI(string endpoint, int amount = 0);

    string getStatus(string what = "");
    string getInfo(string what = "");
    string getGodsay(int amount = 1);
    vector<string> getQuotes(int amount = 1);
    string getDivineIntellect(string what = "divineIntellect", bool return_as_string = true);
    string getAskTerry(bool return_as_string = true);

private:
    CURL *m_curl;
    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, string *data);
};

#endif // HOLYAPI_H
# C++ HolyAPI Wrapper

This is a C++ wrapper for the Holy API. The Holy API provides access to divine messages and knowledge from Terry, as well as random quotes, information about the Holy Church of Terry Davis, and more.

I literally have NO idea wtf I'm doing. If you really want to know how to use this wrapper, go check out the source code...

API: https://api.thcotd.repl.co

## Requirements

- C++11 or higher
- libcurl development headers

## Installation

1. Clone the repository with the following command:
```sh
$ git clone https://github.com/the-holy-church-of-terry-davis/cpp-holy-api-wrapper.git
```


2. Include the `holyapi/` directory in your project.
```cpp
#include <iostream>
#include "holyapi/holyapi.h"
```

## Usage

To use the HolyAPI class in your project, create an instance of the HolyAPI class:
```cpp
HolyAPI api;
```

Example:
```cpp
#include <holyapi/holyapi.h>

using namespace std;

int main() {
    HolyAPI api;
    cout << "Godsay: " << api.getGodsay(5) << endl;
    //                      5 words ~~~~^

    vector<string> quotes = api.getQuotes(2);
    //                       2 quotes ~~~~^
    for (auto& quote : quotes) {
        cout << "Quote: " << quote << endl;
    }
    return 0;
}
/*
Godsay: deserved seem sights fifth suggestions
Quote: The most powerful statement in the C language is the switch statement.
Quote: God said 640x480 16 color.
*/
```

You can then call various functions on the api object to interact with the Holy API. Here are some examples:

### getStatus

Returns the current status of the Holy API.
```cpp
std::string status = api.getStatus();
std::cout << "Status: " << status << std::endl;
```

### getInfo

Returns a message about the Holy API.
```cpp
std::string message = api.getInfo();
std::cout << "Message: " << message << std::endl;
```

### getGodsay

Generates a random message from one of the gods.
```cpp
std::string message = api.getGodsay();
std::cout << "Godsay: " << message << std::endl;
```

### getQuotes

Generates a list of random quotes.
```cpp
std::vector<std::string> quotes = api.getQuotes();
for (auto& quote : quotes) {
    std::cout << "Quote: " << quote << std::endl;
}
```

### getDivineIntellect

Returns a message of divine intellect.
```cpp
std::string intellect = api.getDivineIntellect();
std::cout << "Divine intellect: " << intellect << std::endl;
```

### getAskTerry

Returns an answer to a question using the wisdom of Terry A. Davis.
```cpp
std::string answer = api.getAskTerry();
std::cout << "Terry's answer: " << answer << std::endl;
```
---
You can also call the callAPI function directly to interact with any endpoint of the Holy API:
```cpp
// Call the "status" endpoint
std::string status = api.callAPI("status");
std::cout << "Status: " << status << std::endl;

// Call the "info" endpoint
std::string message = api.callAPI("info");
std::cout << "Message: " << message << std::endl;

// Call the "godsay" endpoint with 3 messages
json godsays = api.callAPI("godsay", 3);
for (auto& godsay : godsays["godsays"]) {
    std::cout << "Godsay: " << godsay << std::endl;
}

// Call the "quote" endpoint with 5 quotes
json quotes = api.callAPI("quote", 5);
for (auto& quote : quotes["quotes"]) {
    std::cout << "Quote: " << quote << std::endl;
}

// Call the "divineIntellect" endpoint with timestamp field
std::string intellect = api.callAPI("divineIntellect");
std::cout << "Divine intellect: " << intellect << std::endl;

// Call the "askTerry" endpoint
json answer = api.callAPI("askTerry", 0);
std::cout << "Terry's answer: " << answer << std::endl;
```

By default, the callAPI function returns the response as a JSON object. You can specify the second argument to request a specific number of items from the endpoint (if the endpoint supports it).

## Endpoint options

The callAPI function supports the following endpoints:

- `/status`: Returns the current status of the Holy API.
- `/info`: Returns a message about the Holy API.
- `/godsay`: Generates a random message from one of the gods.
- `/quote`: Generates a list of random quotes.
- `/divineintellect`: Returns how much divine intellect you have.
- `/askterry`: Returns Terry's answer to a question.
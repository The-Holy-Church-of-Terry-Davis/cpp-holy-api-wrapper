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
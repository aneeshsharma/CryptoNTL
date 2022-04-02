#include "../util.h"
#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main() {
    string s = "hello this is a very long message";

    ZZ result = encodeToZZ(s);

    string message = decodeFromZZ(result);

    if (s == message) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }

    return 0;
}

#include "../util.h"
#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main() {
    string s = "hello this is a very long message";
    cout << s << endl;

    ZZ result = encodeToZZ(s);

    cout << result << endl;

    string message = decodeFromZZ(result);

    cout << message << endl;

    if (s == message) {
        cout << "Passed" << endl;
    }

    return 0;
}

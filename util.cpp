#include "util.h"
#include <NTL/ZZ.h>

using namespace NTL;
using namespace std;

ZZ encodeToZZ(string message) {
    ZZ result;
    result = 0;
    for (int i = message.length() - 1; i >= 0; i--) {
        result *= 0xff;
        result += message[i];
    }

    return result;
}

string decodeFromZZ(ZZ encoded) {
    string result;
    result = "";
    while (encoded != 0) {
        char ch = (char) (encoded % 0xff);
        result += ch;
        encoded /= 0xff;
    }

    return result;
}

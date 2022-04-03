#include "util.h"
#include <NTL/ZZ.h>
#include <openssl/sha.h>

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

string hashString(string message) {
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1((const unsigned char*) message.c_str(), (size_t) message.length(), hash);

    return string(reinterpret_cast<char*>(hash));
}

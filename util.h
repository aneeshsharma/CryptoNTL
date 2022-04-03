#include <NTL/ZZ.h>

using namespace NTL;
using namespace std;

#ifndef __UTIL_H_
#define __UTIL_H_

ZZ encodeToZZ(string message);
string decodeFromZZ(ZZ encoded);

string hashString(string message);

#endif

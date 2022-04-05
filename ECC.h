#include <NTL/ZZ.h>
#include <NTL/tools.h>
#include <cstddef>
#include <tuple>
#include <vector>

using namespace std;
using namespace NTL;

#ifndef __ELGAMAL_H_
#define __ELGAMAL_H_

#define INF power(ZZ(2), 10000)
#define K ZZ(13)

typedef struct Parameters {
    ZZ p, a, b, r, n, x, y; 
} Paramters;

const Parameters NIST192 = {
    .p = power(ZZ(2), 192) - power(ZZ(2), 64) - 1,
    .a = ZZ(-3),
    .b = conv<ZZ>("2455155546008943817740293915197451784769108058161191238065"),
    .r = conv<ZZ>("1191689908718309326471930603292001425137626342642504031845"),
    .n = conv<ZZ>("6277101735386680763835789423176059013767194773182842284081"),
    .x = conv<ZZ>("602046282375688656758213480587526111916698976636884684818"),
    .y = conv<ZZ>("174050332293622031404857552280219410364023488927386650641")
};

class Point {
    public:
        ZZ x, y;
        Point(ZZ x, ZZ y, Parameters param=NIST192);
        Point(): Point(INF, INF) {}
        Point Double();
        Point operator+(const Point &other);
        Point operator*(const ZZ &scalar);
        Point operator*(const int &scalar);
        Point clone();
        Point inverse();
    private:
        Parameters param;
};

ostream& operator<<(ostream& out, Point& p);
Point encodeToPoint(ZZ message, Parameters param=NIST192);
ZZ decodeFromPoint(Point Pm);

class ECC {
    private:
        Parameters param;
        Point P, Q;
        ZZ d;
    public:
        ECC(Parameters param=NIST192);
        tuple<Point, Point> encrypt(string message);
        string decrypt(tuple<Point, Point> ciphertext);
        tuple<Point, Point> sign(string message);
        bool verify(string message, tuple<Point, Point> sign);
    private:
        tuple<Point, Point> encryptZZ(ZZ message);
        ZZ decryptZZ(tuple<Point, Point> ciphertext);
};

#endif

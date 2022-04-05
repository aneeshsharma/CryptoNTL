#include <NTL/ZZ.h>
#include <NTL/tools.h>
#include <cstddef>
#include <tuple>
#include <vector>
#include "ECC.h"
#include "util.h"

using namespace std;
using namespace NTL;

Point::Point(ZZ x, ZZ y, Parameters param) {
    this->x = x;
    this->y = y;
    this->param = param;
}

Point encodeToPoint(ZZ message, Parameters param) {
    ZZ S;
    ZZ x, y;

    bool flag = false;

    for (ZZ i = ZZ(0); i < K; i++)
    {
        x = K * message + i;
        S = (power(x, 3) + (param.a * x) + param.b) % param.p;
        if (Jacobi(S, param.p) == 1)
        {
            PowerMod(y, S, (param.p + 1) / ZZ(4), param.p);
            flag = true;
        }
    }
    
    if (flag) {
        return Point(x, y, param);
    } else {
        Point inf = Point(ZZ(INF), ZZ(INF), param);
        return inf * message;
    }
}

ZZ decodeFromPoint(Point Pm) {
    ZZ result;
    div(result, Pm.x, K);
    return result;
}

Point Point::operator+(const Point &other) {
    // Check if either points are infinity
    if (x == ZZ(INF))
    {
        return other;
    }
    else if (other.x == ZZ(INF))
    {
        return clone();
    }

    // If points are same, Double one of them
    if (x == other.x && y == other.y)
    {
        return this->Double();
    }

    // Resulting Point
    Point R;

    // Temp Variables
    ZZ slope;

    // Compute slope
    slope = (other.y - y) * InvMod((other.x - x) % param.p, param.p);

    // Compute x
    R.x = (power(slope, 2) - x - other.x) % param.p;

    // Compute y
    R.y = (slope * (x - R.x) - y) % param.p;

    return R;
}

Point Point::operator*(const ZZ &scalar) {
    // Initialize R as (0, 0)
    Point R = Point(ZZ(INF), ZZ(INF));
    Point P = clone();

    // Iter through each bit of n
    for (long i = 0; i < NumBits(param.n); i++)
    {

        // Extract the bit
        ZZ mask = ZZ(1) << i;
        ZZ masked_n = param.n & mask;
        ZZ t = masked_n >> i;

        if (t == 1)
        {
            R = P + R;
        }
        P = Double();
    }

    return R;
}

Point Point::Double() {
    // Resulting Doubled Point
    Point Double_P;

    // Temp Variables
    ZZ num, den, slope;
    ZZ x_2;

    // Compute slope
    power(x_2, x, 2);
    num = 3 * x_2 + param.a;
    den = 2 * y;
    slope = num * InvMod(den % param.p, param.p);

    // Compute x
    Double_P.x = (power(slope, 2) - (2 * x)) % param.p;

    // Compute y
    Double_P.y = ((slope * (x - Double_P.x)) - y) % param.p;

    return Double_P;
}

Point Point::clone() {
    return Point(x, y, param);
}

Point Point::inverse() {
    Point P = clone();
    P.y = (-P.y) % param.p;
    return P;
}

ostream& operator<<(ostream& out, Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

ECC::ECC(Parameters param) {
    this->param = param;
    this->P = Point(param.x, param.y, param);
   
    do {
        RandomBnd(d, param.n);
    } while (d == 0);

    Q = P * d;
}

tuple<Point, Point> ECC::encryptZZ(ZZ message) {
    Point M = encodeToPoint(message, param);
    
    ZZ k;

    do {
        RandomBnd(k, param.n);
    } while (k == 0);

    Point C1 = P * k;
    Point C2 = M + Q * k;

    return {C1, C2};
}

ZZ ECC::decryptZZ(tuple<Point, Point> ciphertext) {
    Point temp, M;

    auto [C1, C2] = ciphertext;

    temp = C1 * d;

    M = C2 + temp.inverse();

    return decodeFromPoint(M);
}

tuple<Point, Point> ECC::encrypt(string message) {
    ZZ messageAsZZ = encodeToZZ(message);
    return encryptZZ(messageAsZZ);
}

string ECC::decrypt(tuple<Point, Point> ciphertext) {
    ZZ messageAsZZ = decryptZZ(ciphertext);
    return decodeFromZZ(messageAsZZ);
}


tuple<Point, Point> ECC::sign(string message) {
    string h = hashString(message);
    return encrypt(h);
}

bool ECC::verify(string message, tuple<Point, Point> signature) {
    string h = hashString(message);
    
    string recved_h = decrypt(signature);

    return h == recved_h;
}


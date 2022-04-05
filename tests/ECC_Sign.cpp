#include "../ECC.h"

int main() {
    ECC* ecc = new ECC();

    string message = "This needs to be signed";

    cout << "Message: " << message << endl;

    tuple<Point, Point> sign = ecc->sign(message);

    cout << "Signed: (" << get<0>(sign) << ", " << get<1>(sign) << ") " << endl;

    if (ecc->verify(message, sign)) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }
}

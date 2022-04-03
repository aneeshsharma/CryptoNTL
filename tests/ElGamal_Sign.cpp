#include "../ElGamal.h"

int main() {
    ElGamal* el = new ElGamal(512);

    string message = "This needs to be signed";

    cout << "Message: " << message << endl;

    tuple<ZZ, ZZ> sign = el->sign(message);

    cout << "Signed: (" << get<0>(sign) << ", " << get<1>(sign) << ")" << endl;

    if (el->verify(message, sign)) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }
    return 0;
}

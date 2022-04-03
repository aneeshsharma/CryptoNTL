#include "../RSA.h"

int main() {
    RSA* rsa = new RSA(512);

    string message = "This needs to be signed";

    cout << "Message: " << message << endl;

    ZZ sign = rsa->sign(message);

    cout << "Signed: " << sign << endl;

    if (rsa->verify(message, sign)) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }
    return 0;
}

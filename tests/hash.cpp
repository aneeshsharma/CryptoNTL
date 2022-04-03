#include "../util.h"

int main() {
    string message;
    
    message = "A message to be hashed";
    string h = hashString(message);

    cout << "Original message: " << message << endl;
    cout << "Hash: " << h << endl;

    if (hashString(message) == hashString(message)) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }
}

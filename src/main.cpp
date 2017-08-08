#include "QuynhObject.h"
#include "ADFGVXCipher.h"

using namespace QuynhSecurity;

int main() {
    QuynhObject *object;
    int choice;

    object = new ADFGVXCipher();

    while (1) {
         //Demo 
        cout << "\x43\x68\xe1\xbb\x8d\x6e \x6c\xe1\xbb\xb1\x61\x3a" << endl;
        cout << "\x31\x2e \x4d\xc3\xa3 \x68\x6f\xc3\xa1" << endl;
        cout << "\x32\x2e \x47\x69\xe1\xba\xa3\x69 \x6d\xc3\xa3" << endl;
        cout << "\x33\x2e \x54\x68\x6f\xc3\xa1\x74" << endl;

        cin >> choice;

        switch(choice) {
            case QuynhObject::ENCRYPT:
                object->encript();
            break;
            case QuynhObject::DECRYPT:
                object->decript();
            break;
            case QuynhObject::EXIT_PROGRAM:
                exit(0);
            break;
        }
    }
   


    delete object;

    return 0;
}
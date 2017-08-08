#ifndef ADFGVX_CIPHER_H
#define ADFGVX_CIPHER_H

#include "QuynhObject.h"

/* Polybe related stuff */
#define POLYB "c1ofwjymt5b4i7a28sp30qhxkeul6dvrgzn9"
#define ADFGVX "ADFGVX"
#define POLY_KEY_LEN 6

namespace QuynhSecurity {

    class ADFGVXCipher : public QuynhObject {
    public:
        ADFGVXCipher();
        ~ADFGVXCipher();
        /**
        * Given a polybius square, the permutation key and the plaintext, encrypts the plaintext.
        * @param polyb
        * @param pkey
        * @param plain
        * @return cipher
        */
        char *encrypt(char *polyb, char *pkey, char *plain);
        /**
        * Given a polybius square, the permutation key and the ciphertext, retrieves the plaintext.
        * @param polyb
        * @param pkey
        * @param cipher
        * @return plain
        */
        char *decrypt(char *polyb, char *pkey, char *cipher);
    public: //interface
        virtual void encript();
        virtual void decript();
    };
}

#endif

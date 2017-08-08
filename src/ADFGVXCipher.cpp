#include "ADFGVXCipher.h"
#include <string.h>
#include <stdlib.h>

namespace QuynhSecurity {
    void ADFGVXCipher::encript() {
        cout << "\x43\x68\xc6\xb0\xc6\xa1\x6e\x67 \x74\x72\xc3\xac\x6e\x68 \x6d\xc3\xa3 \x68\x6f\xc3\xa1 \x76\xe1\xbb\x9b\x69 \x74\x68\x75\xe1\xba\xad\x74 \x74\x6f\xc3\xa1\x6e \x41\x44\x46\x47\x56\x58" << endl;
        cout << "Sample" << endl;
        
        string planText = "Le Xuan Quynh";
        string polyb = "3nbiczrfv819dlwht5s0juqx47pkoy6mga2e";
        string pkey = "vietnam";

        cout << "keysquare = " << polyb << endl;
        cout << "keyword = " << pkey << endl;
        cout << "Plaintext = " << planText << endl;
        cout << "Ciphertext = XGDXGVDXGGVFGDAXAXFGGG" << endl;

        cout << "Result = " << encrypt((char*)polyb.c_str(), (char*)pkey.c_str(), (char*)planText.c_str()) << endl;
    }
    
    void ADFGVXCipher::decript() {
        cout << "\x43\x68\xc6\xb0\xc6\xa1\x6e\x67 \x74\x72\xc3\xac\x6e\x68 \x67\x69\xe1\xba\xa3\x69 \x6d\xc3\xa3 \x76\xe1\xbb\x9b\x69 \x74\x68\x75\xe1\xba\xad\x74 \x74\x6f\xc3\xa1\x6e \x41\x44\x46\x47\x56\x58" << endl;
    }

    ADFGVXCipher::ADFGVXCipher() {

    }

    ADFGVXCipher::~ADFGVXCipher() {

    }

    /**
    * Given a polybius square, the permutation key and the plaintext, encrypts the plaintext.
    * @param polyb
    * @param pkey
    * @param plain
    * @return cipher
    */
    char* ADFGVXCipher::encrypt(char *polyb, char *pkey, char *plain) {
        int i, s, n = (int)strlen((pkey));
        int len_plain = (int)strlen(plain);
        int len_cipher = ((2*len_plain + n - 1)/n)*n ; // round up to have a proper multiple of n buffer
        char *sub_cipher = (char*)calloc( (size_t)len_cipher, sizeof(char));
        char *cipher = (char*)calloc( (size_t)len_cipher, sizeof(char));

        /*
         * 1. Substitution
        */

        for( i = 0 ; i < len_plain ; i++) {
            s = 0;
            while( polyb[s] != plain[i] ) s++;

            sub_cipher[2*i] = ADFGVX[s/POLY_KEY_LEN];
            sub_cipher[2*i+1] = ADFGVX[s%POLY_KEY_LEN];
        }

        for(i = 2*len_plain; i < len_cipher ; i++)
            sub_cipher[i] = 'X';

        sub_cipher[len_cipher] = '\0';

        /*
         * 2. Proceed to double permutation cipher
        */

        int nb_lines = len_cipher / n, j;

        for( i = 0 ; i < nb_lines ; i++)
            for (j = 0; j < n; j++)
                cipher[i * n + pkey[j] - '0' - 1] = sub_cipher[i * n + j];

        for (j = 0; j < n; j++)
            for (i = 0; i < nb_lines; i++)
                sub_cipher[j * nb_lines + i] = cipher[i * n + j];

        sub_cipher[len_cipher] = '\0';

        /*
         * Clean up and exit
        */
        free(cipher);

        return sub_cipher;
}


    /**
     * Given a polybius square, the permutation key and the ciphertext, retrieves the plaintext.
    * @param polyb
    * @param pkey
     * @param cipher
    * @return plain
    */

    char* ADFGVXCipher::decrypt(char *polyb, char *pkey, char *cipher) {
        int i, j, pos_x, pos_y, n = (int)strlen((pkey));
        int len_cipher = (int)strlen(cipher);
        int len_plain = (len_cipher / 2);
        int nb_lines = len_cipher / n;
        char *sub_cipher = (char*)calloc( (size_t)len_cipher, sizeof(char));
        char *plain = (char*)calloc( (size_t)len_plain, sizeof(char));

        /*
        * 1. Permutation
        */

        for (i = 0; i < n; i++)
            for (j = 0; j < nb_lines; j++)
                sub_cipher[j*n + i] = cipher[i * nb_lines + j];

        for( i = 0 ; i < nb_lines ; i++)
            for (j = 0; j < n; j++)
                cipher[i*n + j] = sub_cipher[i * n + pkey[j] - '0' - 1];

        /*
        * 2. Substitution
        */
        for(i = 0; i < len_cipher/2 ; i++ ) {
            pos_y = 0;

            while( ADFGVX[pos_y] != cipher[2*i] ) 
            pos_y++;

            pos_x = 0;

            while( ADFGVX[pos_x] != cipher[2*i+1] ) 
                pos_x++;

            plain[i] = polyb[POLY_KEY_LEN*pos_y + pos_x];
        }

        plain[len_plain-1] = '\0';
        free(sub_cipher);

        return plain;
    }
}
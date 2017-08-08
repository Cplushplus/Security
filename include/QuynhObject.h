#ifndef QUYNH_OBJECT_H
#define QUYNH_OBJECT_H

#include<iostream>
#include <string>

namespace QuynhSecurity {
    using std::cout;
    using std::endl;
    using std::cin;
    
    using std::string;
    
    class QuynhObject {
    public:
    // Chon lua ma hoa hay giai ma
        enum {
            ENCRYPT = 1,
            DECRYPT = 2,
            EXIT_PROGRAM = 3
        };   
        //Dinh nghia cac loai ma hoa o day
        enum CIPHER_TYPE {
                ADFGVX_CIPHER
        };

    public:
        QuynhObject();
        virtual ~QuynhObject();

    public: //interface
        virtual void encript() = 0;
        virtual void decript() = 0;
    };
}

#endif
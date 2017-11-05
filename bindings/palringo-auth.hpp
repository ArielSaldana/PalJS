#ifndef palringo_auth_hpp
#define palringo_auth_hpp
#pragma once

#include <stdio.h>
#include <openssl/md5.h>
#include "ecrypt-sync.h"
#include <iostream>
#include <string>

namespace PalAuth {
    class Salsa20 {
    public:
        static void authenticate(unsigned char*, unsigned char*, size_t, unsigned char*);
        static void encrypt(unsigned char* key, unsigned char *iv, unsigned char *msg, unsigned char *out);
    };
}

#endif // palringo_auth_hpp
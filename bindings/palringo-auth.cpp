#include "palringo-auth.hpp"

void PalAuth::Salsa20::authenticate(unsigned char *authMsg, unsigned char *password, size_t passLen, unsigned char *out) {
    unsigned char iv[9];
    unsigned char msg[17];
    unsigned char key[33]; //first 16 bytes will be from salsa 20. then 16 more bytes.
    unsigned char digest[17]; // md5 digest

    bzero(iv, 9);
    bzero(msg, 17);
    bzero(key, 17);
    bzero(out, 32);
    // bzero(digest, 17);

    // set the iv, and msg
    for (int i = 0; i < 24; i++) {
        if (i < 16) {
            msg[i] = authMsg[i];
        } else {
            iv[i-16] = authMsg[i];
        }
    }

    // setup the key.
    MD5_CTX md5ctx;
    MD5_Init(&md5ctx);
    // MD5_Update(&md5ctx, password, strlen((char*)password));
    MD5_Update(&md5ctx, password, passLen);
    MD5_Final(key, &md5ctx);

    unsigned char passWithIv[25];
    bzero(passWithIv, 25);

    for(int i = 0; i < 25; i++) {
        if (i < 16) {
            passWithIv[i] = key[i];
        } else {
            passWithIv[i] = iv[i-16];
        }
    }

    MD5_Init(&md5ctx);
    MD5_Update(&md5ctx, passWithIv, 24);
    MD5_Final(key, &md5ctx);

    // finally do the shiz
    ECRYPT_ctx x;
    ECRYPT_keysetup(&x, key,16,8);
    ECRYPT_ivsetup(&x, iv);
    ECRYPT_encrypt_bytes(&x, msg, out, 16); // force length 16
}

void PalAuth::Salsa20::encrypt(unsigned char* key, unsigned char *iv, unsigned char *msg, unsigned char *out) {
    ECRYPT_ctx x;
    ECRYPT_keysetup(&x, key,16,8);
    ECRYPT_ivsetup(&x, iv);
    ECRYPT_encrypt_bytes(&x, msg, out, 16); // force length 16
}
#include "cryptage.h"

bool cryptPassword(char *str)
{
    char *text, *encrypted, *salt;
    salt = crypt_gensalt("$2b$", 15, NULL, 0);
    encrypted = crypt(text, salt);
    strcpy(str, encrypted);
}

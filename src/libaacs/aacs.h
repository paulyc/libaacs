/*
 * libaacs by Doom9 ppl 2009
 * The aim of libaacs is to achieve a complete open-source implementation of the AACS spec
 * The spec is freely available at http://www.aacsla.com/specifications/
 */

#ifndef AACS_H_
#define AACS_H_

#include <stdint.h>
#include <unistd.h>
#include <openssl/aes.h>

#include "mkb.h"
#include "../file/configfile.h"

#define LIBAACS_VERSION "1.0"

typedef struct aacs_keys AACS_KEYS;
struct aacs_keys {
    uint8_t pk[16], mk[16], vuk[16], vid[16];
    uint8_t *uks;           // unit key array (size = 16 * num_uks, each key is at 16-byte offset)
    uint16_t num_uks;       // number of unit keys
    uint8_t iv[16];
    AES_KEY aes;
    CONFIGFILE *kf;
};

AACS_KEYS *aacs_open(const char *path, const char *keyfile_path);
void aacs_close(AACS_KEYS *aacs);
int aacs_decrypt_unit(AACS_KEYS *aacs, uint8_t *buf, uint32_t len, uint64_t offset);
uint8_t *aacs_get_vid(AACS_KEYS *aacs);

#endif /* AACS_H_ */

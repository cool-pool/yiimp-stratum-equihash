#include "RandomX/src/bytecode_machine.hpp"
#include "RandomX/src/dataset.hpp"
#include "RandomX/src/blake2/endian.h"
#include "RandomX/src/blake2/blake2.h"
#include "RandomX/src/blake2_generator.hpp"
#include "RandomX/src/superscalar.hpp"
#include "RandomX/src/reciprocal.h"
#include "RandomX/src/intrin_portable.h"
#include "RandomX/src/jit_compiler.hpp"
#include "RandomX/src/aes_hash.hpp"
#include "RandomX/src/randomx.h"
#include <openssl/sha.h>
#include "uint256.h"

#include <cassert>

//! barrystyle 04022020
bool is_init = false;
randomx_flags flags;
randomx_cache* cache;
randomx_vm* vm = nullptr;
uint256 *keyCache = (uint256*)malloc(32);

void randomx_init()
{
        memset(keyCache,1,32);
        flags = randomx_get_flags();
        cache = randomx_alloc_cache(flags);
        randomx_init_cache(cache, keyCache, 32);
}

void randomx_shutoff()
{
        randomx_destroy_vm(vm);
        vm = nullptr;
        randomx_release_cache(cache);
}

void setseed(const char *seed)
{
	memcpy(keyCache, seed, 32);
}

void randomx_hash(const char* input, char* output, unsigned int len)
{
        if (!is_init) {
            randomx_init();
            is_init = true;
        }

        char hash[32];
        randomx_init_cache(cache, keyCache, 32);
        vm = randomx_create_vm(flags, cache, nullptr);
        randomx_calculate_hash(vm, input, len, hash);
        randomx_destroy_vm(vm);
        memcpy(output, hash, 32);
}

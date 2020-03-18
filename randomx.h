#include "uint256.h"

void randomx_init();
void randomx_shutoff();
void setseed(const char *seed);
uint256 randomxhash(const char* block);
void randomx_hash(const char* input, char* output, unsigned int len);


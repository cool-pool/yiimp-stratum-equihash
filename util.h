#ifndef _UTIL_H
#define _UTIL_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "json.h"

struct YAAMP_CLIENT;

struct COMMONLISTITEM
{
	void* data;

	struct COMMONLISTITEM* next;
	struct COMMONLISTITEM* prev;
};

typedef COMMONLISTITEM* CLI;

typedef void (*LISTFREEPARAM)(void*);

class CommonList
{
public:
	CommonList();
	~CommonList();

	CLI AddHead(void* data);
	CLI AddTail(void* data);

	void Delete(CLI item);
	void Delete(void* data);

	void DeleteAll(LISTFREEPARAM freeparam);

	CLI Find(void* data);
	void Swap(CLI i1, CLI i2);

	void Enter();
	void Leave();

	pthread_mutex_t mutex;
	int count;

	CLI first;
	CLI last;
};

void CommonLock(pthread_mutex_t* mutex);
void CommonUnlock(pthread_mutex_t* mutex);

//////////////////////////////////////////////////////////////////////////

bool json_get_bool(json_value* json, const char* name);
json_int_t json_get_int(json_value* json, const char* name);
double json_get_double(json_value* json, const char* name);
const char* json_get_string(json_value* json, const char* name);
json_value* json_get_array(json_value* json, const char* name);
json_value* json_get_object(json_value* json, const char* name);

void yaamp_create_mutex(pthread_mutex_t* mutex);
bool yaamp_error(char const* message);

const char* header_value(const char* data, const char* search, char* value);

void initlog(const char* algo);
void closelogs();

void debuglog(const char* format, ...);
void stratumlog(const char* format, ...);
void stratumlogdate(const char* format, ...);
void clientlog(YAAMP_CLIENT* client, const char* format, ...);
void rejectlog(const char* format, ...);

//////////////////////////////////////////////////////////////////////////

std::vector<std::string> merkle_steps(std::vector<std::string> input);
std::string merkle_with_first(std::vector<std::string> steps, std::string f);

//////////////////////////////////////////////////////////////////////////

int base58_decode(const char* input, char* output);
int is_base58(char* input);

void base64_encode(char* base64, const char* normal);
void base64_decode(char* normal, const char* base64);

void ser_number(int n, char* s);

void ser_string_be(const char* input, char* output, int len);
void ser_string_be2(const char* input, char* output, int len);

void string_be(const char* input, char* output);
void string_be1(char* s);

bool ishexa(char* hex, int len);

void hexlify(char* hex, const unsigned char* bin, int len);
void binlify(unsigned char* bin, const char* hex);

unsigned int htoi(const char* s);
uint64_t htoi64(const char* s);

uint64_t decode_compact(const char* input);

uint64_t diff_to_target(double difficulty);
double target_to_diff(uint64_t target);

void bits2target(uint32_t nbits, char* out_target);
uint32_t target2bits(const char* target);
void diff_to_target_equi(uint32_t* target, double diff);
double target_to_diff_equi(uint32_t* target);
double nbits_to_diff_equi(uint32_t* nbits);

uint64_t get_hash_difficulty(unsigned char* input);

long long current_timestamp();
long long current_timestamp_dms();

int opened_files();
int resident_size();

void string_lower(char* s);
void string_upper(char* s);

int getblocheight(const char* coinb1);

//////////////////////////////////////////////////////////////////////////

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//////////////////////////////////////////////////////////////////////////

#if !HAVE_DECL_LE16DEC
static inline uint16_t le16dec(const void* pp)
{
	const uint8_t* p = (uint8_t const*)pp;
	return ((uint16_t)(p[0]) + ((uint16_t)(p[1]) << 8));
}
#endif

#ifndef WIN32
static inline uint32_t bswap32(uint32_t x) {
	__asm__ __volatile__("bswapl %0" : "=r" (x) : "0" (x));
	return x;
}
#else
#define bswap32(x)  ((((x) & 0x000000ff) << 24) | \
(((x) & 0x0000ff00) << 8) | \
(((x) & 0x00ff0000) >> 8) | \
(((x) & 0xff000000) >> 24))
#endif // !WIN32
uint64_t share_to_target(double diff);

#endif // !_UTIL_H

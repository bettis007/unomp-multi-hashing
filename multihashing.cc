#include <node_api.h>
#include <stdint.h>
#include <cstring> // Include for strcmp

extern "C" {
#include "bcrypt.h"
#include "keccak.h"
#include "quark.h"
#include "scryptjane.h"
#include "scryptn.h"
#include "yescrypt/yescrypt.h"
#include "yescrypt/sha256_Y.h"
#include "neoscrypt.h"
#include "skein.h"
#include "x11.h"
#include "groestl.h"
#include "blake.h"
#include "fugue.h"
#include "qubit.h"
#include "s3.h"
#include "hefty1.h"
}

napi_value HashFunction(napi_env env, napi_callback_info info) {
size_t argc = 2;
napi_value argv[2];
napi_value result;

napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

if (argc < 2) {
napi_throw_error(env, nullptr, "Two arguments expected: algorithm and data.");
return nullptr;
}

// Convert arguments to native types
size_t algorithm_len, data_len;
char algorithm[128];
napi_get_value_string_utf8(env, argv[0], algorithm, sizeof(algorithm), &algorithm_len);

uint8_t *data;
napi_get_buffer_info(env, argv[1], (void **)&data, &data_len);

uint8_t hash[32];

if (strcmp(algorithm, "bcrypt") == 0) {
bcrypt_hash((const char*)data, (char*)hash); // Cast data to const char*
} else if (strcmp(algorithm, "keccak") == 0) {
keccak_hash((const char*)data, data_len, (char*)hash); // Explicit cast for keccak_hash
} else if (strcmp(algorithm, "quark") == 0) {
quark_hash((const char*)data, data_len, (char*)hash); // Cast data to const char*
} else {
napi_throw_error(env, nullptr, "Unsupported algorithm.");
return nullptr;
}

napi_create_buffer_copy(env, 32, hash, nullptr, &result);
return result;
}

napi_value Init(napi_env env, napi_value exports) {
napi_property_descriptor desc = { "hash", nullptr, HashFunction, nullptr, nullptr, nullptr, napi_default, nullptr };
napi_define_properties(env, exports, 1, &desc);
return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

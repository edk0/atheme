/*
 * BLAKE2 reference C implementation
 * Retrieved from <https://github.com/BLAKE2/BLAKE2/>
 *
 * Copyright (C) 2012 Samuel Neves <sneves@dei.uc.pt>
 *
 * You may use this work under the terms of a Creative Commons CC0 1.0
 * License/Waiver, the OpenSSL Licence, or the Apache Public License 2.0,
 * at your option. The terms of these licenses can be found at:
 *
 * - CC0 1.0 Universal <http://creativecommons.org/publicdomain/zero/1.0>
 * - OpenSSL License   <https://www.openssl.org/source/license.html>
 * - Apache 2.0        <http://www.apache.org/licenses/LICENSE-2.0>
 *
 * More information about the BLAKE2 hash function can be found at
 * <https://blake2.net/>.
 *
 * Heavily modified for use as part of a password hashing module in Atheme
 * IRC Services <https://github.com/atheme/atheme/> by Aaron M. D. Jones
 * <aaronmdjones@gmail.com> (2017-2018)
 */

#ifndef ATHEME_MOD_CRYPTO_BLAKE2B_H
#define ATHEME_MOD_CRYPTO_BLAKE2B_H 1

#include "atheme.h"

#if (defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || \
    defined(__LITTLE_ENDIAN__) || defined(__ARMEL__) || defined(__MIPSEL__) || defined(__AARCH64EL__) || \
    defined(__amd64__) || defined(__i386__) || defined(_M_IX86) || defined(_M_X64) || defined(_M_AMD64)

#define NATIVE_LITTLE_ENDIAN
#endif

#define BLAKE2B_BLOCKLEN        0x80
#define BLAKE2B_HASHLEN         0x40
#define BLAKE2B_HASHLEN_HALF    0x20
#define BLAKE2B_PERSLEN         0x10
#define BLAKE2B_SALTLEN         0x10

struct blake2b_state
{
	uint64_t        h[0x08];
	uint64_t        t[0x02];
	uint64_t        f[0x02];
	size_t          buflen;
	size_t          outlen;
	uint8_t         last_node;
	uint8_t         buf[BLAKE2B_BLOCKLEN];
};

struct blake2b_functions
{
	void          (*b2b_store32)(uint8_t *, uint32_t);
	void          (*b2b_store64)(uint8_t *, uint64_t);
	uint64_t      (*b2b_load64)(const uint8_t *);
	uint64_t      (*b2b_rotr64)(uint64_t, unsigned int);
	uint64_t      (*b2b_fBlaMka)(uint64_t, uint64_t);
	bool          (*b2b_init)(struct blake2b_state *, size_t, const void *, size_t) ATHEME_FATTR_WUR;
	bool          (*b2b_update)(struct blake2b_state *, const uint8_t *, size_t) ATHEME_FATTR_WUR;
	bool          (*b2b_final)(struct blake2b_state *, uint8_t *) ATHEME_FATTR_WUR;
	bool          (*b2b_full)(const uint8_t *, size_t, const void *, size_t, uint8_t *, size_t) ATHEME_FATTR_WUR;
	bool          (*b2b_long)(const uint8_t *, size_t, const void *, size_t, uint8_t *, size_t) ATHEME_FATTR_WUR;
};

#endif /* !ATHEME_MOD_CRYPTO_BLAKE2B_H */

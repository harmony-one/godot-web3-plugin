#include "keccak.h"

#include "thirdparty/trezor-crypto/sha3.h"

void Keccak::hash(const unsigned char* p_data, int p_len, unsigned char r_digest[32]) {
  keccak_256(p_data, p_len, r_digest);
}

Error Keccak::update(PackedByteArray p_chunk) {
  ERR_FAIL_COND_V(ctx == nullptr, ERR_UNCONFIGURED);
  size_t len = p_chunk.size();
  ERR_FAIL_COND_V(len == 0, FAILED);
  PackedByteArray r = p_chunk;
  keccak_Update((SHA3_CTX *)ctx, &r[0], len);
  return OK;
}

PackedByteArray Keccak::finish() {
  ERR_FAIL_COND_V(ctx == nullptr, PackedByteArray());
  PackedByteArray out;
  out.resize(32);
  keccak_Final((SHA3_CTX *)ctx, (unsigned char*) out.ptr());
  return out;
}

void Keccak::_bind_methods() {
  ClassDB::bind_method(D_METHOD("update", "chunk"), &Keccak::update);
  ClassDB::bind_method(D_METHOD("finish"), &Keccak::finish);
}

Keccak::Keccak() {
  ctx = memalloc(sizeof(SHA3_CTX));
  keccak_256_Init((SHA3_CTX *)ctx);
}

Keccak::~Keccak() {
  memfree((SHA3_CTX *)ctx);
}

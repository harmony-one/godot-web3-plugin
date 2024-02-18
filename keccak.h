#ifndef KECCAK_H
#define KECCAK_H

#include "core/object/ref_counted.h"

class Keccak : public RefCounted {
  GDCLASS(Keccak, RefCounted);

private:
  void *ctx;

protected:
  static void _bind_methods();

public:
  static void hash(const unsigned char* p_data, int p_len, unsigned char r_digest[32]);

  Error update(PackedByteArray p_chunk);
  PackedByteArray finish();

  Keccak();
  ~Keccak();
};

#endif // KECCAK_H

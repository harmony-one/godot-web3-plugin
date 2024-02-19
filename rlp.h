#ifndef RLP_H
#define RLP_H

#include "core/object/ref_counted.h"

class RLP : public RefCounted {
  GDCLASS(RLP, RefCounted);

  PackedByteArray hex_to_bytes(const String &p_hex);

protected:
  static void _bind_methods();

public:
  PackedByteArray encode_length(int length, int offset);
  PackedByteArray encode(const String &p_hex);
};

#endif // RLP_H
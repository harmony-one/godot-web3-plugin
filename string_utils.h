#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "core/variant/variant.h"

class StringUtils {
public:
  static PackedByteArray hex_to_bytes(const String &p_hex);
};

#endif // STRING_UTILS_H
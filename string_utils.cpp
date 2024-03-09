#include "string_utils.h"

PackedByteArray StringUtils::hex_to_bytes(const String &p_hex) {
  String hex = p_hex.trim_prefix("0x");
  hex = hex.lpad(hex.length() + hex.length() % 2, "0");

  PackedByteArray bin;
  for (int i = 0; i < hex.length() - 1; i += 2) {
    bin.append(hex.substr(i, 2).hex_to_int());
  }

  return bin;
}
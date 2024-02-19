#ifndef WALLET_H
#define WALLET_H

#include "core/object/ref_counted.h"

#include "transaction.h"

class Wallet : public RefCounted {
  GDCLASS(Wallet, RefCounted);

  String address;
  uint8_t private_key[32];

protected:
  static void _bind_methods();

public:
  String get_address() const;
  
  Error set_private_key(const String &p_private_key);
  Error sign_transaction(Transaction &p_transaction);
};

#endif // WALLET_H
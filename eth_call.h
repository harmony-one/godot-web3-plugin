#ifndef ETH_CALL_H
#define ETH_CALL_H

#include "scene/main/node.h"

#include "abi.h"
#include "rpc_request.h"

class EthCall : public Node {
  GDCLASS(EthCall, Node);

  Ref<ABI> abi;

  RPCRequest *rpc_request = nullptr;
  void _request_completed(int p_status, const Dictionary &p_result);
  
protected:
  static void _bind_methods();

public:
  void set_abi(const Ref<ABI> &p_abi);
  Ref<ABI> get_abi() const;

  Error request(const String &p_to, const String &p_from, const String &p_name, const Array &p_inputs);

  EthCall();
};

#endif // ETH_CALL_H
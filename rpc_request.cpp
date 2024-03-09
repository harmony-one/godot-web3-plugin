#include "rpc_request.h"

#include "core/io/json.h"
#include "core/config/project_settings.h"
#include "scene/main/http_request.h"

Error RPCRequest::request(const String &p_method, const Array &p_params) {
  String url = GLOBAL_GET("web3/rpc_url");
  ERR_FAIL_COND_V_MSG(url.is_empty(), ERR_UNCONFIGURED, "RPC URL is empty in project settings.");

  Dictionary ddata;
  ddata["id"] = 1;
  ddata["jsonrpc"] = "2.0";
  ddata["method"] = p_method;
  ddata["params"] = p_params;
  JSON parsed;
  return http_request->request(url, Vector<String>(), HTTPClient::METHOD_POST, stringify_variants(ddata));
}

void RPCRequest::_request_completed(int p_status, int p_code, const PackedStringArray &headers, const PackedByteArray &p_data) {
  if (p_status != HTTPRequest::RESULT_SUCCESS || p_code != 200) {
    emit_signal("request_completed", RESULT_HTTP_ERROR, Dictionary());
    return;
  }

  String response_json;
  response_json.parse_utf8((const char *)p_data.ptr(), p_data.size());

  Variant json;
  JSON rj;
  Error err = rj.parse(response_json, true);
  if (err != OK) {
    emit_signal("request_completed", RESULT_JSON_ERROR, Dictionary());
    return;
  }

  Dictionary result = json;
  if (result.has("error")) {
    emit_signal("request_completed", RESULT_RPC_ERROR, result);
    return;
  }

  emit_signal("request_completed", RESULT_SUCCESS, result);
}

void RPCRequest::_bind_methods() {
  ClassDB::bind_method(D_METHOD("request", "method", "params"), &RPCRequest::request);
  ClassDB::bind_method("_request_completed", &RPCRequest::_request_completed);

  ADD_SIGNAL(MethodInfo("request_completed", PropertyInfo(Variant::INT, "status"), PropertyInfo(Variant::DICTIONARY, "result")));

  BIND_ENUM_CONSTANT(RESULT_SUCCESS);
  BIND_ENUM_CONSTANT(RESULT_HTTP_ERROR);
  BIND_ENUM_CONSTANT(RESULT_JSON_ERROR);
}

RPCRequest::RPCRequest() {
  http_request = memnew(HTTPRequest);
  add_child(http_request);
  http_request->connect("request_completed", callable_mp(this, &RPCRequest::_request_completed));
}
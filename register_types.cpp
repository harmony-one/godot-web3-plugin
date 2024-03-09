#include "register_types.h"

#include "abi.h"
#include "eth_balance.h"
#include "eth_call.h"
#include "eth_transaction.h"
#include "keccak.h"
#include "rlp.h"
#include "rpc_request.h"
#include "transaction.h"
#include "wallet.h"

#include "core/object/class_db.h"
#include "core/config/project_settings.h"

static Ref<ResourceFormatLoaderABI> abi_loader;

void uninitialize_web3_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

   ResourceLoader::remove_resource_format_loader(abi_loader);
   abi_loader.unref();
}

void initialize_web3_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<ABI>();
   ClassDB::register_class<EthBalance>();
   ClassDB::register_class<EthCall>();
   ClassDB::register_class<EthTransaction>();
   ClassDB::register_class<Keccak>();
   ClassDB::register_class<RLP>();
   ClassDB::register_class<RPCRequest>();
   ClassDB::register_class<Transaction>();
   ClassDB::register_class<Wallet>();

   abi_loader.instantiate();
   ResourceLoader::add_resource_format_loader(abi_loader);

   GLOBAL_DEF("web3/rpc_url", "");
}

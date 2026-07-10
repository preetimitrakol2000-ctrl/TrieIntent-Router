import ctypes
import os
import sys

class TrieBridge:
    def __init__(self):
        if not os.path.exists("./libtrie.so") and not os.path.exists("./libtrie.dll"):
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o libtrie.dll trie_router.c")
                lib_path = "./libtrie.dll"
            else:
                os.system("gcc -shared -fPIC -o libtrie.so trie_router.c")
                lib_path = "./libtrie.so"
        else:
            lib_path = "./libtrie.dll" if sys.platform.startswith("win") else "./libtrie.so"

        self.lib = ctypes.CDLL(lib_path)
        self.lib.init_trie_node.restype = ctypes.c_void_p
        self.lib.insert_intent_prefix.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int]
        self.lib.resolve_intent_shard.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.resolve_intent_shard.restype = ctypes.c_int
        
        self.root_ptr = self.lib.init_trie_node()

    def map_prefix_intent(self, prefix_keyword: str, destination_shard_id: int):
        self.lib.insert_intent_prefix(self.root_ptr, prefix_keyword.lower().encode('utf-8'), destination_shard_id)

    def route_query_string(self, query_keyword: str) -> int:
        return self.lib.resolve_intent_shard(self.root_ptr, query_keyword.lower().encode('utf-8'))

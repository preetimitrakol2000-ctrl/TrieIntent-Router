from trie_bridge import TrieBridge

if __name__ == "__main__":
    intent_trie = TrieBridge()

    # Route specific runtime query prefixes directly to specialized database shards
    intent_trie.map_prefix_intent(prefix_keyword="auth", destination_shard_id=5001)
    intent_trie.map_prefix_intent(prefix_keyword="logs", destination_shard_id=5002)

    test_token = "auth"
    shard_target = intent_trie.route_query_string(test_token)

    print("=== TRIEINTENT-ROUTER PREFIX GATEWAY ===")
    print(f"[*] Parsed Prefix Token: '{test_token}' -> Directly Routed to Index Shard Workspace: [{shard_target}]")

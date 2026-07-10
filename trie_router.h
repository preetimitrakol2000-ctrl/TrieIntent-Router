#ifndef TRIE_ROUTER_H
#define TRIE_ROUTER_H

typedef struct TrieNode TrieNode;
TrieNode* init_trie_node();
void insert_intent_prefix(TrieNode* root, const char* key, int shard_id);
int resolve_intent_shard(TrieNode* root, const char* key);

#endif

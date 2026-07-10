#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children_branches[ALPHABET_SIZE];
    int linked_cluster_shard;
    int is_end_of_word;
} TrieNode;

#ifdef _WIN32
    __declspec(dllexport) TrieNode* init_trie_node();
    __declspec(dllexport) void insert_intent_prefix(TrieNode* root, const char* key, int shard_id);
    __declspec(dllexport) int resolve_intent_shard(TrieNode* root, const char* key);
#endif

TrieNode* init_trie_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    node->linked_cluster_shard = -1;
    for (int i = 0; i < ALPHABET_SIZE; i++) node->children_branches[i] = NULL;
    return node;
}

void insert_intent_prefix(TrieNode* root, const char* key, int shard_id) {
    TrieNode* curr = root;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        int index = key[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) continue;
        if (!curr->children_branches[index]) {
            curr->children_branches[index] = init_trie_node();
        }
        curr = curr->children_branches[index];
    }
    curr->is_end_of_word = 1;
    curr->linked_cluster_shard = shard_id;
}

int resolve_intent_shard(TrieNode* root, const char* key) {
    TrieNode* curr = root;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        int index = key[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) return -1;
        if (!curr->children_branches[index]) return -1;
        curr = curr->children_branches[index];
    }
    return (curr != NULL && curr->is_end_of_word) ? curr->linked_cluster_shard : -1;
}

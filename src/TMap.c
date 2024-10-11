#include "t.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

typedef struct Node {
  char *key;
  void *value;
  void (*deleteValue)(void *value);
  struct Node *left;
  struct Node *right;
  int height;
} *Node;

struct TMap {
  struct Node *root;
};

static int int_max(int self, int other) { return self > other ? self : other; }

static Node createNode(const char *key, void *value,
                       void (*deleteValue)(void *value)) {
  Node node = (struct Node *)t_malloc(sizeof(struct Node));
  node->key = t_strdup(key);
  node->value = value;
  node->left = node->right = NULL;
  node->height = 1;
  return node;
}

static int getHeight(Node node) { return node == NULL ? 0 : node->height; }

static int getBalanceFactor(Node node) {
  return node == NULL ? 0 : getHeight(node->left) - getHeight(node->right);
}

static Node rotateRight(Node y) {
  Node x = y->left;
  Node T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = 1 + int_max(getHeight(y->left), getHeight(y->right));
  x->height = 1 + int_max(getHeight(x->left), getHeight(x->right));

  return x;
}

static Node rotateLeft(Node x) {
  Node y = x->right;
  Node T2 = y->left;

  y->left = x;
  x->right = T2;

  y->height = 1 + int_max(getHeight(y->left), getHeight(y->right));
  x->height = 1 + int_max(getHeight(x->left), getHeight(x->right));

  return y;
}

static Node balanceNode(Node node) {
  int balance = getBalanceFactor(node);

  if (balance > 1) {
    if (getBalanceFactor(node->left) < 0) {
      node->left = rotateLeft(node->left);
    }
    return rotateRight(node);
  }

  if (balance < -1) {
    if (getBalanceFactor(node->right) > 0) {
      node->right = rotateRight(node->right);
    }
    return rotateLeft(node);
  }

  return node;
}

static Node insertNode(Node node, const char *key, void *value,
                       void (*deleteValue)(void *value)) {
  if (node == NULL) {
    return createNode(key, value, deleteValue);
  }

  int leading_same = 0;
  while (node->key[leading_same] != '\0' && key[leading_same] != '\0' &&
         node->key[leading_same] == key[leading_same]) {
    leading_same++;
  }
  const int cmp = strcmp(node->key + leading_same, key + leading_same);

  if (cmp > 0) {
    node->left = insertNode(node->left, key, value, deleteValue);
  } else if (cmp < 0) {
    node->right = insertNode(node->right, key, value, deleteValue);
  } else {
    abort();
  }

  node->height = 1 + int_max(getHeight(node->left), getHeight(node->right));

  return balanceNode(node);
}

DLLEXPORT TMap TMap_new() {
  const struct TMap result = {NULL};
  return t_memdup(&result, sizeof(result));
}

DLLEXPORT void TMap_insert(TMap map, const char *key, void *value,
                           void (*deleteValue)(void *value)) {
  map->root = insertNode(map->root, key, value, deleteValue);
}

DLLEXPORT void *TMap_search(TMap map, const char *key) {
  Node current = map->root;
  int leading_same = 0;
  while (current != NULL) {
    while (current->key[leading_same] != '\0' && key[leading_same] != '\0' &&
           current->key[leading_same] == key[leading_same]) {
      leading_same++;
    }
    const int cmp = strcmp(current->key + leading_same, key + leading_same);

    if (cmp == 0) {
      return current->value;
    } else if (cmp > 0) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return NULL;
}

static void deleteNode(Node node) {
  if (!node) {
    return;
  }
  deleteNode(node->left);
  deleteNode(node->right);
  if (node->deleteValue) {
    node->deleteValue(node->value);
  }
  free(node->key);
  free(node);
}

DLLEXPORT void TMap_delete(TMap self) {
  deleteNode(self->root);
  free(self);
}

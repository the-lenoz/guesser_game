#ifndef TREE
#define TREE

#include <stdio.h>


typedef struct _tree {
  char *value;
  struct _tree *lchild;
  struct _tree *rchild;
} tree;

typedef int treeStatus;

tree *tree_init();
int tree_destroy(tree *t);

treeStatus tree_check(tree *t);

treeStatus tree_print(tree *t, FILE *fp);

typedef enum { PREFIX, INFIX, POSTFIX } trav_t;
typedef int (*trav_cb) (tree*);

treeStatus tree_DFS(tree *t, trav_cb callback, trav_t trav_type);


tree *read_tree(FILE *fp);

#endif // TREE

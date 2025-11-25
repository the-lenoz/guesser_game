#include <stdio.h>
#include "tree.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

#define CPRINTF(fmt, color, ...) printf(color fmt RESET, ##__VA_ARGS__)
#define PRINTF_GREEN(fmt, ...) CPRINTF(fmt, GRN, ##__VA_ARGS__)
#define PRINTF_RED(fmt, ...) CPRINTF(fmt, RED, ##__VA_ARGS__)
#define PRINTF_YEL(fmt, ...) CPRINTF(fmt, YEL, ##__VA_ARGS__)


int test_print() {
  tree *t = tree_init();

  *t = (tree){"foo", tree_init(), tree_init()};
  *t->lchild = (tree){"spam", NULL, NULL};
  *t->rchild = (tree){"eggs", NULL, NULL};

  tree_print(t, stdout);
  putchar('\n');

  tree_destroy(t);
  
  return 0;
}

int test_read() {
  tree *t = read_tree(stdin);
  
  tree_print(t, stdout);
  putchar('\n');

  return 0;
}



int test_tree() {
  int status = 0;
  PRINTF_YEL("Testing tree.\n");

  status |= test_print();
  status |= test_read();  

  PRINTF_GREEN("Tree passed all tests!\n");
  return status;
}    


int main(void) {
  int status = 0;

  PRINTF_YEL("Starting tests!\n");

  status |= test_tree();

  if (status == 0) PRINTF_GREEN("All tests passed!\n");    
  
  return status;  
}    

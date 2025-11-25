#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "guesser.h"
#include "tree.h"

typedef enum {GUESSING_L, GUESSING_R, GUESSED, WRONG, NOT_FOUND} guesserStatus;

tree *read_guesser_data(const char *data_path) {
  FILE *fp = fopen(data_path, "r");
  if (fp == NULL)
    return NULL;
  tree *t = read_tree(fp);
  fclose(fp);
  return t;
}

int write_guesser_data(tree *data, const char *path) {
  FILE *fp = fopen(path, "w");

  if (fp == NULL)
    return -1;

  tree_print(data, fp);

  fclose(fp);
  
  return 0;  
}    

guesserStatus guess(tree *guesser_tree) {
  if (!guesser_tree) {
    return NOT_FOUND;
  }

  printf("%s", guesser_tree->value);

  guesserStatus status = GUESSING_L;

  if (guesser_tree->lchild || guesser_tree->rchild)
    putchar('?');
  else
    status = GUESSED;

  printf("\n(y/n):");

  int c = getchar();

  if (c == 'y') {
    status = status == GUESSED ? GUESSED : GUESSING_R;
  } else {
    status = status == GUESSED ? WRONG : GUESSING_L;
  }

  getchar(); // swallow \n
  
  return status;
}

int add_new_ch(tree **ptr) {
  if (!ptr || *ptr) return -1; 

  puts("Who is it?");
  putchar(':');

  char *name = NULL;
  size_t len = 0;
  getline(&name, &len, stdin);

  if (!name || !len) return -1;
  
  name[strlen(name) - 1] = '\0';

  *ptr = tree_init();
  (*ptr)->value = name;
  
  return 0;
}

int add_new_ch_update(tree **conflicted) {
  if (!conflicted || !*conflicted)
    return -1;

  puts("How does your character differ from mine?");
  putchar(':');
  char *difference = NULL;
  size_t len = 0;
  getline(&difference, &len, stdin);

  if (!difference || !len) return -1;
  
  difference[strlen(difference) - 1] = '\0';

  tree *diff = tree_init();
  diff->value = difference;
  diff->lchild = *conflicted;

  *conflicted = diff;
  
  return add_new_ch(&(*conflicted)->rchild);
}

int run_guesser_game(const char *guesser_database_path) {
  tree *guesser_data = read_guesser_data(guesser_database_path);

  //if (!guesser_data) return fprintf(stderr, "Can't read guesser database from '%s'\n", guesser_database_path), -1;

  guesserStatus status = GUESSING_L;
  tree **current_guesser_data = &guesser_data;
  while (status == GUESSING_L || status == GUESSING_R) {
    status = guess(*current_guesser_data);
    switch (status) {
    case NOT_FOUND:
      puts("Hm... I don't know!");
      if (add_new_ch(current_guesser_data) == 0)
        puts("Now I know a bit more!");
      else fprintf(stderr, "An error occured!\n");
      break;
    case WRONG:
      puts("I'm sorry, my bad.");
      add_new_ch_update(current_guesser_data);
      puts("Now I know a bit more!");      
      break;
    case GUESSED:
      puts("Good for me!");
      break;
    case GUESSING_L:
      current_guesser_data = &(*current_guesser_data)->lchild;
      break;
    case GUESSING_R:
      current_guesser_data = &(*current_guesser_data)->rchild;
      break;
    default:
      break;
    }
  }

  write_guesser_data(guesser_data, guesser_database_path)
      && fprintf(stderr, "ERROR: Can't save data!\n");

  tree_destroy(guesser_data);
  
  return 0;  
}  

#include <stdio.h>
#include "guesser.h"


int main(int argc, char **argv) {
  if (argc != 2)
    return fprintf(stderr, "Usage: %s database_file\n", argv[0]), -1;

  return run_guesser_game(argv[1]);  
}    

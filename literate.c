
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main(int argc, char** argv) 
{
  if (argc < 3) {
    // print usage
    perror("Usage: literate -[s|d] <input>\n");
    perror("  Ex.: literate -s main.lc > main.c\n");
    perror("  Ex.: literate -d main.lc > main.md\n");
    exit(EXIT_FAILURE);
  }

  // get input filename from commandline
  const char* input_path = argv[2]; 

  // get command line flag (-s or -d)
  const int should_print_code = (strncmp(argv[1], "-s", 2)==0) ? 1 : 0;

  FILE *fp = fopen( input_path, "r");  // open file for reading
  if (fp == NULL) {
    perror("Fatal: Unable to open input file.\n");
    exit(EXIT_FAILURE);
  }
  
  int last_char_was_newline = 0; // false
  int in_code = 0;               // false
  char ch = ' ';                 // a safe default

  // loop through every character
  while ( (ch = (char) fgetc(fp) ) != EOF ) {

    // a super simple parser
    if (ch == '\n') {

      // don't forget to echo the newline
      if (in_code == should_print_code) { printf("%c",ch); }

      // update parser state
      last_char_was_newline = 1; 
      in_code = 0; 
      continue; 

    } else if (last_char_was_newline && ch == '>') { 
      // ... update parser state 
      in_code = 1;
      continue;

    } else if (last_char_was_newline && ch == ' ') {
      // ... skip first space after ">"
      last_char_was_newline = 0;
      continue;

    } 
    last_char_was_newline = 0;

    // if we are in the block we expect, output code
    if (in_code == should_print_code) {
      printf("%c",ch);
    } 
  }

  // close the open file
  fclose(fp);

  return EXIT_SUCCESS;
}

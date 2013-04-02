
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main(int argc, char** argv) 
{
  if (argc < 3) {
    // print usage
    printf("Usage: literate -[s|d] <input>\n");
    printf("  Ex.: literate -s main.lc > main.c\n");
    printf("  Ex.: literate -d main.lc > main.md\n");
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
  int in_desired_block = 0;      // false
  char ch = ' ';                 // a safe default

  // loop through every character
  while ( (ch = (char) fgetc(fp) ) != EOF ) {

    // an awkward boolean logic, but this figures out whether this character should be visible.
    in_desired_block = (!should_print_code || (in_code == should_print_code));

    // a super simple parser
    if (ch == '\n') {
      // update parser state
      last_char_was_newline = 1; 
      in_code = 0; 

      // print newline when in desired block
      if (in_desired_block) { 
        printf("%c",ch); 
      }
      continue; 

    } else if (last_char_was_newline && ch == '>') { 
      // ... we've detected a code block
      in_code = 1;
      continue;

    } else if (last_char_was_newline && ch == ' ') {
      // ... skip first space after ">"
      last_char_was_newline = 0;
      continue;

    } 
    last_char_was_newline = 0;

    // if we should, output the current character
    if (in_desired_block) printf("%c",ch); 

  }

  // close the open file
  fclose(fp);

  return EXIT_SUCCESS;
}

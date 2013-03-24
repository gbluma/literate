
An incredibly simple tool for handling literate programming.

# Usage

~~~~
literate -s example.lc > example.c
=> outputs the source code from example.lc

literate -d example.lc > example.md
=> outputs the documentation from example.lc
~~~~

# Formatting

There are only two rules. First, normal text is considered a comment. Second, lines that start
with ">" are considered code.

~~~~
This is a top level comment.

This is also a comment.

> /* this is a comment that will show up in code */
>
> int main(int argc, char** argv) {
>     printf("Hello world\n");
>     return 0;
> }

Closing comments.
~~~~



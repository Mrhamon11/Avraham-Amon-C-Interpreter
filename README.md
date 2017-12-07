<h1>Top Down Parser</h1>

This project creates a parse tree from the tokens produced and the EBNF grammar
found in the file called "grammar-and-example-code.txt". The parser file is 
called Parser_Main.c and even though it requires the Tokenizer_Main.c file to 
function, this file is included in the top of Parser_Main.c, and thus, should not
be included in the gcc compile command.

The file that will be run by default is called CFile.c and it contains a sample 
program that follows the rules of the grammar. It is also included here below 
the grammar in the file listed above.

To run this program, open the file location in a terminal and compile
Parser_Main.c in the with the following command: 


<code>gcc Parser_Main.c -o Parser</code>

If no command line arguments are included, CFile.c will be used as the basis for
making the tree. If another file is passed as a command line argument, the 
parser will produce the parse tree for the contained code assuming it follows
the grammar rules.
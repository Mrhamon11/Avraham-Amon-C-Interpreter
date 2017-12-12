<h1>Interpreter</h1>

This project creates a parse tree and symbol table from the tokens produced from
included tokenizer program. The parse tree follows the rules of the EBNF 
grammar found in the file called "grammar-and-example-code.txt". After the 
parse tree is created, the interpreter will then run, using the generated 
parse tree and symbol table to execute the commands in of the input file.
The Interpreter file is called Interpreter.c and even though it requires the 
Parser.c and Tokenizer.c files to function properly, these file is included 
in the top of Interpreter.c file as preprocessor declaration. Thus, they 
should not be included in the gcc compile command.

The parser will catch any syntax errors that might exist, print as many of them
as it can find out to the screen, and then terminate the application. If any 
runtime errors exist, the Interpreter should print them to the screen, and 
terminate the application.

The file that will be run by default is called CFile.c and it contains a sample 
program that follows the rules of the grammar. If this project is opened in 
CLion, the compiled executable will reside in the cmake-build-debug folder 
supplied, and as such, the CFile.c that will be run will be the one run inside
of that folder. However, if one wishes to compile the Interpreter themselves,
a copy of CFile.c is included in the same directory as the Interpreter.c file
for convenience.

To compile this program, open the file location in a terminal and compile
Interpreter.c in the with the following command: 


<code>gcc Interpreter.c -o Interpreter</code>

To run the program, enter: <code>./Interpreter</code> in a terminal in the 
same directory as the executable file.

If no command line arguments are included, CFile.c will be used as the basis for
making the tree. If another file is passed as a command line argument, this 
program will execute the file assuming it follows the rules of the parse tree.


<h2>CFile.c Program</h2>

If one wishes to use the default test file included with this project for testing
purposes, please note that when the program seems to be doing nothing, it is actually
waiting for user input. A <code>cin</code> statement is the same as a <code>scanf</code>
in C. The program will first take user input from the console and store it in a variable
<code>char c</code>, the value of which will be printed back to the console. It then 
compares that variable to 'Z'. If the variable equals 'Z', a value of 1 will be printed,
and 0 will be printed otherwise. The program then asks for two more int arguments since 
the variables that these values will be stored in are ints. It will then do some calculations
and print out three values. Read the code to see exactly what is going on. 

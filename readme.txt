Michael Sabbagh
Tokenizer readme

This tokenizer takes 2 command line arguments. The first is a list of delimiters, 
and the second is the string which is to be tokenized. Upon running the program, 
the first check makes sure that the number of arguments is correct. If not, 
it will print an error. Then, the program checks to make sure the arguments 
actually have characters in them. If not, a different error prints. Now that 
there are 2 valid arguments, the tokenizer struct is created. From this point
on, the function printTokenStream() is called. This is how the output is 
created. The print function loops and repeatedly calls TKGetNextToken()
until all the tokens have been printed. Lastly, all the allocated memory
is free'd, and the program returns. 

While the tokenizer may seem clunky or overwhelming, the majority of the code 
is devoted to dealing with escape characters ie '\n' to result in the desired 
printout described in the assignment.

Also, the tokenizer is very efficient. If the size of the delimiter array is
m, and the size of the token array is n, the runtime of this toknizer is 
O(m*n). This complexity results from the TKGetNextToken function.



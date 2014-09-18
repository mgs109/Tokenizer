/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char* delims;
	char* token;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {

	char* sepcopy;
	char* tokcopy;

	sepcopy = (char*)malloc(1000);
	tokcopy = (char*)malloc(1000);
	
	strcpy(sepcopy, separators);
	strcpy(tokcopy, ts);

	TokenizerT *tk = malloc(sizeof(TokenizerT)); 
	tk->delims = sepcopy;
	tk->token = tokcopy;

	
	if(tk->delims != NULL && tk->token != NULL){	
		return tk;
	}

	else{
		return NULL;
	}
  
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {

	free(tk);


}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
	int delimscount = 0;
	int tokencount = 0;
	int returncount = 0;
	int remaindercount = 0;
	int delimcount2 = 0;
	int delimcount3 = 0;
	int tokenlength = strlen(tk->token);

	while(tk->token[tokencount] != '\0'){

		delimscount = 0;
		
		while(tk->delims[delimscount] != '\0' ){
			if(tk->token[tokencount] == tk->delims[delimscount] || tk->token[tokencount+1] == '\0'){
				char* returnChar;
				returnChar = (char*)malloc(1000);
				delimcount2 = delimscount;
				while(tk->delims[delimcount2] != '\0'){
					if( tk->delims[delimcount2] == '\\' && tk->token[tokencount+1] == tk->delims[delimcount2+1] && tk->token[tokencount+1] != '\0' ){
					
						while(returncount < tokencount){
							returnChar[returncount] = tk->token[returncount];
							returncount++;
						}
						if(tk->token[tokencount+2] == '\0'){
							returnChar[returncount] = tk->token[returncount];
							returnChar[returncount+1] = '\0';

						}
						else{
							returnChar[returncount] = '\0';
						}
						
						returncount++;
						char* nextToken;
						nextToken = (char*) malloc(1000);

						while(returncount <= tokenlength){
							nextToken[remaindercount] = tk->token[returncount+1];
							remaindercount++;
							returncount++;

						}

						nextToken[returncount] = '\0';
						strcpy(tk->token, nextToken);
					
					return returnChar;
					}delimcount2++;
				
				} if( tk->delims[delimscount - 1] != '\\'){
		
				/*Copies the token if it is followed by a delimiter*/
				while(returncount < tokencount){
					returnChar[returncount] = tk->token[returncount];
					returncount++;
	
				}
	
				/*If token is final char sequences of the string, completes the string differently than if token is followed by a delimiter*/
				if(tk->token[tokencount+1] == '\0'){
					while(tk->delims[delimcount3] != '\0'){ 
						if(tk->delims[delimcount3] == tk->token[returncount]){						
						returnChar[returncount+1] = '\0';
						}else if(tk->delims[delimcount3+1] == '\0'){
							returnChar[returncount] = tk->token[returncount];
						}

						delimcount3++;
					}
				}else{
					returnChar[returncount] = '\0';
				}




				/*Updates the next tokens stored in tokenizer struct*/
				returncount++;
				char* nextToken;
				nextToken = (char*)malloc(1000);
				
				while(returncount <= tokenlength){
					nextToken[remaindercount] = tk->token[returncount];
					remaindercount++;
					returncount++;
				}
				nextToken[returncount] = '\0';
				strcpy(tk->token, nextToken);
					
				
				return returnChar;
				
				}		

			}
			delimscount++;
		}
		
		tokencount++;
	}
	
  return 0;
}



/*Prints the token stream for entered phrase*/
void printTokenStream(TokenizerT *tk){



	/*Prints the first token*/
	char* printToken;
	printToken = (char*)malloc(1000);
	printToken = TKGetNextToken(tk);
	


	/*Prints the rest of the tokens*/
	while(printToken != 0){
		if(printToken != 0 && strlen(printToken) > 0){
			printf("%s\n", printToken);
		}	
		
		printToken = TKGetNextToken(tk);
	}




}


/*Fixes escaoe chars in token string when there are no delimters*/
void fixMissingDelims(TokenizerT *tk){
	int tokenindex = 0;
	int tokenlength = -1;
	
	while(tk->token[tokenindex] != '\0'){
		tokenlength = strlen(tk->token);
		if(tk->token[tokenindex] == '\\' || tk->token[tokenindex] == '\"'){
			if(tokenindex != tokenlength){


	
				if(tk->token[tokenindex]== '\"'){
					while(tokenlength > tokenindex ){
						tk->token[tokenlength+5] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = 'a';
					tk->token[tokenindex+5] = ']';
				}

				if(tk->token[tokenindex+1]== 'n'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = 'a';
					tk->token[tokenindex+5] = ']';
				}
	



				if(tk->token[tokenindex+1]== 't'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}
					
					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = '9';
					tk->token[tokenindex+5] = ']';

				}

				if(tk->token[tokenindex+1]== 'v'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}
					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = 'b';
					tk->token[tokenindex+5] = ']';

				}


				if(tk->token[tokenindex+1]== 'b'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = '8';
					tk->token[tokenindex+5] = ']';


				}



				if(tk->token[tokenindex+1]== 'r'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = 'd';
					tk->token[tokenindex+5] = ']';


				}




				if(tk->token[tokenindex+1]== 'f'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = 'c';
					tk->token[tokenindex+5] = ']';


				}


				if(tk->token[tokenindex+1]== 'a'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '0';
					tk->token[tokenindex+4] = '7';
					tk->token[tokenindex+5] = ']';


				}

				if(tk->token[tokenindex+1]== '\\'){
					while(tokenlength > tokenindex + 1){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '5';
					tk->token[tokenindex+4] = 'c';
					tk->token[tokenindex+5] = ']';


				}

				if(tk->token[tokenindex+1]== '\"'){
					while(tokenlength > tokenindex){
						tk->token[tokenlength+4] = tk->token[tokenlength];
						tokenlength--;
					}

					tk->token[tokenindex] = '[';	
					tk->token[tokenindex+1] = '0';
					tk->token[tokenindex+2] = 'x';
					tk->token[tokenindex+3] = '2';
					tk->token[tokenindex+4] = '2';
					tk->token[tokenindex+5] = ']';

				}

			}

		}


		tokenindex++;
	}
	
}


void trimTokens(char* tokens){

int tokenslength = strlen(tokens);


	while(tokens[tokenslength-1] == '\\'){
		tokens[tokenslength-1] = '\0';
		tokenslength--;
		


	}


}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	

	/*Checks if correct number of arguments*/	
	if(argc != 3){
		printf("Incorrect number of arguments, please try again.\nFormat of inputs should be: <delimiters> <stringoftokens>.\n");
		return 0;
	
	}
	/*Saves arguments to memory*/	
	char* delims = argv[1];
	char* tokens = argv[2];

	/*Fixes '\' at the end of the token string*/
	trimTokens(tokens);




	
	
	/*Creates the Tokenizer*/
	TokenizerT *tk = TKCreate(delims, tokens);


	
	
	/*Checks if delims argument is empty. If so, fixes and prints the main string including escape chars*/
	if(strcmp(delims, "") == 0 || strcmp(tokens, "") == 0){
		if(strcmp(tokens, "") == 0){
			printf("Please input a string to be tokenized.\n");
			return 0;
		}
		fixMissingDelims(tk);
		printf("%s\n", tk->token);
		return 0;
	}
	//reduceInputs(tk);	
	printTokenStream(tk);
	TKDestroy(tk);	

  return 0;
}

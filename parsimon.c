//brunet, matt... compiler for cqq...from scratch
//tokens: "WHILE", "INT", "CHAR", "IF", "ELSE", "VAR", "PLUS"
        //"MINUS", "DIV", "MULT", "EQ", "QM","LT", "GT", "LEQ"
        // "GEQ" 
        //NO UNDERSCORES!!!!!!!!!!!!
//parser will parse apart keywords/variable names from symbols


#include<ctype.h>
#include"symbolTable.h"
#define SYNT "syntax error"
#define COND "conditional syntax error"
#define VARI "invalid variable declaration"
#define EXPR "invalid expression"
#define PARN "unbalanced parenthese"
#define UNRE "unrecognized variable"
char varBuffer[65];
int lineNum = 1;
char tokenBuff[65];
char lastToken[65];
char booleanString[100];
char expro[65];
int currReg = 0; 
int final = 0;
int innaParen = 0;
int i; int j; int boolFlag = 0; int parseKeyFlag = 0; int parseSymFlag = 0; int varLen = 0;
char currChar = ' '; 
char ops[4] = {'/','*','+','-'};
char* opStr[4] = {"div", "mul", "add", "sub"};
//thrown when encountering a parse error 
void parseError(char* message){
     printf("%s on line %d\n",message, lineNum);
     exit(1);
}


/*idea: do it recursively... 
take (i + 40)-v 
1. search for first pair of closed parens
add to stack??





*/

int parseExpr(char * boolean, int ball){
	int curr= ball;
	//search for parens 			//how to detect ( l + a ) -> l + a vs. (l + 1) - (a + 1) 
	//printf("%s\n", boolean);
	int r = 0;
	while(boolean[r] != '\0'){
		if(boolean[r] == '('){
			boolean[r++] = '.';
			int open = 1; if(boolean[r] == ')'){parseError(EXPR);}
			int p = 0; char nexp[60];
			//check for outermost parens to ignore
			while(1){
				if(boolean[r] == '('){open++;} 
				if(boolean[r] == ')'){open--;} // can deal with single reg ops here
				if( (boolean[r] == ')') && (open == 0)){boolean[r] = '.'; break;}
				nexp[p++] = boolean[r++];
				boolean[r-1] = (curr + 1) + '0';
			}
			nexp[p] = '\0';
			parseExpr(nexp, (curr + 1));
		curr++;
		}
		else{r++;}
	}
	//printf("ATOMIC EXPR %s...\n", boolean);


	int detect = 0; // this will be used for final step
	for(int opio = 0; opio <= 4; opio++){
	//int m = 0;
	r = 0;

	while(boolean[r] != '\0'){
		if(boolean[r] != ops[opio]){r++;}
		else{ //deal with left side... get lExp... could be .reg., var, num... 
		detect++;int l = r; int ptr = 0;int imm = 0; char regioLeft = ' '; int isVar = 0; char lVar [30]; memset(lVar, '\0', sizeof(lVar));
			if(!l){parseError(EXPR);} char regioRight = ' ';
			 // atomic expr needs two regs (maybe), one for left, one for right
			boolean[l--] = (curr + 1) + '0';
			if(boolean[l] == '.'){     //the case of a reg on left side... grab reg and replace
				if(!l){parseError(EXPR);} if(!isdigit(boolean[l-1])){parseError(EXPR);} 
				  regioLeft = boolean[l - 1]; boolean[l] = (curr+1) + '0';printf("move, $%d, $%c\n", (curr + 1), regioLeft);
				while(boolean[l] != '.'){if(l < 0){break;}boolean[l--] = (curr+1) + '0';} //progress to left until lmost .
				l = r;
			}
			else{ //if isVar/isImm on left, copy it, replace w currReg
		       		while((l >= 0) && isalnum(boolean[l])){ 
					if(isdigit(boolean[l])){imm++;}
					if(isalpha(boolean[l])){isVar++;}
					lVar[ptr++] = boolean[l];
					boolean[l] = (curr + 1) + '0'; //replace w reg
					l--;
				}
				if(boolean[l] == '!'){l--;}
				boolean[l + 1] = '.';
				//printf("BOOL W REG TEST L: %s\n", boolean);
				lVar[ptr] = '\0';

				//reverse dat hoe 
				//printf("got here lol\n");
				int  e = 0; char spare = ' ';
				if( ((ptr) % 2) == 0){ptr--; for(; (ptr) >= e; ){spare = lVar[ptr]; lVar[ptr] = lVar[e]; lVar[e] = spare; e++; ptr--;}}
				else{ ptr--; for(; (ptr) > e;){spare = lVar[ptr]; lVar[ptr] = lVar[e]; lVar[e] = spare; ptr--; e++;}}


				//printf("LVAR: %s \n", lVar);
				/*look up and add to reg*/
				//if(lookup(lVar) == NULL){parseError(UNRE);} SEMANTIC LOOKUP
 				//printf("REG LEFT: %c\n", regioLeft);
				//if(m == 1){printf("move reg %c to reg %d\n", regioLeft, (curr + 1));}
				printf("move, $%d, %s\n", (curr+1), lVar); //temp
			}


				//get right 
				ptr = 0; memset(lVar, '\0', sizeof(lVar));
				l = r + 1;
				if(boolean[l] == '\0'){parseError(EXPR);}
				if(boolean[l] == '.'){if(!isdigit(boolean[l+1])){parseError(EXPR);}regioRight = boolean[l + 1]; printf("move, $%d, $%c\n", (curr+2), regioRight);while(boolean[++l] != '.'){boolean[l] = (curr + 1) + '0';;}}
				else{

				while(isalnum(boolean[l]) && (boolean[l] != '\0')){
                                        if(isdigit(boolean[l])){imm++;}
                                        if(isalpha(boolean[l])){isVar++;}
                                        lVar[ptr++] = boolean[l];
					boolean[l] = (curr + 1) + '0';
					l++;
                                }
				if(boolean[l] == '!'){l++;}
				lVar[ptr] = '\0'; boolean[l- 1] = '.';
				printf("move, $%d, %s\n", (curr+2), lVar); // this will be changed to lw possibly?
				}
				printf("%s, $%d, $%d, $%d\n", opStr[opio], curr + 1, curr + 1,curr + 2);

				//curr++;
				//printf("BOOL W REG TEST : %s\n", boolean);

				r++;


			//printf("BOOL AFTER:%s\n", boolean);
				int bullshit = 0;
				int k = 0; while(boolean[k++] != '\0'){if( (boolean[k] == '+') || (boolean[k] == '-') ||  (boolean[k] == '/') || (boolean[k] == '*')) {bullshit++;}}
				if(bullshit == 0){printf("move, $%d, $%c\n", ball, boolean[1]);}
				//printf("%d BALLS\n", ball);
				final = ball;

		}
		//end of else{parseoperations


		}
	
	}
	
	//if(currReg - curr == 0){printf("BRUH move, $%d, $%d\n", currReg, curr + 1);}
	//printf("move, $%d, $%d\n", currReg - 1, ball);
       	//printf("%d BALLS\n", ball);

	return 0;
}



// parse sumthn like while( (i / 10) <= (v - 1)){...}
// or sumthn like while i / 10 <= v - 1 {...}
void parseBool(char* boolean){
        int p = 0;
	int q = 0;
        int cmp = 0;
	char nextExpr[65];
        //copy left side to send up for parsing
        while(cmp ==  0){
	nextExpr[p] = boolean[p];
	if(p >= j - 1) {parseError(COND);}
	//get comparison type
	if( boolean[p] == '<') cmp = 1;
	if( boolean[p] == '>') cmp = 2;
	if( boolean[p] == '<'  && boolean[p+1] == '=') cmp = 3;
	if( boolean[p] == '>'  && boolean[p+1] == '=') cmp = 4;
        if( boolean[p] == '='  && boolean[p+1] == '=') cmp = 5;
        if( boolean[p] == '!'  && boolean[p+1] == '=') cmp = 6;
	p++;
 	}
	nextExpr[p - 1] = '\0'; if(cmp>2){nextExpr[p++] = '\0';}  
	int pOpen = 0; int closed;
for(q = 0; nextExpr[q] != '\0'; q++){
		if(nextExpr[q] == '(' ){pOpen++;} if(nextExpr[q] == ')'){pOpen--;}
	}
	closed = pOpen;
	for(q = 0; pOpen > 0;q++){if(nextExpr[q] == '('){nextExpr[q] = '!'; pOpen--;}} 
	parseExpr(nextExpr, currReg++);


	memset(nextExpr, '\0', sizeof(nextExpr));
	for(q = 0; boolean[p] != '\0'; p++){
		nextExpr[q++] = boolean[p];
	}
	nextExpr[q] = '\0';
	for(; closed > 0;){/*printf("bruh\n");*/ nextExpr[q - closed] = '!';closed--;} 
	//printf("hellaaaaa bruh\n");
	parseExpr(nextExpr, currReg++);
}


void clearWhite(){
char newChar;
    while((isspace(newChar = getchar()))){
                if(newChar == '\n'){lineNum++;}
        }
        ungetc(newChar, stdin);
}


void tokenize(){
	j = 0;
        boolFlag = 0;
	//reset booleanString 
        memset(booleanString, '\0', sizeof(booleanString));
	if(!strcmp(tokenBuff, "while")){ //upon encountering a while
        	strcpy(lastToken, tokenBuff);
                clearWhite();
                //begin conditional parse // copy cond to booleanString
                	while( (currChar = getchar()) != '{'){
                                clearWhite();
				if(currChar == '('){boolFlag++;}if(currChar==')'){boolFlag--;} if(boolFlag < 0){parseError(PARN);}
                                if(j + 1 >= 100){parseError(COND);}
                        	booleanString[j++] = currChar;	
			}
                if(boolFlag != 0){parseError(PARN);}
                parseBool(booleanString);


	/*put label junk here*/   
	}

	if(!strcmp(tokenBuff, "int")){
		varLen = 0;
		int valid = 0;
		memset(varBuffer, '\0', sizeof(varBuffer));
		strcpy(lastToken,tokenBuff);
		clearWhite();
		while(((currChar = getchar()) != '?') && (currChar != '=')){
			if(!isalnum(currChar)){parseError(VARI);}
			if(isalpha(currChar)){valid = 1;}
			varBuffer[varLen++] = currChar;
			clearWhite();
		}
		if(!valid){parseError(VARI);}  // if at least one of the chars is alphabetic then its valid
		if(currChar == '?'){install(varBuffer,"int"); printf("declaration of %s valid\n", varBuffer);}
		
		if(currChar == '='){clearWhite(); memset(expro, '\0', sizeof(expro));
		int l = 0; int div = 0; while((currChar = getchar()) != '?'){clearWhite();if (l > 60){parseError(VARI);} expro[l++] = currChar; clearWhite();}
		expro[l] = '\0'; 
		parseExpr(expro, currReg++);
		if(final != currReg - 1){ printf("move, $%d, $%d\n", (currReg-1), (final));}

		}
	


	}



} 



void parseio(){
        i = 0;
        memset(tokenBuff, '\0', sizeof(tokenBuff));
	parseKeyFlag = 0;
        parseSymFlag = 0;

        //ignore any whitespace 
        clearWhite();

        //capture any keywords or variables
        while(isalnum(currChar = getchar())){
	 tokenBuff[i++] = currChar;
         parseKeyFlag++;
	}
        ungetc(currChar, stdin);

        //capture any operational symbols
        if(!parseKeyFlag){
        tokenBuff[i++] = (currChar = getchar());
        parseSymFlag = 1;
        }
        
        printf("%s\n", tokenBuff);
//      printf("%zu \n", strlen(tokenBuff));
        tokenize();
}

int main(){


	while(currChar != EOF){
        	parseio();
        }



    return 0;
}

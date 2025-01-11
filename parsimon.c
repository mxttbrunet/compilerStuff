//brunet, matt... parser for cqq...from scratch
//tokens: "WHILE", "INT", "CHAR", "IF", "ELSE", "VAR", "PLUS"
        //"MINUS", "DIV", "MULT", "EQ", "QM","LT", "GT", "LEQ"
        // "GEQ" 
        //NO UNDERSCORES!!!!!!!!!!!!
//parser will parse apart keywords/variable names from symbols


#include<ctype.h>
#include"symbolTable.h"
#define SYN "syntax error"
#define COND "conditional syntax error"
#define VARI "invalid variable declaration"
#define EXPR "invalid expression"
char varBuffer[65];
int lineNum = 1;
char tokenBuff[65];
char lastToken[65];
char booleanString[100];
char expro[65];
int currReg = 0;
int innaParen = 0;
int i; int j; int boolFlag = 0; int parseKeyFlag = 0; int parseSymFlag = 0; int varLen = 0;
char currChar = ' '; 

//thrown when encountering a parse error 
void parseError(char* message){
     printf("%s on line %d\n",message, lineNum);
     exit(1);
}


/*idea: do it recursively... 
take (i + 40)-v 
1. search for first pair of closed parens;
add to stack??





*/

void parseExpr(char * boolean, int ball){
	int curr = ball;
	//search for parens 
	printf("%s\n", boolean);
	int r = 0;
	innaParen = 0;
	while(boolean[r] != '\0'){
		if(boolean[r] == '('){
			curr++;
			boolean[r++] = '.';
			int open = 1; if(boolean[r] == ')'){parseError(EXPR);}
			int p = 0; char nexp[35];
			while(1){
				if(boolean[r] == '('){open++;} if(boolean[r] == ')'){open--;} // can deal with single reg ops here
				if( (boolean[r] == ')') && (open == 0)){boolean[r] = '.'; break;}
				nexp[p++] = boolean[r++];
				boolean[r-1] = curr + '0';
			}
			nexp[p] = '\0';
			parseExpr(nexp, curr);
		}
		else{r++;}
	}
	printf("DONE w %s... in reg: %d\n", boolean, ball);






	
	
}



// parse sum like while( (i / 10) <= (v - 1)){...}
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
	nextExpr[p - 1] = '\0'; if(cmp>2){nextExpr[p] = '\0';}  
	int pOpen = 0;
for(q = 0; nextExpr[q] != '\0'; q++){
		if(nextExpr[q] == '(' ){pOpen++;} if(nextExpr[q] == ')'){pOpen--;}
	}
	for(q = 0; pOpen > 0;q++){if(nextExpr[q] == '('){nextExpr[q] = '!';  pOpen--;}} 
	parseExpr(nextExpr, currReg++);
	memset(nextExpr, '\0', sizeof(nextExpr));
	for(q = 0, p++; boolean[p] != '\0'; p++){
		nextExpr[q] = boolean[p];
	}
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
				if(currChar == '('){boolFlag++;}if(currChar==')'){boolFlag--;}
                                if(j + 1 >= 100){parseError(COND);}
                        	booleanString[j++] = currChar;	
			}
                if(boolFlag != 0){parseError("unbalanced parentheses");}
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
		if(currChar == '?'){install(varBuffer,"int"); printf("declaration of %s valid", varBuffer);}
		
		if(currChar == '='){clearWhite(); memset(expro, '\0', sizeof(expro));
		int l = 0; while((currChar = getchar()) != '?'){clearWhite();if (l > 60){parseError(VARI);} expro[l++] = currChar; clearWhite();}
		expro[l] = '\0'; parseExpr(expro, currReg++);
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

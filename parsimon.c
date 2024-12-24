//brunet, matt... parser for cqq...from scratch
//tokens: "WHILE", "INT", "CHAR", "IF", "ELSE", "VAR", "PLUS"
        //"MINUS", "DIV", "MULT", "EQ", "QM","LT", "GT", "LEQ"
        // "GEQ" 
        //NO UNDERSCORES!!!!!!!!!!!!
//parser will parse apart keywords/variable names from symbols


#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define SYN "syntax error" 
#define COND "conditional syntax error"
#define VARI "invalid variable declaration"
char varBuffer[65];
int lineNum = 1;
char tokenBuff[65];
char lastToken[65];
char booleanString[100];
char expro[65];
int i; int j; int boolFlag = 0; int parseKeyFlag = 0; int parseSymFlag = 0; int varLen = 0;
char currChar = ' '; char newchar;

//thrown when encountering a parse error 
void parseError(char* message){
     printf("%s on line %d\n",message, lineNum);
     exit(1);
}



void parseExpr(char * boolean){
        char current;
	//search for parens 
	printf("%s\n", boolean);

}



// parse sum like while( (i / 10) <= (v - 1)){...}
void parseBool(char* boolean){
        int p = 0;
        int cmp = 0;
	int dummy = 0;
	char nextExpr[50];
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
        if(cmp > 0){nextExpr[p++] = '\0'; if(cmp >= 3){p++;} break;} 
        p++;
 	}
	int pOpen = 0;
	for(int q = 0; q < (p-1); q++){
		if(nextExpr[q] == '(' ){pOpen++;} if(nextExpr[q] == ')'){pOpen--;}
	}
	for(int q = 0; pOpen > 0;q++){if(nextExpr[q] == '('){nextExpr[q] = '!';  pOpen--;}} 
	parseExpr(nextExpr);

	
}


void clearWhite(){
char newChar;
    while((isspace(newchar = getchar()))){
                if(newchar == '\n'){lineNum++;}
        }
        ungetc(newchar, stdin);
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
		memset(varBuffer, '\0', sizeof(varBuffer));
		strcpy(lastToken,tokenBuff);
		clearWhite();
		while(((currChar = getchar()) != '?') && (currChar != '=')){
			if(!isalnum(currChar)){parseError(VARI);}
			varBuffer[varLen++] = currChar;
			clearWhite();
		}
		if(currChar == '?'){/**ENTER ROOM FOR IT ON SYMBOL TABLE */ printf("declaration of %s valid", varBuffer);}
		
		if(currChar == '='){clearWhite(); memset(expro, '\0', sizeof(expro));
		int l = 0; while((currChar = getchar()) != '?'){if (l > 60){parseError(VARI);} expro[l++] = currChar; clearWhite();}
		parseExpr(expro);
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

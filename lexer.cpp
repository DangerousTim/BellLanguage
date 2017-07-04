/* Kicks ass */

#include "lexer.h"

using std::cout;

//Lexeme lexlist[1024]; //After lex_init is called, this array is filled with Lexemes. Parser will use this array.
char * text;

/*lexeme list related functions*/

Lexeme* createLexemeList(char buffer[]) {
    Lexeme *lexlist = new Lexeme [256];
    text = buffer;
    int i = -1;
    do {
        i++;
        if (lex_makelexeme(lexlist[i]) < 0) { //making Lexemes out of the string. If <0, then it is an error, -1 is error code
            return 0;
        }
    } while (i < 256 && lexlist[i].length != 0); //while (lexlist[i].length!=0), as 0 is assigned as lex.length of '\0' only
	return lexlist;
}

void destroyLexemeList(Lexeme *lexlist){
    delete[] lexlist;
}

void printLexemeList(Lexeme* lexlist){
	if (lexlist == NULL) return;

    for (int i = 0; lexlist[i].length != 0; i++)
        cout<<'\''<<lexlist[i].text<<'\''<<' ';
}

/*Lexeme class*/

int Lexeme::isValidInt(){
	if (!isdigit(text[0]))
		return 0;
	//checks if lexeme.text is purely an integer values
	char *endptr;
	strtol(text, &endptr, 10);

	//if not entirely a number, endptr will contain a string
	if (*endptr != '\0')
		cout<<"error: token cannot start with a digit!\n";
	//number cannot be bigger than int limit
	else if (strlen(text) > 5)
		cout<<"error: too large a number!\n";
	//if text is purely integer and within limits, return true
	else
		return 1;	//is a valid integer

	return 0;	//invalid integer
}

/*Magic*/

int lex_makelexeme(Lexeme & lex) {
    if (!text) {
        return -1;
    }
    while ( * text == ' ') { //ignores white spaces
        text++;
    }
    if ( * text == '\0') { //String terminator wala
        lex.length = 0;
        return 0;
    }
    check(lex);
    return 0;
}

int check(Lexeme & lex) { //checks type of Lexeme
    switch ( * text) { //cases dekhle bey, pretty much self explanatory
    case '+':
        lex.length = 1;
        strcpy(lex.text, "+");
        text++;
        break;

    case '-':
        lex.length = 1;
        strcpy(lex.text, "-");
        text++;
        break;

    case '*':
        lex.length = 1;
        strcpy(lex.text, "*");
        text++;
        break;

    case '/':
        lex.length = 1;
        strcpy(lex.text, "/");
        text++;
        break;

    case '%':
        lex.length = 1;
        strcpy(lex.text, "%");
        text++;
        break;
        
    case '>':
        lex.length = 1;
        if(text[1] == '>'){
            lex.length = 2;
        }
        strncpy(lex.text, text, lex.length);
        lex.text[lex.length] = '\0';
        text += lex.length;
        break;

    case '<':
        lex.length = 1;
        if(text[1] == '<'){
            lex.length = 2;
        }
        strncpy(lex.text, text, lex.length);
        lex.text[lex.length] = '\0';
        text += lex.length;
        break;

    case ':':
        lex.length = 1;
        strcpy(lex.text, ":");
        text++;
        break;

    case '[':
        lex.length = 1;
        strcpy(lex.text, "[");
        text++;
        break;

    case ']':
        lex.length = 1;
        strcpy(lex.text, "]");
        text++;
        break;

    case '{':
        lex.length = 1;
        strcpy(lex.text, "{");
        text++;
        break;

    case '}':
        lex.length = 1;
        strcpy(lex.text, "}");
        text++;
        break;

    case '(':
        lex.length = 1;
        strcpy(lex.text, "(");
        text++;
        break;

    case ')':
        lex.length = 1;
        strcpy(lex.text, ")");
        text++;
        break;

    case '?':
        lex.length = 1;
        strcpy(lex.text, "?");
        text++;
        break;

    case '=':
        lex.length = 1;
        strcpy(lex.text, "=");
        text++;
        break;

    default:
        if (isdigit( * text)) { //for integers
            lex.length = 1;
            while (isdigit(text[lex.length])) {
                lex.length++;
            }
            strncpy(lex.text, text, lex.length);
            lex.text[lex.length] = '\0';
            text += lex.length;
        } else if ( * text == 'L' && text[1] == 'T') { //for LT
            lex.length = 2;
            strncpy(lex.text, text, lex.length);
            lex.text[lex.length] = '\0';
            text += lex.length;
        } else if ( * text == 'G' && text[1] == 'T') { //for GT
            lex.length = 2;
            strncpy(lex.text, text, lex.length);
            lex.text[lex.length] = '\0';
            text += lex.length;
        } else if ( * text == 'E' && text[1] == 'Q') { //for EQ
            lex.length = 2;
            strncpy(lex.text, text, lex.length);
            lex.text[lex.length] = '\0';
            text += lex.length;
        }  else if (isalpha( * text) || * text == '_') { //for function names, keywords etc
            lex.length = 1;
            while (isalnum(text[lex.length]) || text[lex.length] == '_') {
                lex.length++;
            }
            strncpy(lex.text, text, lex.length);
            lex.text[lex.length] = '\0';
            text += lex.length;
        }
	else {
            return -1;
        }
    }
    return 0;
}


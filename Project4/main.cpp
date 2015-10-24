/* Derek Baker
	011176059
	CECS 444
	Dr. Wang
*/

#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <cmath>

char token; //global token variable

//function prototypes for recursive calls
int exp( void );
int term( void );
int factor( void );

void error( void ) {
	fprintf(stderr, "Error\n");
}

void match( char expectedToken ) {
	if( token == expectedToken ) 
		token = getchar();
	else 
		error();
}

int main() {
	printf( "x to quit\n" );
	while( 1 ) {
		int result;		
		token = getchar(); //load token with first character for lookahead				
		if( token =='x' )
			break;
		result = exp();
		if( token == '\n' ) //check for end of line
			printf( "Result = %d\n", result );
		else error(); //extraneous chars on line
	}
	return 0;
}

int exp( void ) {
	int temp = term();
	while(( token == '+' || token == '-')) {
		switch( token ) {
		case '+':
			match( '+' );
			temp += term();
			break;
		case '-':
			match( '-' );
			temp -= term();
			break;
		}
	}
	return temp;
}

int term( void ) {
	int temp = factor();
	while( token == '^' ) {
		token = getchar();
		temp = pow( temp, term() );
	}
	while( token == '*' || token == '/' || token == '%' ) {
		if( token == '*' ) {
			match( '*' );
			temp *= factor();
		} else if( token == '/' ) {
			match( '/' );
			temp /= factor();
		} else if( token == '%' ) {
			match( '%' );
			temp %= factor();
		}
	}
	return temp;
}

int factor( void ) {
	int temp;
	if( token == '(' ) {
		match( '(' );
		temp = exp();
		match( ')' );
	} else if( isdigit( token ) ) {
		ungetc( token, stdin );
		scanf( "%d", &temp );
		token = getchar();
	} else if( token == '-' ) {
		ungetc( token, stdin );
		scanf( "%d", &temp );
		token = getchar();
	} else {
		error();
	}
	return temp;
}
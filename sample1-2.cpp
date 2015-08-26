
// tiny-peg ver1.0


#include <stdio.h>

// Definition of tiny-peg ver1.0 (only 7 lines)
// I used "comma operator" in C Language. 
typedef char const *_iterator; 
#define _is(c) c == *it && (++it, true)
#define _L(n) (it_old[n] = it, true) && ( true
#define _C(n) true || (it = it_old[n], true)
#define _R true )
#define _head(n) _iterator it_old[n]; it_old[0] = it
#define _false (it = it_old[0], false)



/*
 In this sample, I construct a parser for arithmetic expressions. 
 As is usual, the PEG expressions for arithmetic expressions are as follows: 

 expr <- term ( ('+' | '-') term)*
 term <- factor ( ('*' | '/') factor)*
 factor <- ('+' | '-' | '') ( '(' expr ')' | number )
 number <- ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+

 However, I did not implement "*" (zero-or-more) in tiny-peg ver1.0. 
 Hence, I use the following expressions: 

 expr <- term term__
 term <- factor factor__
 factor <- ('+' | '-' | '') ( '(' expr ')' | number__ )

 term__ <- ('+' | '-') term term__ | ''
 factor__ <- ('*' | '/') factor factor__ | ''

 digit <- '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
 number__ <- digit (number__ | '')


 Note: 
 We can use "*" and "+" in tiny-peg ver2.0. 

*/

bool is_expr(_iterator &it); 
bool is_term(_iterator &it); 
bool is_factor(_iterator &it); 

bool is_term__(_iterator &it); 
bool is_factor__(_iterator &it); 

bool is_digit(_iterator &it); 
bool is_number__(_iterator &it); 


bool is_expr(_iterator &it){ 
	_head(1); 
	if(is_term(it) && is_term__(it)){ return true; }
	return _false; 
}

bool is_term(_iterator &it){ 
	_head(1); 
	if(is_factor(it) && is_factor__(it)){ return true; }
	return _false; 
}

bool is_factor(_iterator &it){ 
	_head(2); 
	if(_L(1) && _is('+') && _C(1) && _is('-') && _C(1) && true && _R && _L(1) && _is('(') && is_expr(it) && _is(')') && _C(1) && is_number__(it) && _R){ return true; }
	return _false; 
}

bool is_term__(_iterator &it){ 
	_head(2); 
	if(_L(1) && _is('+') && _C(1) && _is('-') && _R && is_term(it) && is_term__(it) && _C(0) && true){ return true; }
	return _false; 
}

bool is_factor__(_iterator &it){ 
	_head(2); 
	if(_L(1) && _is('*') && _C(1) && _is('/') && _R && is_factor(it) && is_factor__(it) && _C(0) && true){ return true; }
	return _false; 
}

bool is_digit(_iterator &it){ 
	_head(1); 
	if(_is('0') && _C(0) && _is('1') && _C(0) && _is('2') && _C(0) && _is('3') && _C(0) && _is('4') && _C(0) && _is('5') && _C(0) && _is('6') && _C(0) && _is('7') && _C(0) && _is('8') && _C(0) && _is('9')){ return true; }
	return _false; 
}

bool is_number__(_iterator &it){ 
	_head(2); 
	if(is_digit(it) && _L(1) && is_number__(it) && _C(1) && true && _R){ return true; }
	return _false; 
}

void test(char const *str){
	_iterator it = str; 
	printf("[%s] ", it);printf("%d\n", is_expr(it)); 
	printf("[%s] ", it);printf("%d\n", is_expr(it)); 
	if(0 != *it){ printf("--invalid expression--\n"); }
	printf("\n");
}

int main(int argc, char *argv[]){
	test("1+1*(2-3*4)*(5-6*(7/8+9))"); 
	test("-(1+2)*(-3)-(-4)/(+5)"); 
	test("1/*2"); // invalid expression
	test("38*46*(4)-((79)*75/16-(66-78))/54+((92/(67))/84-(10*9/88/70-(28)/(30)*(77+94))+88-48*(47)+(43))*(87)/(90)/(23)-(76)/(59+50*(19))*84+(49*(3)*50/(81+(52/25)+(58*(16)-72)*(14/89)-(7+14-54-39))/(66)-(83+(98))-(36)/40+6)+(22)/29*(8+95)*(18)-100/(93)+81-(7/29+30)-(71)-((38)/86/88*(23)*9*63-81/(8)+80*86+(56)*(32/63)*2-(75)*(43)*100-89+61-(57)*(79+(47))/(75)*(7)*(19-49-(46)/29-(91-8)/81)+(72-15)-(48)-77)"); 

	return 0; 
}

/*
result: 

[1+1*(2-3*4)*(5-6*(7/8+9))] 1
[] 0

[-(1+2)*(-3)-(-4)/(+5)] 1
[] 0

[1/*2] 1
[/*2] 0
--invalid expression--

[38*46*(4)-((79)*75/16-(66-78))/54+((92/(67))/84-(10*9/88/70-(28)/(30)*(77+94))+88-48*(47)+(43))*(87)/(90)/(23)-(76)/(59+50*(19))*84+(49*(3)*50/(81+(52/25)+(58*(16)-72)*(14/89)-(7+14-54-39))/(66)-(83+(98))-(36)/40+6)+(22)/29*(8+95)*(18)-100/(93)+81-(7/29+30)-(71)-((38)/86/88*(23)*9*63-81/(8)+80*86+(56)*(32/63)*2-(75)*(43)*100-89+61-(57)*(79+(47))/(75)*(7)*(19-49-(46)/29-(91-8)/81)+(72-15)-(48)-77)] 1
[] 0

*/

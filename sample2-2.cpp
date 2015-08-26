
// tiny-peg ver2.0


#include <stdio.h>

// Definition of tiny-peg ver2.0 (only 20 lines) 
// This version meets the requirements of PEG. 
typedef char const *_iterator; 
static bool is_err = false, not_predicate_flag = false; 
static _iterator it_old[1 << 20]; 
static int const it_old_end = sizeof(it_old) / sizeof(_iterator); 
static int __n = -1; 
#define _is(c) c == *it && (++it, true)
#define _L !is_err && (((++__n, true) && it_old_end > __n && (it_old[__n] = it, true) || (is_err = true, false)) && (true
#define _C !is_err || !is_err && (it = it_old[__n], true)
#define _R !is_err) && (--__n, true) || (--__n, false))
#define _head _iterator it_origin = it; int __n_old = __n; ++__n; if(is_err || it_old_end <= __n){ is_err = true; return _false; } it_old[__n] = it
#define _true (__n = __n_old, true)
#define _false (__n = __n_old, !is_err && (it = it_origin, false))
#define LOOP(n) [&]()->bool{ _head; for(int ______cnt = 0, ______n = n; ; ++______cnt){ if(______n < ______cnt){ ______cnt = ______n; } it_old[__n] = it; bool result = true
#define END_LOOP true; if(is_err){ return _false; } if(!result){ it = it_old[__n]; if(______n > ______cnt){ return _false; } break; } if(it == it_old[__n]){ break; } } return _true; }() 
#define H _L
#define END_H _C && true && _R
#define AND _L
#define END_AND !is_err) && (!is_err && (it = it_old[__n], true), --__n, true) || (!is_err && (it = it_old[__n], true), --__n, false))
#define NOT ((AND
#define END_NOT END_AND && (not_predicate_flag = true) || !(not_predicate_flag = false) ) && !is_err && !not_predicate_flag)



/*
 In this sample, I construct a parser for arithmetic expressions. 
 As is usual, the PEG expressions for arithmetic expressions are as follows: 

 expr <- term ( ('+' | '-') term)*
 term <- factor ( ('*' | '/') factor)*
 factor <- ?('+' | '-') ( '(' expr ')' | number )
 number <- ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+

*/

bool is_expr(_iterator &it); 
bool is_term(_iterator &it); 
bool is_factor(_iterator &it); 
bool is_number(_iterator &it); 


bool is_expr(_iterator &it){ 
	_head; 
	if(is_term(it) && LOOP(0) && _L && _is('+') && _C && _is('-') && _R && is_term(it) && END_LOOP){ return _true; }
	return _false; 
}

bool is_term(_iterator &it){ 
	_head; 
	if(is_factor(it) && LOOP(0) && _L && _is('*') && _C && _is('/') && _R && is_factor(it) && END_LOOP){ return _true; }
	return _false; 
}

bool is_factor(_iterator &it){ 
	_head; 
	if(H && _is('+') && _C && _is('-') && END_H && _L && _is('(') && is_expr(it) && _is(')') && _C && is_number(it) && _R){ return _true; }
	return _false; 
}

bool is_number(_iterator &it){ 
	_head; 
	if(LOOP(1) && _is('0') && _C && _is('1') && _C && _is('2') && _C && _is('3') && _C && _is('4') && _C && _is('5') && _C && _is('6') && _C && _is('7') && _C && _is('8') && _C && _is('9') && END_LOOP){ return _true; }
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


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
 In this sample, I improve sample2-2.cpp so that "is_expr" can calculate arithmetic expressions. 

*/

#define _set(a, b) (a = (b), true)

bool is_expr(_iterator &it, int &x); 
bool is_term(_iterator &it, int &x); 
bool is_factor(_iterator &it, int &x); 
bool is_number(_iterator &it, int &x); 


bool is_expr(_iterator &it, int &x){ 
	int y = 0, z = 0; bool isMinus = false; 
	_head; 
	if(is_term(it, z) && LOOP(0) && _L && _is('+') && _C && _is('-') && _set(isMinus, true) && _R && is_term(it, y) && (isMinus && _set(z, z - y) && _set(isMinus, false) || _set(z, z + y)) && END_LOOP && _set(x, z)){ return _true; }
	return _false; 
}

bool is_term(_iterator &it, int &x){ 
	int y = 0, z = 0; bool isDiv = false; 
	_head; 
	if(is_factor(it, z) && LOOP(0) && _L && _is('*') && _C && _is('/') && _set(isDiv, true) && _R && is_factor(it, y) && (isDiv && _set(z, z / y) && _set(isDiv, false) || _set(z, z * y)) && END_LOOP && _set(x, z)){ return _true; }
	return _false; 
}

bool is_factor(_iterator &it, int &x){ 
	int y = 0; bool isMinus = false; 
	_head; 
	if(H && _is('+') && _C && _is('-') && _set(isMinus, true) && END_H && _L && _is('(') && is_expr(it, y) && _is(')') && _C && is_number(it, y) && _R && _set(x, y) && (!isMinus || _set(x, -x))){ return _true; }
	return _false; 
}

#define _is_(c) _is(c) && _set(y, 10 * y + ((c) - '0'))

bool is_number(_iterator &it, int &x){ 
	int y = 0; 
	_head; 
	if(LOOP(1) && _is_('0') && _C && _is_('1') && _C && _is_('2') && _C && _is_('3') && _C && _is_('4') && _C && _is_('5') && _C && _is_('6') && _C && _is_('7') && _C && _is_('8') && _C && _is_('9') && END_LOOP && _set(x, y)){ return _true; }
	return _false; 
}

int main(int argc, char *argv[]){
	
	{
		_iterator it	= "-(87651+3580431)"; 
		int ans		=  -(87651+3580431); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it	= "1+1*(2-3*4)*(5-6*(7/8+9))"; 
		int ans		=  1+1*(2-3*4)*(5-6*(7/8+9)); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it	= "-(1+2)*(-3)-(-4)/(+5)"; 
		int ans		=  -(1+2)*(-3)-(-4)/(+5); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it	= "38*46*(4)-((79)*75/16-(66-78))/54+((92/(67))/84-(10*9/88/70-(28)/(30)*(77+94))+88-48*(47)+(43))*(87)/(90)/(23)-(76)/(59+50*(19))*84+(49*(3)*50/(81+(52/25)+(58*(16)-72)*(14/89)-(7+14-54-39))/(66)-(83+(98))-(36)/40+6)+(22)/29*(8+95)*(18)-100/(93)+81-(7/29+30)-(71)-((38)/86/88*(23)*9*63-81/(8)+80*86+(56)*(32/63)*2-(75)*(43)*100-89+61-(57)*(79+(47))/(75)*(7)*(19-49-(46)/29-(91-8)/81)+(72-15)-(48)-77)"; 
		int ans		=  38*46*(4)-((79)*75/16-(66-78))/54+((92/(67))/84-(10*9/88/70-(28)/(30)*(77+94))+88-48*(47)+(43))*(87)/(90)/(23)-(76)/(59+50*(19))*84+(49*(3)*50/(81+(52/25)+(58*(16)-72)*(14/89)-(7+14-54-39))/(66)-(83+(98))-(36)/40+6)+(22)/29*(8+95)*(18)-100/(93)+81-(7/29+30)-(71)-((38)/86/88*(23)*9*63-81/(8)+80*86+(56)*(32/63)*2-(75)*(43)*100-89+61-(57)*(79+(47))/(75)*(7)*(19-49-(46)/29-(91-8)/81)+(72-15)-(48)-77); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it	= "95*(18/13/(43)*71)-94+31+(15)-92-4+17*(38*(41))+(89)-53*54/(19)/29+95*20*(82)/79+(15)/(33)+32*17-94/38+(53)-(45)*(70)-33+(38)+80-37/31-(48)+50/85*(33)/80-(59/((48)+81-21)*(91)-(43)*37)/(42+24-(62)/53/(17)+(7)-(51)*(28-(44)/74)+(((31)*52)+44+75+(89))/(70)/(100)-(50)*35+(69*(36-(57)-((24)+(85)-78)*56)-51)/(32+80))-((69)*(49*73)-(76*(55))/45-71)+14+(87)/27-61/((97)+(89)/88)*51+(24)+13/63-88*2*(27)*(15)+(42)"; 
		int ans		=  95*(18/13/(43)*71)-94+31+(15)-92-4+17*(38*(41))+(89)-53*54/(19)/29+95*20*(82)/79+(15)/(33)+32*17-94/38+(53)-(45)*(70)-33+(38)+80-37/31-(48)+50/85*(33)/80-(59/((48)+81-21)*(91)-(43)*37)/(42+24-(62)/53/(17)+(7)-(51)*(28-(44)/74)+(((31)*52)+44+75+(89))/(70)/(100)-(50)*35+(69*(36-(57)-((24)+(85)-78)*56)-51)/(32+80))-((69)*(49*73)-(76*(55))/45-71)+14+(87)/27-61/((97)+(89)/88)*51+(24)+13/63-88*2*(27)*(15)+(42); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}
	

	return 0; 
}

/*
result: 

1 []
ans = -3668082
x   = -3668082

1 []
ans = 491
x   = 491

1 []
ans = 9
x   = 9

1 []
ans = 301146
x   = 301146

1 []
ans = -291968
x   = -291968

*/

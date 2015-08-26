
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
 In this sample, I improve sample1-2.cpp so that "is_expr" can calculate arithmetic expressions. 

*/

#define _set(a, b) (a = (b), true)

bool is_expr(_iterator &it, int &x); 
bool is_term(_iterator &it, int &x); 
bool is_factor(_iterator &it, int &x); 

bool is_term__(_iterator &it, int &x); 
bool is_factor__(_iterator &it, int &x); 

bool is_digit(_iterator &it, char &c); 
bool is_number__(_iterator &it, int &x); 


bool is_expr(_iterator &it, int &x){ 
	int y = 0; 
	_head(1); 
	if(is_term(it, y) && is_term__(it, y) && _set(x, y)){ return true; }
	return _false; 
}

bool is_term(_iterator &it, int &x){ 
	int y = 0; 
	_head(1); 
	if(is_factor(it, y) && is_factor__(it, y) && _set(x, y)){ return true; }
	return _false; 
}

bool is_factor(_iterator &it, int &x){ 
	int y = 0; bool isMinus = false; 
	_head(2); 
	if(_L(1) && _is('+') && _C(1) && _is('-') && _set(isMinus, true) && _C(1) && true && _R && _L(1) && _is('(') && is_expr(it, y) && _is(')') && _C(1) && _set(y, 0) && is_number__(it, y) && _R && _set(x, y) && (!isMinus || _set(x, -x))){ return true; }
	return _false; 
}

bool is_term__(_iterator &it, int &x){ 
	int y = 0; bool isMinus = false; 
	_head(2); 
	if(_L(1) && _is('+') && _C(1) && _is('-') && _set(isMinus, true) && _R && is_term(it, y) && (isMinus && _set(x, x - y) || _set(x, x + y)) && is_term__(it, x) && _C(0) && true){ return true; }
	return _false; 
}

bool is_factor__(_iterator &it, int &x){ 
	int y = 0; bool isDiv = false; 
	_head(2); 
	if(_L(1) && _is('*') && _C(1) && _is('/') && _set(isDiv, true) && _R && is_factor(it, y) && (isDiv && _set(x, x / y) || _set(x, x * y)) && is_factor__(it, x) && _C(0) && true){ return true; }
	return _false; 
}

bool is_digit(_iterator &it, char &c){ 
	_head(1); 
	if(_is('0') && _set(c, 0) && _C(0) && _is('1') && _set(c, 1) && _C(0) && _is('2') && _set(c, 2) && _C(0) && _is('3') && _set(c, 3) && _C(0) && _is('4') && _set(c, 4) && _C(0) && _is('5') && _set(c, 5) && _C(0) && _is('6') && _set(c, 6) && _C(0) && _is('7') && _set(c, 7) && _C(0) && _is('8') && _set(c, 8) && _C(0) && _is('9') && _set(c, 9)){ return true; }
	return _false; 
}

bool is_number__(_iterator &it, int &x){ 
	char c = 0; 
	_head(2); 
	if(is_digit(it, c) && _set(x, x * 10 + c) && _L(1) && is_number__(it, x) && _C(1) && true && _R){ return true; }
	return _false; 
}



int main(int argc, char *argv[]){
	
	{
		_iterator it = "-(87651+3580431)"; 
		int ans      =  -(87651+3580431); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it = "1+1*(2-3*4)*(5-6*(7/8+9))"; 
		int ans      =  1+1*(2-3*4)*(5-6*(7/8+9)); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it = "-(1+2)*(-3)-(-4)/(+5)"; 
		int ans      =  -(1+2)*(-3)-(-4)/(+5); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it = "38*46*(4)-((79)*75/16-(66-78))/54+((92/(67))/84-(10*9/88/70-(28)/(30)*(77+94))+88-48*(47)+(43))*(87)/(90)/(23)-(76)/(59+50*(19))*84+(49*(3)*50/(81+(52/25)+(58*(16)-72)*(14/89)-(7+14-54-39))/(66)-(83+(98))-(36)/40+6)+(22)/29*(8+95)*(18)-100/(93)+81-(7/29+30)-(71)-((38)/86/88*(23)*9*63-81/(8)+80*86+(56)*(32/63)*2-(75)*(43)*100-89+61-(57)*(79+(47))/(75)*(7)*(19-49-(46)/29-(91-8)/81)+(72-15)-(48)-77)"; 
		int ans      =  38*46*(4)-((79)*75/16-(66-78))/54+((92/(67))/84-(10*9/88/70-(28)/(30)*(77+94))+88-48*(47)+(43))*(87)/(90)/(23)-(76)/(59+50*(19))*84+(49*(3)*50/(81+(52/25)+(58*(16)-72)*(14/89)-(7+14-54-39))/(66)-(83+(98))-(36)/40+6)+(22)/29*(8+95)*(18)-100/(93)+81-(7/29+30)-(71)-((38)/86/88*(23)*9*63-81/(8)+80*86+(56)*(32/63)*2-(75)*(43)*100-89+61-(57)*(79+(47))/(75)*(7)*(19-49-(46)/29-(91-8)/81)+(72-15)-(48)-77); 
		int x = 0; 
		printf("%d ", is_expr(it, x)); printf("[%s]\n", it);
		printf("ans = %d\nx   = %d\n\n", ans, x);
	}

	{
		_iterator it = "95*(18/13/(43)*71)-94+31+(15)-92-4+17*(38*(41))+(89)-53*54/(19)/29+95*20*(82)/79+(15)/(33)+32*17-94/38+(53)-(45)*(70)-33+(38)+80-37/31-(48)+50/85*(33)/80-(59/((48)+81-21)*(91)-(43)*37)/(42+24-(62)/53/(17)+(7)-(51)*(28-(44)/74)+(((31)*52)+44+75+(89))/(70)/(100)-(50)*35+(69*(36-(57)-((24)+(85)-78)*56)-51)/(32+80))-((69)*(49*73)-(76*(55))/45-71)+14+(87)/27-61/((97)+(89)/88)*51+(24)+13/63-88*2*(27)*(15)+(42)"; 
		int ans      =  95*(18/13/(43)*71)-94+31+(15)-92-4+17*(38*(41))+(89)-53*54/(19)/29+95*20*(82)/79+(15)/(33)+32*17-94/38+(53)-(45)*(70)-33+(38)+80-37/31-(48)+50/85*(33)/80-(59/((48)+81-21)*(91)-(43)*37)/(42+24-(62)/53/(17)+(7)-(51)*(28-(44)/74)+(((31)*52)+44+75+(89))/(70)/(100)-(50)*35+(69*(36-(57)-((24)+(85)-78)*56)-51)/(32+80))-((69)*(49*73)-(76*(55))/45-71)+14+(87)/27-61/((97)+(89)/88)*51+(24)+13/63-88*2*(27)*(15)+(42); 
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

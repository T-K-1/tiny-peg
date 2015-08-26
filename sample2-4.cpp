
// tiny-peg ver2.0


#include <stdio.h>
#include <string>
#include <list>

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
 In this sample, I improve sample2-2.cpp so that "is_expr" can output assembly-language-like codes. 

*/

#define _set(a, b) (a = (b), true)
#define P(str) (list.push_back(str), true)

bool output_asm_expr(_iterator &it, std::list<std::string> &list); 
bool is_expr(_iterator &it, std::list<std::string> &list); 
bool is_term(_iterator &it, std::list<std::string> &list); 
bool is_factor(_iterator &it, std::list<std::string> &list); 
bool is_varname(_iterator &it, std::string &name); 

bool output_asm_expr(_iterator &it, std::list<std::string> &list){
	return P("++s; ") && is_expr(it, list) &&  P("--s; "); 
}

bool is_expr(_iterator &it, std::list<std::string> &list){ 
	bool isMinus = false; 
	_head; 
	if(is_term(it, list) && LOOP(0) && _L && _is('+') && _C && _is('-') && _set(isMinus, true) && _R && P("++s; ") && is_term(it, list) && P("--s; ") && (isMinus && P("*s -= *(s + 1); ") && _set(isMinus, false) || P("*s += *(s + 1); ")) && END_LOOP){ return _true; }
	return _false; 
}

bool is_term(_iterator &it, std::list<std::string> &list){ 
	bool isDiv = false; 
	_head; 
	if(is_factor(it, list) && LOOP(0) && _L && _is('*') && _C && _is('/') && _set(isDiv, true) && _R && P("++s; ") && is_factor(it, list) && P("--s; ") && (isDiv && P("*s /= *(s + 1); ") && _set(isDiv, false) || P("*s *= *(s + 1); ")) && END_LOOP){ return _true; }
	return _false; 
}

bool is_factor(_iterator &it, std::list<std::string> &list){ 
	bool isMinus = false; std::string name; 
	_head; 
	if(H && _is('+') && _C && _is('-') && _set(isMinus, true) && END_H && _L && _is('(') && is_expr(it, list) && _is(')') && _C && is_varname(it, name) && P("*s = " + name + "; ") && _R && (!isMinus || P("*s *= -1; "))){ return _true; }
	return _false; 
}


#define _is_(c) _is(c) && (name += c, true)

bool is_varname(_iterator &it, std::string &name){
	_head; 
	if(LOOP(1) && _is_('a') && _C && _is_('b') && _C && _is_('c') && _C && _is_('d') && _C && _is_('e') && _C && _is_('f') && _C && _is_('g') && _C && _is_('h') && _C && _is_('i') && _C && _is_('j') && _C && _is_('k') && _C && _is_('l') && _C && _is_('m') && _C && _is_('n') && _C && _is_('o') && _C && _is_('p') && _C && _is_('q') && _C && _is_('r') && _C && _is_('s') && _C && _is_('t') && _C && _is_('u') && _C && _is_('v') && _C && _is_('w') && _C && _is_('x') && _C && _is_('y') && _C && _is_('z') && _C && _is_('A') && _C && _is_('B') && _C && _is_('C') && _C && _is_('D') && _C && _is_('E') && _C && _is_('F') && _C && _is_('G') && _C && _is_('H') && _C && _is_('I') && _C && _is_('J') && _C && _is_('K') && _C && _is_('L') && _C && _is_('M') && _C && _is_('N') && _C && _is_('O') && _C && _is_('P') && _C && _is_('Q') && _C && _is_('R') && _C && _is_('S') && _C && _is_('T') && _C && _is_('U') && _C && _is_('V') && _C && _is_('W') && _C && _is_('X') && _C && _is_('Y') && _C && _is_('Z') && _C && _is_('0') && _C && _is_('1') && _C && _is_('2') && _C && _is_('3') && _C && _is_('4') && _C && _is_('5') && _C && _is_('6') && _C && _is_('7') && _C && _is_('8') && _C && _is_('9') && END_LOOP){ return _true; }
	return _false; 
}


void test(char const *str){
	_iterator it = str; 
	std::list<std::string> list; 

	if(!output_asm_expr(it, list)){ printf("[err: false == output_asm_expr]\n"); return; }
	if(0 != *it){ printf("[err: 0 != *it][%s]\n", it); return; }

	printf("\n-----------------------------\n[%s]\n", str);
	for(std::list<std::string>::iterator i = list.begin(), e = list.end(); i != e; ++i){
		printf("%s\n", i->c_str()); 
	}
	printf("(Thus *(s + 1) == %s.)\n", str);
}


int main(int argc, char *argv[]){

	test("2015");
	test("3+abcde");
	test("a+b+c"); 
	test("-a*-b/-c"); 
	test("(-a*-b)/-c"); 
	test("-a*(-b/-c)"); 
	test("-(b+c/d)*-a"); 
	test("a*-(-b+c*34/(x+(y/-z)))"); 

	return 0; 
}

/*
result: 

-----------------------------
[2015]
++s; 
*s = 2015; 
--s; 
(Thus *(s + 1) == 2015.)

-----------------------------
[3+abcde]
++s; 
*s = 3; 
++s; 
*s = abcde; 
--s; 
*s += *(s + 1); 
--s; 
(Thus *(s + 1) == 3+abcde.)

-----------------------------
[a+b+c]
++s; 
*s = a; 
++s; 
*s = b; 
--s; 
*s += *(s + 1); 
++s; 
*s = c; 
--s; 
*s += *(s + 1); 
--s; 
(Thus *(s + 1) == a+b+c.)

-----------------------------
[-a*-b/-c]
++s; 
*s = a; 
*s *= -1; 
++s; 
*s = b; 
*s *= -1; 
--s; 
*s *= *(s + 1); 
++s; 
*s = c; 
*s *= -1; 
--s; 
*s /= *(s + 1); 
--s; 
(Thus *(s + 1) == -a*-b/-c.)

-----------------------------
[(-a*-b)/-c]
++s; 
*s = a; 
*s *= -1; 
++s; 
*s = b; 
*s *= -1; 
--s; 
*s *= *(s + 1); 
++s; 
*s = c; 
*s *= -1; 
--s; 
*s /= *(s + 1); 
--s; 
(Thus *(s + 1) == (-a*-b)/-c.)

-----------------------------
[-a*(-b/-c)]
++s; 
*s = a; 
*s *= -1; 
++s; 
*s = b; 
*s *= -1; 
++s; 
*s = c; 
*s *= -1; 
--s; 
*s /= *(s + 1); 
--s; 
*s *= *(s + 1); 
--s; 
(Thus *(s + 1) == -a*(-b/-c).)

-----------------------------
[-(b+c/d)*-a]
++s; 
*s = b; 
++s; 
*s = c; 
++s; 
*s = d; 
--s; 
*s /= *(s + 1); 
--s; 
*s += *(s + 1); 
*s *= -1; 
++s; 
*s = a; 
*s *= -1; 
--s; 
*s *= *(s + 1); 
--s; 
(Thus *(s + 1) == -(b+c/d)*-a.)

-----------------------------
[a*-(-b+c*34/(x+(y/-z)))]
++s; 
*s = a; 
++s; 
*s = b; 
*s *= -1; 
++s; 
*s = c; 
++s; 
*s = 34; 
--s; 
*s *= *(s + 1); 
++s; 
*s = x; 
++s; 
*s = y; 
++s; 
*s = z; 
*s *= -1; 
--s; 
*s /= *(s + 1); 
--s; 
*s += *(s + 1); 
--s; 
*s /= *(s + 1); 
--s; 
*s += *(s + 1); 
*s *= -1; 
--s; 
*s *= *(s + 1); 
--s; 
(Thus *(s + 1) == a*-(-b+c*34/(x+(y/-z))).)

*/

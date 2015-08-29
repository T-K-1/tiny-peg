
// tiny-peg ver3.0


#include <stdio.h>

// Definition of tiny-peg ver3.0 (21 lines) 
// This version is a refactoring of ver2.1. 
typedef char const *_iterator; 
static bool is_err = false, not_predicate_flag = false; 
static _iterator it_array[1 << 20], *pit = it_array - 1; 
static _iterator const * const it_array_end = it_array + sizeof(it_array) / sizeof(_iterator); 
#define _is(c) c == *it && (++it, true)
#define _L !is_err && (((++pit, true) && it_array_end > pit && (*pit = it, true) || !(is_err = true)) && (true
#define _C !is_err || !is_err && (it = *pit, true)
#define _R !is_err) && (--pit, true) || (--pit, false))
#define PEG(tiny_peg_expression) _iterator const it_old = it; do{ bool result = _L && tiny_peg_expression && _R; if(is_err){ return false; } if(!result){ it = it_old; return false; } }while(false)
#define LOOP(n)  _L && [&]()->bool{ _iterator const it_old = it; for(int ______cnt = 0, ______n = n;                    ; ++______cnt){ if(______n < ______cnt){ ______cnt = ______n; } *pit = it; bool result = true
#define TIMES(n) _L && [&]()->bool{ _iterator const it_old = it; for(int ______cnt = 0, ______n = n; ______cnt < ______n; ++______cnt){                                                 *pit = it; bool result = true
#define END_LOOP  true; if(is_err){ return false; } if(!result){ if(______n > ______cnt){ it = it_old; return false; } it = *pit; return true; } if(it == *pit){ return true; } } return true; }() && _R
#define END_TIMES true; if(is_err){ return false; } if(!result){                          it = it_old; return false;                           } if(it == *pit){ return true; } } return true; }() && _R 
#define H _L
#define END_H _C && true && _R
#define AND _L
#define END_AND !is_err) && (!is_err && (it = *pit, true), --pit, true) || (!is_err && (it = *pit, true), --pit, false))
#define NOT ((AND
#define END_NOT END_AND && (not_predicate_flag = true) || !(not_predicate_flag = false) ) && !is_err && !not_predicate_flag)
#define _mu(a) (_is(a) || !(is_err = true))
#define mu_(func) (is_##func || !(is_err = true))



/*
 tiny-peg ver3.0 is a refactoring of ver2.1. 
 Explanations for implementation of this tiny-peg is at the end of this file. 
*/

// A <- 'a' 'b' 'c' 'd' 'e'
bool is_A(_iterator &it){ 
	PEG(
		_is('a') && _is('b') && _is('c') && _is('d') && _is('e')
	);
	return true; 
}


// B <- &('a' | 'b') 'c' 'd'
bool is_B(_iterator &it){ 
	PEG(
		AND && _is('a') && _C && _is('b') && END_AND && _is('c') && _is('d')
	);
	return true; 
}


// C <- !('a' 'b') 'a' 
bool is_C(_iterator &it){ 
	PEG(
		NOT && _is('a') && _is('b') && END_NOT && _is('a')
	);
	return true; 
}

// D <- ?('a') 'b'
bool is_D(_iterator &it){ 
	PEG(
		H && _is('a') && END_H && _is('b')
	);
	return true; 
}

// E <- 'd' ('a' 'b' | 'd') 
bool is_E(_iterator &it){
	PEG(
		_is('d') && _L && _is('a') && _is('b') && _C && _is('d') && _R
	);
	return true; 
}

// F <- ('a' | 'b' | ('c' 'd' ('e' | 'f') ) ('g' | 'h') ) 'i' | 'j'
bool is_F(_iterator &it){ 
	PEG(
		_L && _is('a') && _C && _is('b') && _C && _L && _is('c') && _is('d') && _L && _is('e') && _C && _is('f') && _R && _R && _L && _is('g') && _C && _is('h') && _R && _R && _is('i') && _C && _is('j')
	); 
	return true; 
}

// G <- ('a')+
bool is_G(_iterator &it){ 
	PEG(
		LOOP(1) && _is('a') && END_LOOP
	);
	return true; 
}

// H <- ('a' 'b')+5
bool is_H(_iterator &it){ 
	PEG(
		LOOP(5) && _is('a') && _is('b') && END_LOOP
	);
	return true; 
}

// I denote by "**n" the counterpart of "TIMES(n)." 
// I <- ('a' 'b')**3
bool is_I(_iterator &it){ 
	PEG(
		TIMES(3) && _is('a') && _is('b') && END_TIMES
	);
	return true; 
}

void test(char const *str, bool (*is_func)(_iterator &)){
	_iterator it = str; 
	printf("[%s] ", it); printf("%d %d\n", is_func(it), it_array - 1 == pit); 
	printf("[%s] ", it); printf("%d %d\n", is_func(it), it_array - 1 == pit); 
	printf("[%s] ", it); printf("%d %d\n", is_func(it), it_array - 1 == pit); 
	printf("\n"); 
}

int main(int argc, char *argv[]){
	test("abcde", is_A); 
	test("dddabx", is_E); 
	test("aaaab", is_G); 
	test("abababababababababababa", is_H); 
	test("ababab", is_H); 
	test("ababababab", is_I); 
	return 0; 
}

/*
result: 

[abcde] 1 1
[] 0 1
[] 0 1

[dddabx] 1 1
[dabx] 1 1
[x] 0 1

[aaaab] 1 1
[b] 0 1
[b] 0 1

[abababababababababababa] 1 1
[a] 0 1
[a] 0 1

[ababab] 0 1
[ababab] 0 1
[ababab] 0 1

[ababababab] 1 1
[abab] 0 1
[abab] 0 1

*/




/*

 Explanations for implementation of tiny-peg ver3.0. 

 it_array: 
 This variable is the counterpart of "it_old" in ver2.1.

 pit:
 This variable is the counterpart of "it_old[__n]" in ver2.1. 

 PEG(tiny_peg_expression):
 This macro is the counterpart of "_head" and "_true" and "_false" in ver2.1. 
 
 LOOP(n) and END_LOOP: 
 The usage of these macros is as same as ver 2.1, namely, "LOOP(n) && [tiny-peg expression] && END_LOOP." 
 If we expand this expression, then we have

 _L && [&]()->bool{ 
	_iterator const it_old = it; 
	for(int ______cnt = 0, ______n = n; ; ++______cnt){ 
		if(______n < ______cnt){ ______cnt = ______n; } 
		*pit = it; 
		bool result = true && [tiny-peg expression] && true; 
		if(is_err){ return false; } 
		if(!result){ if(______n > ______cnt){ it = it_old; return false; } it = *pit; return true; } 
		if(it == *pit){ return true; } 
	} 
	return true; 
 }() && _R

 As you can see, the implementation of these macros is different from ver 2.1, but this works as expected. 

 TIMES(n) and END_TIMES: 
 This TIMES(n) works as "exactly-n operator," so that this macro is actually an extension of PEG. 
 The usage of these macros is "TIMES(n) && [tiny-peg expression] && END_TIMES." 
 Then [tiny-peg expression] must be consumed exactly n times, otherwise the expression 
 "TIMES(n) && [tiny-peg expression] && END_TIMES" returns false. 

*/



// tiny-peg ver2.1


#include <stdio.h>

// Definition of tiny-peg ver2.1 (22 lines) 
// This version is a slight extension of PEG. 
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
#define _mu(a) (_is(a) || !(is_err = true))
#define mu_(func) (is_##func || !(is_err = true))



/*
 tiny-peg ver2.1 is a slight extension of the basic PEG. 
 We can use "_mu(a)" and "mu_(func)" for PEG expressions. 
 If we use _mu('a'), then the character 'a' must be consumed, otherwise 
 tiny-peg ver2.1 does not consume remaining process at all. In this case, 
 the iterator "it" does not backtrack completely: the iterator "it" stays in the position 
 where _mu(a) or mu_(func) failed. Moreover, the variable is_err turns to be "true." 

*/

// I denote by @'a' the counterpart of _mu('a'). 
// A <- 'a' 'b' @'c' @'d'
bool is_A(_iterator &it){
	_head;
	if(_is('a') && _is('b') && _mu('c') && _mu('d')){ return _true; }
	return _false; 
}


// B <- 'a' 'b' 'z'
bool is_B(_iterator &it){
	_head;
	if(_is('a') && _is('b') && _is('z')){ return _true; }
	return _false; 
}

// _C <- B @B
bool is_C(_iterator &it){
	_head;
	if( is_B(it) &&  mu_( B(it) ) ){ return _true; }
	return _false; 
}

// D <- B B
bool is_D(_iterator &it){
	_head;
	if( is_B(it) &&  is_B(it) ){ return _true; }
	return _false; 
}


int main(int argc, char *argv[]){
	
	{
		_iterator it = "abzabcdabc"; 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_A(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_A(it)); printf("is_err == %d\n", is_err); 
		printf("\n"); 
	}

	{ // Since is_err == true, the following is_B does not work at all. 
		_iterator it = "abzabz"; 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("\n"); 
	}

	printf("__n == %d\n\n", __n); // __n always satisfies __n == -1 even if is_err == true. 
	is_err = false; 

	{ // Since is_err == false, the following is_B works as expected. 
		_iterator it = "abzabz"; 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("\n===============================\n\n"); 
	}

	{
		_iterator it = "abzabzabzabcd"; 
		printf("[%s] ", it); printf("%d ", is_D(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_D(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_D(it)); printf("is_err == %d (The iterator \"it\" backtracks completely.)\n", is_err); 
		printf("\n"); 
	}

	{
		_iterator it = "abzabzabzabcd"; 
		printf("[%s] ", it); printf("%d ", is_C(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_C(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_C(it)); printf("is_err == %d (The iterator \"it\" does not backtrack completely.)\n", is_err); 
		printf("\n"); 
	}

	{ // Since is_err == true, the following is_B does not work at all. 
		_iterator it = "abzabz"; 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("\n"); 
	}

	printf("__n == %d\n\n", __n); // __n always satisfies __n == -1 even if is_err == true. 
	is_err = false; 

	{ // Since is_err == false, the following is_B works as expected. 
		_iterator it = "abzabz"; 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("[%s] ", it); printf("%d ", is_B(it)); printf("is_err == %d\n", is_err); 
		printf("\n"); 
	}
	return 0; 
}

/*
result: 

[abzabcdabc] 1 is_err == 0
[abcdabc] 0 is_err == 0
[abcdabc] 1 is_err == 0
[abc] 0 is_err == 1

[abzabz] 0 is_err == 1
[abzabz] 0 is_err == 1
[abzabz] 0 is_err == 1

__n == -1

[abzabz] 1 is_err == 0
[abz] 1 is_err == 0
[] 0 is_err == 0

===============================

[abzabzabzabcd] 1 is_err == 0
[abzabcd] 0 is_err == 0
[abzabcd] 0 is_err == 0 (The iterator "it" backtracks completely.)

[abzabzabzabcd] 1 is_err == 0
[abzabcd] 0 is_err == 1
[abcd] 0 is_err == 1 (The iterator "it" does not backtrack completely.)

[abzabz] 0 is_err == 1
[abzabz] 0 is_err == 1
[abzabz] 0 is_err == 1

__n == -1

[abzabz] 1 is_err == 0
[abz] 1 is_err == 0
[] 0 is_err == 0


*/

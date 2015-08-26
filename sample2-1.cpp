
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
 Below are examples of tiny-peg ver2.0. 
 Explanations for implementation of this tiny-peg is at the end of this file. 
*/

// A <- 'a' 'b' 'c' 'd' 'e'
bool is_A(_iterator &it){ 
	_head; 
	if(_is('a') && _is('b') && _is('c') && _is('d') && _is('e')){ return _true; }
	return _false; 
}


// B <- &('a' | 'b') 'c' 'd'
bool is_B(_iterator &it){ 
	_head; 
	if(AND && _is('a') && _C && _is('b') && END_AND && _is('c') && _is('d')){ return _true; }
	return _false; 
}


// C <- !('a' 'b') 'a' 
bool is_C(_iterator &it){ 
	_head;
	if(NOT && _is('a') && _is('b') && END_NOT && _is('a')){ return _true; }
	return _false; 
}

// D <- ?('a') 'b'
bool is_D(_iterator &it){ 
	_head;
	if(H && _is('a') && END_H && _is('b')){ return _true; }
	return _false; 
}

// E <- 'd' ('a' 'b' | 'd') 
bool is_E(_iterator &it){
	_head;
	if(_is('d') && _L && _is('a') && _is('b') && _C && _is('d') && _R){ return _true; }
	return _false; 
}

// F <- ('a' | 'b' | ('c' 'd' ('e' | 'f') ) ('g' | 'h') ) 'i' | 'j'
bool is_F(_iterator &it){ 
	_head;
	if(_L && _is('a') && _C && _is('b') && _C && _L && _is('c') && _is('d') && _L && _is('e') && _C && _is('f') && _R && _R && _L && _is('g') && _C && _is('h') && _R && _R && _is('i') && _C && _is('j')){ return _true; }
	return _false; 
}

// G <- ('a')+
bool is_G(_iterator &it){ 
	_head;
	if(LOOP(1) && _is('a') && END_LOOP){ return _true; }
	return _false; 
}

// This example is a slight extension of PEG expression. 
// I denote by "+5" the "five-or-more operator." 
// H <- ('a' 'b')+5
bool is_H(_iterator &it){ 
	_head;
	if(LOOP(5) && _is('a') && _is('b') && END_LOOP){ return _true; }
	return _false; 
}

void test(char const *str, bool (*is_func)(_iterator &)){
	_iterator it = str; 
	printf("[%s] ", it); printf("%d %d\n", is_func(it), __n); // __n always satisfies __n == -1. 
	printf("[%s] ", it); printf("%d %d\n", is_func(it), __n); // __n always satisfies __n == -1. 
	printf("[%s] ", it); printf("%d %d\n", is_func(it), __n); // __n always satisfies __n == -1. 
	printf("\n"); 
}

int main(int argc, char *argv[]){
	test("abcde", is_A); 
	test("dddabx", is_E); 
	test("aaaab", is_G); 
	test("abababababababababababa", is_H); 
	test("ababab", is_H); 
	return 0; 
}

/*
result: 

[abcde] 1 -1
[] 0 -1 
[] 0 -1 

[dddabx] 1 -1
[dabx] 1 -1 
[x] 0 -1 

[aaaab] 1 -1 
[b] 0 -1 
[b] 0 -1 

[abababababababababababa] 1 -1 
[a] 0 -1 
[a] 0 -1 

[ababab] 0 -1 
[ababab] 0 -1 
[ababab] 0 -1 

*/




/*

 Explanations for implementation of tiny-peg ver2.0. 


 _L and _R: 
 In this version, we do not have to choose specific n manually for _L(n) and _C(n) and _head(n), 
 because this process is done automatically. The basic idea of implementing this behavior is to 
 take an array of iterator "static _iterator it_old[1 << 20];" and a variable "static int __n = -1;" 
 so that "it_old[__n]" behaves itself like a "stack." Whenever _L appears in tiny-peg expressions, 
 then __n is incremented automatically. Similarly, whenever _R appears in tiny-peg expressions, 
 then __n is decremented automatically. Then one can define _L and _R as 

 #define _L (++__n, it_old[__n] = it, true) && (true
 #define _R true) && (--__n, true)

 However, this implementation does not work as expected. For example, consider the following tiny-peg: 

 _L && _is('a') && _R

 If _is('a') is false, then "--__n" in _R does not work because of "short-circuit evaluation." 
 We can avoid this difficulty if we define _L and _R as 

 #define _L ( (++__n, it_old[__n] = it, true) && ( true
 #define _R true) && (--__n, true) || (--__n, false) )

 This implementation works as expected. Furthermore, I improved this implementation again and I actually defined _L and _R as 

 #define _L !is_err && (((++__n, true) && it_old_end > __n && (it_old[__n] = it, true) || (is_err = true, false)) && (true
 #define _R !is_err) && (--__n, true) || (--__n, false))

 This is because I do not want tiny-peg parser to work any more if is_err == true. 


 _C:
 _C is almost as same as _C(n) of ver1.0. One can define _C as

 #define _C true || (it = it_old[__n], true)

 Furthermore, I improved this implementation again and I actually defined _C as

 #define _C !is_err || !is_err && (it = it_old[__n], true)

 This is because I do not want tiny-peg parser to work any more if is_err == true. 


 Zero-or-more operator: 
 I need Lambda expression to implement zero-or-more operator, so that I need C++ in general. 
 I defined "LOOP" and "END_LOOP" as 

 #define LOOP(n) [&]()->bool{ _head; for(int ______cnt = 0, ______n = n; ; ++______cnt){ if(______n < ______cnt){ ______cnt = ______n; } it_old[__n] = it; bool result = true
 #define END_LOOP true; if(is_err){ return _false; } if(!result){ it = it_old[__n]; if(______n > ______cnt){ return _false; } break; } if(it == it_old[__n]){ break; } } return _true; }() 

 This LOOP(n) works as "n-or-more operator," so that this macro is actually an extension of zero-or-more operator. 
 The usage of this macro is "LOOP(n) && [tiny-peg expression] && END_LOOP." 
 If we expand this expression, then we have

 [&]()->bool{ 
	_head; 
	for(int ______cnt = 0, ______n = n; ; ++______cnt){ 
		if(______n < ______cnt){ ______cnt = ______n; } 
		it_old[__n] = it; 
		bool result = true && [tiny-peg expression] && true; 
		if(is_err){ return _false; } 
		if(!result){ it = it_old[__n]; if(______n > ______cnt){ return _false; } break; } 
		if(it == it_old[__n]){ break; } 
	} 
	return _true; 
 }() 

 This code works as expected. 


 Optional:
 "H" and "END_H" are the counterpart of "?" (optional). 
 The expression "?e" is just a syntactic sugar of 

 (e | '')

 so that I defined H and END_H as 

 #define H _L
 #define END_H _C && true && _R


 And-predicate:
 "AND" and "END_AND" are the counterpart of "&" (and-predicate). 
 The expression "&e" is just a syntactic sugar of 

 !!e

 so that one can define AND and END_AND as

 #define AND NOT && NOT
 #define END_AND END_NOT && END_NOT

 though I did not implement in this way. 
 In fact, one can implement and-predicate by modifying _L and _R. 
 Let _L and _R be defined as 

 #define _L !is_err && (((++__n, true) && it_old_end > __n && (it_old[__n] = it, true) || (is_err = true, false)) && (true
 #define _R !is_err) && (--__n, true) || (--__n, false))

 These _L and _R are the normal _L and _R. Then we modify _R, so that 

 #define _R !is_err) && (it = it_old[__n], --__n, true) || (it = it_old[__n], --__n, false))
 
 These _L and _R clearly work as and-predicate. Thus we can define AND and END_AND as 

 #define AND !is_err && (((++__n, true) && it_old_end > __n && (it_old[__n] = it, true) || (is_err = true, false)) && (true
 #define END_AND !is_err) && (it = it_old[__n], --__n, true) || (it = it_old[__n], --__n, false))

 Since _L is not modified at all, we can define AND and END_AND as 

 #define AND _L
 #define END_AND !is_err) && (it = it_old[__n], --__n, true) || (it = it_old[__n], --__n, false))

 Furthermore, I improved this implementation again and I actually defined END_AND as 

 #define END_AND !is_err) && (!is_err && (it = it_old[__n], true), --__n, true) || (!is_err && (it = it_old[__n], true), --__n, false))

 This is because I do not want iterator "it" to backtrack any more if is_err == true. 


 Not-predicate:
 "NOT" and "END_NOT" are the counterpart of "!" (not-predicate). 
 We can implement not-predicate by a method similar to _L and _R, namely, 

 #define NOT ((AND
 #define END_NOT END_AND && (not_predicate_flag = true) || !(not_predicate_flag = false) ) && !is_err && !not_predicate_flag)


*/


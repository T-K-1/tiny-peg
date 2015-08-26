
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
 Below are examples of tiny-peg ver1.0. 
 See also PEG_tiny-peg.png for reference. 

 Note:
 In this version, we can not use "*" (zero-or-more operator) or "!" (not-predicate) or "&" (and-predicate) or "?" (optional). 
 In fact, one can easily implement "!" and "&" and "?" in this version within C Language. But I did not implement 
 these operators for convenience sake. On the other hand, we need Lambda expression to implement "*", 
 so that we need C++ in general. I could not implement "*" within C Language (in my implementation plan for tiny-peg). 
 I did not implement "*" in this version, for convenience sake. These four operators are available on tiny-peg ver2.0. 

*/

// The first example of tiny-peg is the following: 
// A <- 'a' 'b' 'c' 'd' 'e'
bool is_A(_iterator &it){ 
	_head(1); 
	if(_is('a') && _is('b') && _is('c') && _is('d') && _is('e')){ return true; }
	return _false; 
}


// The second example is the following: 
// B <- ('a' | 'b') 'c' 'd'
bool is_B(_iterator &it){ 
	_head(2); 
	if(_L(1) && _is('a') && _C(1) && _is('b') && _R && _is('c') && _is('d')){ return true; }
	return _false; 
}

/*
 _C(n) is the counterpart of "|" (choice operator for PEG).
 _L(n) is the counterpart of "(" (left bracket for PEG).
 _R is the counterpart of ")" (right bracket for PEG).

 We have to choose specific n manually for _L(n) and _C(n) and _head(n). 
 For example, consider the following PEG expression: 

 F <-   ( 'a' | 'b' | ( 'c' 'd' ( 'e' | 'f' ) ) ( 'g' | 'h' ) ) 'i' | 'j'

 We define the depth of terms of this expression as follows: 

 F <-   ( 'a' | 'b' | ( 'c' 'd' ( 'e' | 'f' ) ) ( 'g' | 'h' ) ) 'i' | 'j'
      0 1  1  1  1  1 2  2   2  3  3  3  3  2 1 2  2  2  2  1 0  0  0  0  0

 Then we only have to choose the corresponding numbers from this sequence. Therefore the tiny-peg expression is given by 

 bool is_F(_iterator &it){ 
	_head(4); 
	if(_L(1) && _is('a') && _C(1) && _is('b') && _C(1) && _L(2) && _is('c') && _is('d') && _L(3) && _is('e') && _C(3) && _is('f') && _R && _R && _L(2) && _is('g') && _C(2) && _is('h') && _R && _R && _is('i') && _C(0) && _is('j')){ return true; }
	return _false; 
 }

 Note: 
 tiny-peg ver2.0 (which appears in sample2-1.cpp, sample2-2.cpp, sample2-3.cpp and sample2-4.cpp) 
 does not require this complicated manual process, because this process is done automatically in ver2.0. 

*/

// The next example is 
// C <- 'a' 'b' | 'b' 
bool is_C(_iterator &it){ 
	_head(1);
	if(_is('a') && _is('b') && _C(0) && _is('b')){ return true; }
	return _false; 
}

// This example is equivalent to is_C: 
// D <- ('a' | '') 'b'
bool is_D(_iterator &it){ 
	_head(2);
	if(_L(1) && _is('a') && _C(1) && true && _R && _is('b')){ return true; }
	return _false; 
}

// E <- 'd' ('a' 'b' | 'd') 
bool is_E(_iterator &it){
	_head(2);
	if(_is('d') && _L(1) && _is('a') && _is('b') && _C(1) && _is('d') && _R){ return true; }
	return _false; 
}

// This example is already appeared: 
// F <- ('a' | 'b' | ('c' 'd' ('e' | 'f') ) ('g' | 'h') ) 'i' | 'j'
bool is_F(_iterator &it){ 
	_head(4);
	if(_L(1) && _is('a') && _C(1) && _is('b') && _C(1) && _L(2) && _is('c') && _is('d') && _L(3) && _is('e') && _C(3) && _is('f') && _R && _R && _L(2) && _is('g') && _C(2) && _is('h') && _R && _R && _is('i') && _C(0) && _is('j')){ return true; }
	return _false; 
}

// G <- 'a' (G | '')
bool is_G(_iterator &it){ 
	_head(2);
	if(_is('a') && _L(1) && is_G(it) && _C(1) && true && _R){ return true; }
	return _false; 
}

void test(char const *str, bool (*is_func)(_iterator &)){
	_iterator it = str; 
	printf("[%s] ", it); printf("%d\n", is_func(it)); 
	printf("[%s] ", it); printf("%d\n", is_func(it)); 
	printf("[%s] ", it); printf("%d\n", is_func(it)); 
	printf("\n"); 
}

int main(int argc, char *argv[]){
	test("abcde", is_A); 
	test("dddabx", is_E); 
	test("aaaab", is_G); 
	return 0; 
}

/*
result: 

[abcde] 1
[] 0
[] 0

[dddabx] 1
[dabx] 1
[x] 0

[aaaab] 1
[b] 0
[b] 0

*/


#include <iostream>
#include <string>
#include "algorithm.h"

bool Test1() {

	return true;
}
bool Test2() {

	return true;
}
bool Test3() {

	return true;
}
bool Test4() {

	return true;
}
bool Test5() {

	return true;
}


void Tests() {
	int trueTests = 0;
	if (Test1()) trueTests++;
	if (Test2()) trueTests++;
	if (Test3()) trueTests++;
	if (Test4()) trueTests++;
	if (Test5()) trueTests++;
	if (trueTests == 5) {
		std::cout << "Tests ran successfully" << std::endl;
	}
}
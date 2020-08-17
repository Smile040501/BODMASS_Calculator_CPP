#include<iostream>
#include<string>
#include<iomanip>
#include "BODMASS_Calculator.h"

/**
		+		: Addition
		- 		: Subtraction or Unary Minus
		* 		: Multiplication
		/ 		: Division
		% 	: Modulo or remainder operator
		** 	: Power
		& 	: Bitwise AND
		| 		: Bitwise OR
		^ 		: Bitwise XOR
		<< 	: Bitwise left shift operator
		>> 	: Bitwise right shift operator
 */

// Function to print the list of operators available
void printListOfOperators() {
	std::cout << "Here is the list of operators you can use..." << std::endl << std::endl;
	std::cout << "		+	: Addition" << std::endl;
	std::cout << "		-	: Subtraction or Unary Minus" << std::endl;
	std::cout << "		*	: Multiplication" << std::endl;
	std::cout << "		/	: Division" << std::endl;
	std::cout << "		%	: Modulo or remainder operator" << std::endl;
	std::cout << "		**	: Power" << std::endl;
	std::cout << "		&	: Bitwise AND" << std::endl;
	std::cout << "		|	: Bitwise OR" << std::endl;
	std::cout << "		^	: Bitwise XOR" << std::endl;
	std::cout << "		<<	: Bitwise left shift operator" << std::endl;
	std::cout << "		>>	: Bitwise right shift operator" << std::endl;
	std::cout << std::endl << std::endl;
}

int main() {
	printListOfOperators();
    std::string expr{};
    std::cout << "Enter the expression to evaluate : " << std::endl;
    std::cin >> expr;
    
    BODMASS_Calculator expression{expr};
	
    //std::cout << "Brackets Matching: " << std::boolalpha << expression.areBracketsMatching() << std::endl;
    //std::cout << "Postfix : " << expression.postfix() << std::endl;
	
    std::cout << "Value : " << expression.value() << std::endl;
    
    std::cout << std::endl;
    return 0;
}

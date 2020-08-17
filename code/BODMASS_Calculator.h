#ifndef _BODMASS_CALCULATOR_
#define _BODMASS_CALCULATOR_

#include<string>
#include<map>
#include<utility>

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

class BODMASS_Calculator {
private:
    std::string expr;
	std::map<std::string, std::pair<int, int>> priorityTable;
    std::map<int, std::string> singleStringMap;
	std::map<int, std::string> postfixMap;
	
    bool checkUnwantedOperatorOperand();
    bool checkCorrectOperatorUse();
	void modifyExpression();
    void createPriorityTable();
    void createSingleStringMap();
    int inStackPrecedence(std::string op);
    int outStackPrecedence(std::string op);
    
public:
    BODMASS_Calculator(std::string expr);
    
    ~BODMASS_Calculator();
    
    bool areBracketsMatching();
    std::string postfix();
    double value();

};

#endif // _BODMASS_CALCULATOR_

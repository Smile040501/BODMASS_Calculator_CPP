#include "BODMASS_Calculator.h"
#include<stack>
#include<iostream>
#include<sstream>
#include<cmath>

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


// Utility function to check unwanted operator or operand
bool BODMASS_Calculator::checkUnwantedOperatorOperand() {
    bool result{true};
    for(const auto &c: expr) {
        if((c>='A' && c<='Z') || (c>='a' && c<='z')) {
            result = false;
            break;
        } else if(c=='`' || c=='~' || c=='!' || c=='@' || c=='#' || c=='$' || c=='_' || c=='\\' || c==';' || c==':' || c=='\"' || c=='\'' || c==',' || c=='?' || c=='=') {
            result = false;
            break;
        }
    }
    if(expr.find("++")!=std::string::npos || expr.find("--")!=std::string::npos || expr.find("&&")!=std::string::npos || expr.find("||")!=std::string::npos) {
        result = false;
    }
    return result;
}

// Utitlity Function to check whether the operators are used correctly or not
bool BODMASS_Calculator::checkCorrectOperatorUse() {
    bool result{true};
    for(size_t i{}; i<expr.length(); i++) {
		// Checking that before and after an operator either a digit should come or the corresponding bracket should come
        if((expr.at(i)=='*' && expr.at(i+1)=='*') || (expr.at(i)=='<' && expr.at(i+1)=='<') || (expr.at(i)=='>' && expr.at(i+1)=='>')) {
            if(!(expr.at(i-1)==')' || expr.at(i-1)=='}' || expr.at(i-1)==']' || (expr.at(i-1)<='9' && expr.at(i-1)>='0'))) {
                result = false;
                break;
            }
            if(!(expr.at(i+2)=='(' || expr.at(i+2)=='{' || expr.at(i+2)=='[' || (expr.at(i+2)<='9' && expr.at(i+2)>='0'))) {
                result = false;
                break;
            }
        } else if((expr.at(i)=='*' && expr.at(i-1)!='*' && expr.at(i+1)!='*') || (expr.at(i)=='/') || (expr.at(i)=='%') || (expr.at(i)=='+') || (expr.at(i)=='&') || (expr.at(i)=='^') || (expr.at(i)=='|')) {
            if(!(expr.at(i-1)==')' || expr.at(i-1)=='}' || expr.at(i-1)==']' || (expr.at(i-1)<='9' && expr.at(i-1)>='0'))) {
                result = false;
                break;
            }
            if(!(expr.at(i+1)=='(' || expr.at(i+1)=='{' || expr.at(i+1)=='[' || (expr.at(i+1)<='9' && expr.at(i+1)>='0'))) {
                result = false;
                break;
            }
        } else if(expr.at(i)=='-' && i!=0) {
            if(expr.at(i-1)=='(' || expr.at(i-1)=='{' || expr.at(i-1)=='[') {
                result = true;
            } else {
                if(!(expr.at(i-1)==')' || expr.at(i-1)=='}' || expr.at(i-1)==']' || (expr.at(i-1)<='9' && expr.at(i-1)>='0'))) {
                result = false;
                break;
                }
                if(!(expr.at(i+1)=='(' || expr.at(i+1)=='{' || expr.at(i+1)=='[' || (expr.at(i+1)<='9' && expr.at(i+1)>='0'))) {
                    result = false;
                    break;
                }
            }
        }
    }
    return result;
}

// Utility Function to modify the given expression to the proper mathematical expression
void BODMASS_Calculator::modifyExpression() {
	
	// Modifying decimal point cases as : .5 => 0.5 and 5. => 5.0
    for(size_t i{}; i<expr.length(); i++) {
        if(expr.at(i)=='.') {
             if(i==0) {
                expr.insert(i, "0");
                i++;
            } else if(expr.at(i-1)<'0' || expr.at(i-1)>'9') {
                expr.insert(i, "0");
                i++;
            }
            if(i+1==expr.length()) {
                expr.insert(i+1, "0");
            } else if(expr.at(i+1)<'0' || expr.at(i+1)>'9') {
                expr.insert(i+1, "0");
            }
        }
    }
    
    // Modifying multiplication cases as : 8(9) => 8*(9) and (8)(9) => (8)*(9) and (8)9 => (8)*9
    for(size_t i{}; i<expr.length(); i++) {
        if(i!=0 && (expr.at(i)=='(' || expr.at(i)=='{' || expr.at(i)=='[')) {
            if((expr.at(i-1)<='9' && expr.at(i-1)>='0') || expr.at(i-1)==')' || expr.at(i-1)=='}' || expr.at(i-1)==']') {
                expr.insert(i, "*");
            }
        } else if(expr.at(i)==')' || expr.at(i)=='}' || expr.at(i)==']') {
            if(i+1<expr.length()) {
                if((expr.at(i+1)<='9' && expr.at(i+1)>='0') || expr.at(i+1)=='(' || expr.at(i+1)=='{' || expr.at(i+1)=='[') {
                    expr.insert(i+1, "*");
                }
            }
        }
    }
    
    // Modifying unary minus cases as : -8*9 => M8*9 and 9*(-8) => 9*(M8)
    for(size_t i{}; i<expr.length(); i++) {
        if(i==0 && expr.at(i)=='-') {
            expr.at(i) = 'M';
        } else if(expr.at(i)=='-' && (expr.at(i-1)=='(' || expr.at(i-1)=='{' || expr.at(i-1)=='[')) {
            expr.at(i) = 'M';
        }
    }
    
    // Modifying power operator cases as : 8**9 => 8P9
    for(size_t i{}; i<expr.length(); i++) {
        if(expr.at(i)=='*' && expr.at(i+1)=='*') {
            expr.at(i) = 'P';
            expr.erase(i+1, 1);
        }
    }
}

// Utility Function to create the priority table for operators and operands
void BODMASS_Calculator::createPriorityTable() {
    priorityTable["1"] = std::pair(18, 18);
    priorityTable["2"] = std::pair(18, 18);
    priorityTable["3"] = std::pair(18, 18);
    priorityTable["4"] = std::pair(18, 18);
    priorityTable["5"] = std::pair(18, 18);
    priorityTable["6"] = std::pair(18, 18);
    priorityTable["7"] = std::pair(18, 18);
    priorityTable["8"] = std::pair(18, 18);
    priorityTable["9"] = std::pair(18, 18);
    priorityTable["0"] = std::pair(18, 18);
    
    priorityTable["("] = std::pair(17, 0);
    priorityTable["["] = std::pair(17, 0);
    priorityTable["{"] = std::pair(17, 0);
    
    priorityTable[")"] = std::pair(0, -1);
    priorityTable["]"] = std::pair(0, -1);
    priorityTable["}"] = std::pair(0, -1);
    
    priorityTable["M"] = std::pair(16, 15);
    priorityTable["P"] = std::pair(14, 13);
    priorityTable["*"] = std::pair(11, 12);
    priorityTable["/"] = std::pair(11, 12);
    priorityTable["%"] = std::pair(11, 12);
    priorityTable["+"] = std::pair(9, 10);
    priorityTable["-"] = std::pair(9, 10);
    priorityTable["<<"] = std::pair(7, 8);
    priorityTable[">>"] = std::pair(7, 8);
    priorityTable["&"] = std::pair(5, 6);
    priorityTable["^"] = std::pair(3, 4);
    priorityTable["|"] = std::pair(1, 2);
}

// Utility Function to create the maping of the operands and operators to interpret them as single unit
// To handle the case of numbers with multiple digits and floating point numbers also
void BODMASS_Calculator::createSingleStringMap() {
    size_t i{};
    int key{};
    while(i<expr.length()) {
        if(expr.at(i)<='9' && expr.at(i)>='0') {	
            std::string num{};
            int countDecimal{};
            while(i<expr.length() && ((expr.at(i)<='9' && expr.at(i)>='0') || expr.at(i)=='.')) {
                num += expr.at(i);
                if(expr.at(i)=='.') {
                    countDecimal++;
                    if(countDecimal>1) {
                        throw 0;
                    }
                }
                i++;
            }
            singleStringMap[key] = num;
            key++;
        } else if(expr.at(i)=='<' && expr.at(i+1)=='<') {
            singleStringMap[key] = "<<";
            key++;
            i+=2;
        } else if(expr.at(i)=='>' && expr.at(i+1)=='>') {
            singleStringMap[key] = ">>";
            key++;
            i+=2;
        } else {
            singleStringMap[key] = expr.at(i);
            key++;
            i++;
        }
    }
}

// Utility Function to return the in stack precedence of the operator/operand
int BODMASS_Calculator::inStackPrecedence(std::string op) {
    if(op.at(0)<='9' && op.at(0)>='0') {
        op = op.at(0);
    }
	return priorityTable[op].second;
}

// Utility Function to return the out stack precedence of the operator/operand
int BODMASS_Calculator::outStackPrecedence(std::string op) {
    if(op.at(0)<='9' && op.at(0)>='0') {
        op = op.at(0);
    }
	return priorityTable[op].first;
}

// Constructor
BODMASS_Calculator::BODMASS_Calculator(std::string expr)
: expr{expr}, priorityTable{}, singleStringMap{}, postfixMap{} {
    createPriorityTable();
}

// Destructor
BODMASS_Calculator::~BODMASS_Calculator() {
}

// Funtion to check the correct brackets matching pairs
bool BODMASS_Calculator::areBracketsMatching() {
    std::stack<char> bracketStack;
    bool result{true};
    for(const auto &c: expr) {
        if(c == '{' || c == '[' || c == '(') {
            bracketStack.push(c);
        } else if(c == '}') {
            if(!bracketStack.empty()) {
                if(bracketStack.top() == '{') {
                    bracketStack.pop();
                } else {
                    result = false;
                    break;
                }
            } else {
                result = false;
                break;
            }
        } else if(c == ']') {
            if(!bracketStack.empty()) {
                if(bracketStack.top() == '[') {
                    bracketStack.pop();
                } else {
                    result = false;
                    break;
                }
            } else {
                result = false;
                break;
            }
        } else if(c == ')') {
            if(!bracketStack.empty()) {
                if(bracketStack.top() == '(') {
                    bracketStack.pop();
                } else {
                    result = false;
                    break;
                }
            } else {
                result = false;
                break;
            }
        }
    }
    if(!bracketStack.empty()) {
        result = false;
    }
    return result;
}

// Function to get the postfix expression of the input expression
std::string BODMASS_Calculator::postfix() {
    std::string result{};
    if(areBracketsMatching()) {
        try {
            if(checkUnwantedOperatorOperand() && checkCorrectOperatorUse()) {
				modifyExpression();
                createSingleStringMap();
                std::stack<std::string> operatorStack;
                int key{};
                for(size_t i{}; i<singleStringMap.size();) {
                    if(operatorStack.empty() && (singleStringMap[i]!=")" || singleStringMap[i]!="}" || singleStringMap[i]!="]")) {
                        operatorStack.push(singleStringMap[i]);
                        i++;
                    } else {
                        if(inStackPrecedence(operatorStack.top()) < outStackPrecedence(singleStringMap[i])) {
                            operatorStack.push(singleStringMap[i]);
                            i++;
                        } else if(inStackPrecedence(operatorStack.top()) > outStackPrecedence(singleStringMap[i])) {
                            result += operatorStack.top();
                            postfixMap[key] = operatorStack.top();
                            key++;
                            operatorStack.pop();
                        } else {
                            operatorStack.pop();
                            i++;
                        }
                    }
                }
                while(!operatorStack.empty()) {
                    result += operatorStack.top();
                    postfixMap[key] = operatorStack.top();
                    key++;
                    operatorStack.pop();
                }
            } else {
                std::cout << std::endl << std::endl;
                std::cout << "*************************************************************************************************************" << std::endl;
                std::cout << "An unexpected error occured." << std::endl << "Please try again & Make sure you have entered a correct Mathematical Expression with proper paranthesization" << std::endl;
                std::cout << "*************************************************************************************************************" << std::endl;
                std::cout << std::endl;
            }
        } catch(...) {
            std::cout << std::endl << std::endl;
            std::cout << "*************************************************************************************************************" << std::endl;
            std::cout << "An unexpected error occured." << std::endl << "Please try again & Make sure you have entered a correct Mathematical Epression with proper paranthesization" << std::endl;
            std::cout << "*************************************************************************************************************" << std::endl;
            std::cout << std::endl;
        }
    } else {
		std::cout << std::endl << std::endl;
		std::cout << "*************************************************************************************************************" << std::endl;
		std::cout << "Error : Brackets Not Matching In The Expression..." << std::endl;
		std::cout << "*************************************************************************************************************" << std::endl;
		std::cout << std::endl;
    }
    return result;
}

// Function to calculate the value of the entered expression
double BODMASS_Calculator::value() {
    if(postfixMap.size()==0) {
        postfix();
    }
    std::stack<double> operandStack;
    for(size_t i{}; i<postfixMap.size(); i++) {
        if(postfixMap[i].at(0)<='9' && postfixMap[i].at(0)>='0') {
            std::stringstream ss{postfixMap[i]};
            double value{};
            ss >> value;
            operandStack.push(value);
        } else {
            double newValue{};
            if(postfixMap[i]=="M") {		// Unary Minus
                double temp{operandStack.top()};
                operandStack.pop();
                newValue = -temp;
                operandStack.push(newValue);
            } else {
                double val1{operandStack.top()};
                operandStack.pop();
                double val2{operandStack.top()};
                operandStack.pop();
                if(postfixMap[i]=="P") {		// Power
                    newValue = std::pow(val2, val1);
                } else if(postfixMap[i]=="*") {
                    newValue = static_cast<double>(val2 * val1);
                } else if(postfixMap[i]=="/") {
                    newValue = static_cast<double>(val2 / val1);
                } else if(postfixMap[i]=="%") {
                    newValue =static_cast<double>( static_cast<long long>(val2) % static_cast<long long>(val1) );
                } else if(postfixMap[i]=="+") {
                    newValue = static_cast<double>(val2 + val1);
                } else if(postfixMap[i]=="-") {
                    newValue = static_cast<double>(val2 - val1);
                } else if(postfixMap[i]=="<<") {
                    newValue = static_cast<double>( static_cast<long long>(val2) << static_cast<long long>(val1) );
                } else if(postfixMap[i]==">>") {
                    newValue = static_cast<double>( static_cast<long long>(val2) >> static_cast<long long>(val1) );
                } else if(postfixMap[i]=="&") {
                    newValue = static_cast<double>( static_cast<long long>(val2) & static_cast<long long>(val1) );
                } else if(postfixMap[i]=="^") {
                    newValue = static_cast<double>( static_cast<long long>(val2) ^ static_cast<long long>(val1) );
                } else if(postfixMap[i]=="|") {
                    newValue = static_cast<double>( static_cast<long long>(val2) | static_cast<long long>(val1) );
                }
                operandStack.push(newValue);
            }
        }
    }
    if(!operandStack.empty()) {
        return operandStack.top();
    } else {
        return 0.0;
    }
}

// Copyright 2017, Bradley Peterson, Weber State University, all rights reserved.

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>
#include <memory>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;
using std::unique_ptr;

template <typename T>
struct Node {
public:
	T data{}; //the {} means that if not initialized, it will be given that
			  //data type's default value
	unique_ptr<Node<T>> left;//unique_ptr<DataTypeTheUniquePtrIsPointingTo>
	unique_ptr<Node<T>> right;
};

class TreeParser {

public:
	TreeParser();
	void displayParseTree();
	void processExpression(string &expression);

	string computeAnswer();
	void inOrderTraversal() const;
	void postOrderTraversal() const;

protected:
	string expression;
	int position;

private:
	stack<string> mathStack;
	double castStrToDouble(string const &s);
	string castDoubleToStr(const double d);
	void initialize();
	
	bool isDigit(char c);
	bool isOperator(char c);
	void processExpression(Node<string> *p);
	void computeAnswer(Node<string> *p);
	
	void inOrderTraversal(Node<string> * ptr) const;
	void postOrderTraversal(Node<string> * ptr) const;
	unique_ptr< Node<string> > root;

};

void TreeParser::initialize() {
	expression = "";
	position = 0;
	while (!mathStack.empty()) {
		mathStack.pop();
	}

}

double TreeParser::castStrToDouble(const string &s) {
	istringstream iss(s);
	double x;
	iss >> x;
	return x;
}

string TreeParser::castDoubleToStr(const double d) {
	ostringstream oss;
	oss << d;
	return oss.str();

}

TreeParser::TreeParser() {
	initialize();
}

bool TreeParser::isDigit(char c) {

	//run through and check if the char is a digit 1 char at a time
	if (c == '0') {
		return true;
	}
	else if (c == '1') {
		return true;
	}
	else if (c == '2') {
		return true;
	}
	else if (c == '3') {
		return true;
	}
	else if (c == '4') {
		return true;
	}
	else if (c == '5') {
		return true;
	}
	else if (c == '6') {
		return true;
	}
	else if (c == '7') {
		return true;
	}
	else if (c == '8') {
		return true;
	}
	else if (c == '9') {
		return true;
	}

	//if gets to this point must be false
	return false;
	
}

bool TreeParser::isOperator(char c) {

	if (c == '+') {
		return true;
	}
	else if (c == '-') {
		return true;
	}
	else if (c == '*') {
		return true;
	}
	else if (c == '/') {
		return true;
	}
	else if (c == '^') {
		return true;
	}

	//if code gets to this point, it must be false
	return false;
}

void TreeParser::processExpression(string &expression) {
	//if empty
	if (expression == "") {
		return;
	}

	//prep new binary tree
	this->expression = expression;
	position = 0;
	root = std::make_unique<Node<string>>();
	
	//call the private method
	processExpression(root.get());
}

void TreeParser::processExpression(Node<string> *p) {
	//temp string for converting chars to strings
	string tempString;
	
	while (position < expression.length()) {

		// if char is '('
		if (expression.at(position) == '(') {
			//make a new node left of current node, increment position, 
			//then make a recurrsive function call
			p->left = std::make_unique<Node<string>>();
			position++;
			processExpression(p->left.get());
		}
		//if char is digit
		else if (isDigit(expression.at(position))) {
			
			//reset tempString
			tempString = "";

			do {

				//put verified digit into temp string
				tempString += expression.at(position);

				position++;

			} while (isDigit(expression.at(position)));

			//save completed number in current nodes data, then return
			p->data = tempString;

			return;

		}
		//if char is operator
		else if (isOperator(expression.at(position))) {
			//reset tempString then save operator in current node
			tempString = "";
			tempString += expression.at(position);
			p->data = tempString;

			//create a new node to the right
			p->right = std::make_unique<Node<string>>();
			//increment to next char
			position++;
			//and recursively go right
			processExpression(p->right.get());

		}
		//if char is ')'
		else if (expression.at(position) == ')') {
			//return to recursively backtrack
			position++;
			return;
		}
		//if char is a space
		else if (expression.at(position) == ' ') {
			//ignore
			position++;
		}
		else {
			cout << "Somethings wrong. I shouldn't have gotten this far..." << endl;
			position++;
		}
	}
}

string TreeParser::computeAnswer() {
	//start the process going in the private function
	computeAnswer(root.get());
	//collect the completed answer and return it
	return mathStack.top();
}

void TreeParser::computeAnswer(Node<string> *p) {

	if (p) {//if something is in the node
		//look left
		computeAnswer(p->left.get());
		//look right
		computeAnswer(p->right.get());
		//look at the current nodes data
		//if a digit
		if (isDigit(p->data.at(0))) {
			mathStack.push(p->data);
		}
		//else if an operator
		else if (isOperator(p->data.at(0))) {
			//set right operand to what is at the top of the math stack then pop it off
			double rightOp = castStrToDouble(mathStack.top());
			mathStack.pop();

			//set left operand to what is now at the top, then pop that.
			double leftOp = castStrToDouble(mathStack.top());
			mathStack.pop();

			double answer = 0;

			//run through the process of solving for each possible operand
			if (p->data.at(0) == '+') {
				answer = leftOp + rightOp;
			}
			else if (p->data.at(0) == '-') {
				answer = leftOp - rightOp;
			}
			else if (p->data.at(0) == '*') {
				answer = leftOp * rightOp;
			}
			else if (p->data.at(0) == '/') {
				answer = leftOp / rightOp;
			}
			else if (p->data.at(0) == '^') {
				answer = pow(leftOp, rightOp);
			}

			//push the answer on top of the stack
			mathStack.push(castDoubleToStr(answer));
		}
		//just in case something weird gets into the tree
		else {
			cout << "This means you have a weird character in one of your nodes.\n";
		}
	}

	return;
}

void TreeParser::displayParseTree() {
	cout << "The expression seen using in-order traversal: ";
	inOrderTraversal();
	cout << endl;
	cout << "The expression seen using post-order traversal: ";
	postOrderTraversal();
	cout << endl;

}

void TreeParser::inOrderTraversal() const {
	inOrderTraversal(root.get());
	cout << endl;
}

void TreeParser::inOrderTraversal(Node<string> * ptr) const {
	if (ptr) {//if not empty
			  //left visit right
		inOrderTraversal(ptr->left.get());//go left recursively
		cout << ptr->data << " ";// visit
		inOrderTraversal(ptr->right.get());//go right recursively
	}
}

//The Public one, the one the user can call, the one that get's it started
void TreeParser::postOrderTraversal() const {
	postOrderTraversal(root.get());
	cout << endl;
}

//The private one that access pointers and keeps recursion going
//makes a very good manual destructor
void TreeParser::postOrderTraversal(Node<string> * ptr) const {
	if (ptr) {//if not empty
			  //left right visit
		postOrderTraversal(ptr->left.get());//go left recursively
		postOrderTraversal(ptr->right.get());//go right recursively
		cout << ptr->data << " ";// visit
	}
}

void pressAnyKeyToContinue() {
	printf("Press any key to continue\n");

	//Linux and Mac users with g++ don't need this
	//But everyone else will see this message.
#ifndef __GNUC__
	_getch();
#else
	int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif

}


int main() {
	TreeParser *tp = new TreeParser;

	string expression = "(4+7)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output

	expression = "(7-4)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 3 as a double output

	expression = "(4^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 64 as a double output

	expression = "((2-5)-5)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display -8 as a double output

	expression = "(5*(6/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 15 as a double output

	expression = "((1 + 2) * (3 + 4))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 21 as a double output

	expression = "(543+321)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 864 as a double output

	expression = "(((((3+12)-7)*120)/(2+3))^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 7077888 as a double output

	expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 1337 as a double/decimal output

	pressAnyKeyToContinue();
	return 0;
}

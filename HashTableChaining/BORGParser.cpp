#include "BORGParser.h"

// ===== ExecutionStack =====
// Constructor
ExecutionStack::ExecutionStack()
{
	// Set initial array size
	arrSize = 1;

	// Set stack size
	stackSize = 0;

	// Initialize array of HashTables
	scopes = new HashTable*[arrSize] { nullptr };
}

// Destructor
ExecutionStack::~ExecutionStack()
{
	// Delete all HashTable refs in scopes array
	for (int i = 0; i < arrSize; i++) {
		delete scopes[i];
	}

	// Delete array
	delete[] scopes;
}

void ExecutionStack::push(HashTable* newScope)
{
	// Insert HashTable at top of stack
	scopes[stackSize] = newScope;

	// Increment stackSize
	stackSize++;

	// If stack is now full, increase size of array
	if (stackSize >= arrSize) {
		// Double capacity of array
		arrSize *= 2;

		// Create a new array
		HashTable** tempArray = new HashTable*[arrSize] { nullptr };

		// Copy existing elements to new array
		for (int i = 0; i < stackSize; i++) {
			tempArray[i] = scopes[i];
		}

		// Delete old array
		delete[] scopes;

		// Rename new scopes
		scopes = tempArray;
	}
}

HashTable* ExecutionStack::pop()
{
	// Decrement stack size
	stackSize--;

	// Get scope at top of stack
	HashTable* currScope = scopes[stackSize];

	// Reset spot in stack
	scopes[stackSize] = nullptr;

	// Return scope
	return currScope;
}

HashTable* ExecutionStack::getCurrentScope()
{
	if (stackSize > 0) {
		return scopes[stackSize - 1];
	}
	else {
		return nullptr;
	}
}

void ExecutionStack::addNodeToCurrentScope(std::string key, int value)
{
	// Get current scope
	HashTable* currentScope = getCurrentScope();

	// Insert key value pair
	currentScope->insert(key, value);
}

Node* ExecutionStack::findNode(std::string key)
{
	Node* n;

	// walk through execution stack starting with top of stack
	for (int i = stackSize - 1; i >= 0; i--) {
		// look for key in scope
		n = scopes[i]->find(key);

		if (n != nullptr) {
			return n;
		}
	}
	return nullptr;
}


void ExecutionStack::print()
{
	for (int i = 0; i < arrSize; i++) {
		std::cout << i << ": " << scopes[i] << std::endl;
	}
}

int ExecutionStack::getArraySize()
{
	return arrSize;
}

int ExecutionStack::getStackSize()
{
	return stackSize;
}


// ===== BORGParser =====
// Constructor
BORGParser::BORGParser(std::string filename)
{
	// Initialize execution stack
	executionStack = new ExecutionStack();

	// Open file
	std::ifstream f;
	f.open(filename);

	// Read file line by line, and execute
	std::string line;
	int linenumber = 1;
	while (std::getline(f, line)) {
		 parseLine(line);

		//// test line parser:
		//std::string* words = splitLine(line);
		//std::cout << linenumber << ": ";
		//for (int i = 0; i < 10; i++) {
		//	std::cout << i << words[i] << "\t";
		//}
		//std::cout << std::endl;
		//linenumber++;

	}
}

BORGParser::~BORGParser() {
	delete executionStack;
}

void BORGParser::addScope()
{
	HashTable* ht = new HashTable();
	executionStack->push(ht);
}

void BORGParser::removeScope()
{
	executionStack->pop();
}

int BORGParser::getVarValue(std::string var)
{
	return executionStack->findNode(var)->value;
}

void BORGParser::createVar(std::string var, int value)
{
	// Add variable to current scope
	executionStack->addNodeToCurrentScope(var, value);
}

void BORGParser::updateVar(std::string var, int value)
{
	// Find var
	Node* n = executionStack->findNode(var);

	// Update value
	n->value = value;

}


bool BORGParser::isNumber(std::string word)
{
	bool decimal = false;
	for (std::string::iterator it = word.begin(); it != word.end(); ++it) {
		if (*it == '-' && it == word.begin()) {
			continue;
		}
		else if (*it == '.' && !decimal) {
			decimal = true;
		}
		else if (!std::isdigit(*it)) {
			return false;
		}
	}

	return true;
}

bool BORGParser::isBinaryOperator(char c)
{
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
	else if (c == '%') {
		return true;
	}

	return false;
}

std::string* BORGParser::splitLine(std::string line)
{
	std::string* words = new std::string[50];

	// Split into words
	std::string word = "";
	int i = 0;
	for (std::string::iterator it = line.begin(); it != line.end(); it++) {
		if (word.length() > 0 && std::isspace(*it)) {
			// reached end of word... 
			// add to words array 
			words[i] = word;

			// reset word
			word = "";

			// increment position in words array
			i++;
		}
		//else if (word.length() > 0 && isBinaryOperator(*it)) {	// TODO: handle non-space-separated operators
		//	// reached end of word... 
		//	// add to words array 
		//	words[i] = word;

		//	// reset word
		//	word = "" + *it;

		//	// increment position in words array
		//	i++;


		//}
		else {
			// add onto word if character is not whitespace
			if (!std::isspace(*it)) {
				word += *it;
			}
		}
	}

	// Add last word to words array
	words[i] = word;

	// Return array of words
	return words;
}

int BORGParser::evaluateExpression(std::string* words)
{
	// Assume only one operation allowed
	// TODO: build expression tree; handle more complex expressions
	int operand1;
	int operand2;

	// Get first operand
	if (isNumber(words[0])) {
		operand1 = stoi(words[0]);
	}
	else {
		// if operand1 is not a number, look for variable
		operand1 = getVarValue(words[0]);

		// throw an error if not found
	}

	// Check whether there's an operator after operand1
	if (isBinaryOperator(*words[1].begin())) {
		// if it is an operator, get second operand and evaluate
		if (isNumber(words[2])) {
			operand2 = stoi(words[2]);
		}
		else {
			// if operand1 is not a number, look for variable
			operand2 = getVarValue(words[2]);
		}

		if (words[1] == "+") {
			return operand1 + operand2;
		}
		if (words[1] == "-") {
			return operand1 - operand2;
		}
		if (words[1] == "*") {
			return operand1 * operand2;
		}
		if (words[1] == "/") {
			return operand1 / operand2;
		}
		if (words[1] == "^") {
			return pow(operand1, operand2);
		}
		if (words[1] == "%") {
			return operand1 % operand2;
		}
	}
	else {
		return operand1;
	}

}

// Parse line and execute
void BORGParser::parseLine(std::string line)
{
	// if empty line: continue
	if (line.length() == 0) {
		return;
	}

	// TODO -- figure out size of words
	// Split line into words
	std::string* words = splitLine(line);

	// if line == START: create a new scope
	if (words[0] == "START") {
		addScope();
		return;
	}

	// if line == FINISH: remove scope
	else if (words[0] == "FINISH") {
		removeScope();
		return;
	}

	// if line starts with COM ignore
	else if (words[0] == "COM") {
		return;
	}

	// if line starts with PRINT, print value of variable or expression
	else if (words[0] == "PRINT") {
		// Split line into words
		std::string* words = splitLine(line);

		// Evaluate expression to print
		std::cout << evaluateExpression(words+1) << std::endl;

	}

	// if line starts with VAR, create new variable
	else if (words[0] == "VAR") {
		// First word is VAR; second word is variable name
		// if third word is =, assign the value of the expression that follows... 
		std::string key = words[1];
		int value;
		if (words[2] == "=") {
			//value = evaluateExpression(
			//	line.substr(
			//		line.find('='), 
			//		line.length() - line.find('=')
			//	)
			//);
			value = evaluateExpression(words+3);
		}

		// 
		createVar(key, value);

		return;
	}

	// otherwise, line updates a variable
	else {
		// First word is variable name
		std::string key = words[0];
		int value;
		if (words[1] == "=") {
			value = evaluateExpression(words+2);
		}
		else if (words[1] == "++") {
			value = getVarValue(key) + 1;
		}
		else if (words[1] == "--") {
			value = getVarValue(key) - 1;
		}
		else {
			value = INT_MIN;
		}

		// Update key value pair
		updateVar(key, value);
	}
}


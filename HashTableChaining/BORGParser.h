#ifndef BORGParser
#include <iostream>
#include <fstream>
#include <cmath>
#include "HashTable.h"


// Array based stack of hash tables
// Each hash table represents a scope in the program
class ExecutionStack 
{
private:
	int arrSize;	// capacity
	int stackSize;	// # of items currently stored
	HashTable** scopes;
public:
	ExecutionStack();
	~ExecutionStack();

	// Add or remove scopes from stack
	void push(HashTable*);
	HashTable* pop();

	// Edit current scope
	HashTable* getCurrentScope();
	void addNodeToCurrentScope(std::string key, int value);

	// Find node
	Node* findNode(std::string key);

	// Helpful debugging functions
	void print();
	int getArraySize();
	int getStackSize();
};


// Parse and execute a BORG program
class BORGParser
{
private:
	ExecutionStack* executionStack; // Stack of hash tables

	//void print();

	// Helper functions to execute BORG code
	void addScope();		// start of new scope
	void removeScope();		// end of scope
	int getVarValue(std::string var);				// lookup value of variable
	void createVar(std::string var, int value);		// add a variable to the hash table
	void updateVar(std::string var, int value);		// update variable

	// Functions to read BORG code and evaluate]
	bool isNumber(std::string word);			// check whether a word is numeric
	bool isBinaryOperator(char word);	// check whether a word is an operator
	std::string* splitLine(std::string line);	// given line, split into words
	int evaluateExpression(std::string* words);	// given string expression, return evaluated value
	void parseLine(std::string line);	// parse a line of code
	
public:
	BORGParser(std::string filename);
	~BORGParser();
	
};

#endif // !BORGParser

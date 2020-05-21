#include "assert.h"
//#include "HashTable.h"
#include "BORGParser.h"

/*
Assumptions:
- all vars are integers
- expressions are written with spaces separating all operators and operands 
  (eg x ++, not x++) 
- VAR declarations come with an assignment immediately
*/

int main() {

	// =======================================================================
	//		TEST HASH TABLE 
	// =======================================================================
	//HashTable* ht = new HashTable();

	//// test insert
	//ht->insert("ABC", 2);
	//ht->insert("abc", 3);
	//ht->insert("abxpe2", 1);
	//ht->print();

	//// test lookup
	//assert(ht->find("abxpe2")->value == 1);
	//assert(ht->find("xyz") == nullptr);


	// =======================================================================
	//		TEST EXECUTION STACK
	// =======================================================================
	//ExecutionStack* mystack = new ExecutionStack();

	//// Print initial settings
	//std::cout << "Arr Size: " << mystack->getArraySize() << "; Stack Size: " << mystack->getStackSize() << std::endl;

	//// Add scope to stack
	//mystack->push(ht);
	//std::cout << "Arr Size: " << mystack->getArraySize() << "; Stack Size: " << mystack->getStackSize() << std::endl;

	//// Add another scope to stack
	//HashTable* ht2 = new HashTable();
	//mystack->push(ht2);
	//// test ExecutionStack->addNodeToCurrentScope()
	//mystack->addNodeToCurrentScope("abc", 5);
	//mystack->addNodeToCurrentScope("xx", 11);
	//std::cout << "\nhash table 2: " << std::endl;
	//ht2->print();
	//std::cout << "Arr Size: " << mystack->getArraySize() << "; Stack Size: " << mystack->getStackSize() << std::endl;

	//// Test findNode in stack
	//assert(mystack->findNode("abc")->value == 5);	// should return node from ht2, not ht1
	//assert(mystack->findNode("ABC")->value == 2);	// test key not in ht2, but in ht1
	//assert(mystack->findNode("z") == nullptr);		// test key not in stack

	//// Remove scope from stack
	//mystack->pop();
	//std::cout << "Arr Size: " << mystack->getArraySize() << "; Stack Size: " << mystack->getStackSize() << std::endl;

	//// Now lookup of abc should return value from first scope
	//assert(mystack->findNode("abc")->value == 3);	// should return node from ht

	//mystack->print();

	//delete mystack;


	// =======================================================================
	//		TEST BORG PARSER
	// =======================================================================
	BORGParser* borg = new BORGParser("BORGProgram1.txt");
}
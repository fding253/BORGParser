#ifndef HASHTABLE_H
#include <string>
#include <iostream>

// Define nodes that can store key-value pairs
class Node {
public:
	std::string key;
	int value;
	Node* next;

	// Constructor
	Node(std::string k, int v) {
		key = k;
		value = v;
		next = nullptr;
	};

	// Destructor
	~Node() {
		delete next;
	};
};

// Chained hash table
class HashTable
{
private:
	const int TABLE_SIZE = 101;
	Node** table;		// array of lists of nodes

	int hashFunction(std::string key);

public:
	HashTable();
	~HashTable();

	// Insert key value pair into hash table
	void insert(std::string key, int value);

	// Find node
	Node* find(std::string key);

	// For testing: print hash table
	void print();

};


#endif // !HASHTABLE_H




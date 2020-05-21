#include <string>
#include "HashTable.h"


int HashTable::hashFunction(std::string key)
{
	// Function: sum the ordinal values of the characters of the variable
	// multiplied by their position in the string (1-indexing), 
	// then take the modulo by TABLESIZE.
	// eg:  ABC = (65 * 1 + 66 * 2 + 67 * 3) % TABLESIZE

	// Iterate through characters in string
	int charSum = 0;
	char curr;
	for (unsigned int i = 0; i < key.length(); i++) {
		curr = key[i];
		charSum += (i+1) * (int)curr;

		//std::cout << curr << " -> " << (int)curr << " * " << i+1 << std::endl;
	}

	// Return the sum, modulo TABLE_SIZE
	return charSum % TABLE_SIZE;
}


HashTable::HashTable()
{
	// Initialize hash table to nullptrs
	table = new Node * [TABLE_SIZE] {nullptr};

}


HashTable::~HashTable()
{
	// Delete all nodes stored in hashtable
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i] != nullptr) {
			Node* currNode = table[i];
			Node* nextNode = nullptr;

			while (currNode != nullptr) {
				nextNode = currNode->next;
				delete currNode;
				currNode = nextNode;
			}
		}
	}
}


void HashTable::insert(std::string key, int value)
{
	// Hash the key
	int index = hashFunction(key);

	// Create new node storing key value pair
	Node* newNode = new Node(key, value);

	// Insert node at index
	if (table[index] == nullptr) {
		// no data at index - put newNode in
		table[index] = newNode;
	} 
	else {
		// index already contains data; insert newNode at beginning
		newNode->next = table[index];
		table[index] = newNode;
	}
}

Node* HashTable::find(std::string key)
{
	// Get index of key
	int hashIndex = hashFunction(key);

	// Look through nodes at that index
	Node* n = table[hashIndex];		// start at hash index
	while (n != nullptr) {
		if (n->key == key) {
			return n;
		}
		else {
			n = n->next;
		}
	}

	// Walked through all nodes at hashIndex without finding key
	return nullptr;
}

void HashTable::print()
{
	for (int i = 0; i < TABLE_SIZE; i++) {
		std::cout << i << ": ";
		Node* curr = table[i];
		while (curr != nullptr) {
			std::cout << curr->key << "=" << curr->value << " -> ";
			curr = curr->next;
		}
		std::cout << std::endl;
	}
}




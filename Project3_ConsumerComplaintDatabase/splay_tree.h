/*
* COP3530
* 
* Project 3: Consumer Complaints Database (Karens, am I Right? (KAIR) Project)
* 
* Group Name: I Need To Speak With Your Manager (INTSWYM)
* Group Members: Karen Liu, Amy Wu, Erik Meurrens
* 
* 
*/

#pragma once
#include <unordered_set>
#include <iostream>
using namespace std;

/*================ SPLAY TREE CLASS ================*/
// BST with most recently called node at top
// Performs splay function when node is accessed (insert/find)
// Complaints will be stored in separate class from this file
// PLEASE USE ITERATOR AFTER INSERTING ALL NODES INTO TREE; IF MORE NODES
// ARE ADDED/REMOVED AFTER INSTANTIATION, REINSTANTIATE ITERATOR PLEASE
template <typename T>
class SplayTree
{
	/*===PRIVATE NESTED NODE STRUCT===*/
	struct Node 
	{
		// Stores data value and parent, left child, and right child pointers
		T* data;
		Node* parent;
		Node* left;
		Node* right;
		unsigned int count;

		// Constructor
		Node(T* data = nullptr, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr);
		// Destructor
		~Node();
	};

	/*=== VERY IMPORTANT PRIVATE MEMBERS/FUNCTIONS CLUB ===*/
	Node* root;
	Node* maxNode;
	Node* endNode;
	unsigned int numNodes;
	
	void adjustMax();
	// Rotation/Zig-zag operations
	void rotateLeft(Node* N);
	void rotateRight(Node* N);
	void splay(Node* N);

public:
	/*===ITERATOR struct===*/
	struct iterator
	{
		Node* nodePtr;
		Node* endPtr;
		unordered_set<Node*> visited;
	public:
		// Constructor
		iterator(Node* nodePtr = nullptr,  Node* endPtr = nullptr);
		// increment operators (++)
		iterator& operator++();			// pre increment
		iterator operator++(int);		// post increment
		// decrement operators (--)
		iterator& operator--();			// pre decrement
		iterator operator--(int);		// post decrement
		// equality (==)
		bool operator==(const iterator& rhs) const;
		// inequality (!=)
		bool operator!=(const iterator& rhs) const;
		// dereference (*)
		const T& operator*() const;
		T& operator*();
		// indirect member access operator
		T* operator->() const;

	};
	// Return iterator begin
	iterator begin();
	// Return iterator end
	iterator end();

	/*=== VERY IMPORTANT FUNCTIONS ===*/
	// Constructor
	SplayTree();
	SplayTree(T& data);
	// empty
	bool empty() const;
	// size
	unsigned int size() const;
	// peek
	T& peek() const;
	// insert
	bool insert(T& val);
	// erase
	void erase(T& val);
	// clear
	void clear();
	// find
	iterator find(T& val);
	// count
	unsigned int count(T& val);
	// Destructor
	~SplayTree();
};

/*============== FUNCTION DEFINITIONS ==============*/
// ==================================== NODE ====================================
// Constructor
template <typename T>
SplayTree<T>::Node::Node(T* data, Node* parent, Node* left, Node* right) {
	this->data = data;
	this->parent = parent;
	this->left = left;
	this->right = right;

	count = 0;
}
// Destructor
template <typename T>
SplayTree<T>::Node::~Node() {
	delete data;
}
// ==================================== ITERATOR ====================================
// Constructor
template <typename T>
SplayTree<T>::iterator::iterator(Node* nodePtr, Node* endPtr) {
	if (nodePtr != nullptr) {
		if (nodePtr->data != nullptr)
			visited.insert(nodePtr);
	}
	this->nodePtr = nodePtr;
	this->endPtr = endPtr;
}
// Increment operators (++)
template <typename T>
typename SplayTree<T>::iterator& SplayTree<T>::iterator::operator++() {	// pre increment
	if (nodePtr == nullptr || nodePtr->data == nullptr) {
		return *this;
	}

	Node* currNode = nodePtr;
	// Check right, if exists, change currNode to currNode->right and go as far left as can
	if (nodePtr->right->data != nullptr) {
		currNode = currNode->right;
		while (currNode->left->data != nullptr) {
			currNode = currNode->left;
		}
	}
	// Else, keep checking parents until exists and is not visited, assign currNode to parent
	else {
		if (currNode->parent == nullptr)
			currNode == endPtr;
		else {
			while (currNode->parent != nullptr) {
				currNode = currNode->parent;
				if (currNode != *visited.find(currNode)) {
					break;
				}
				if (currNode->parent == nullptr) {
					currNode == endPtr;	// currNode == endNode
					break;
				}
			}
		}
	}

	// Set nodePtr to currNode, insert, and return reference
	nodePtr = currNode;
	visited.insert(nodePtr);
	return *this;
}
template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::iterator::operator++(int) {	// post increment
	SplayTree<T>::iterator temp = *this;
	++*this;
	return temp;
}
// Decrement operators (--)
template <typename T>
typename SplayTree<T>::iterator& SplayTree<T>::iterator::operator--() {	// pre decrement
	// Check if there are no more nodes to revisit
	if (visited.size() == 1) {
		return *this;
	}
	// Consider iterator at splay.end() as well as at a node in tree
	Node* currNode = nodePtr;
	if (currNode == endPtr) {
		currNode = endPtr->parent;
	}
	if (currNode->parent != *visited.find(currNode->parent) && currNode->left == nullptr) {

	}
	// Remove currNode from visited
	visited.erase(currNode);
	// Check left, if exists, change currNode to currNode->left and go as far right as possible
	if (currNode->left != nullptr && currNode->left != endPtr) {
		currNode = currNode->left;
		while (currNode->left->data != nullptr) {
			currNode = currNode->right;
		}
	}
	// Else, keep checking parents until exists and is visited, assign currNode to parent
	else {
		
			while (currNode->parent != nullptr) {
				currNode = currNode->parent;
				if (currNode == *visited.find(currNode)) {
					break;
				}
			}
		
	}

	nodePtr = currNode;
	return *this;
}
template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::iterator::operator--(int) { // post decrement
	SplayTree<T>::iterator temp = *this;
	--*this;
	return temp;
}
// Dereference operators
template <typename T>
const T& SplayTree<T>::iterator::operator*() const{
	return *(this->nodePtr->data);
}
// Dereference operator
template <typename T>
T& SplayTree<T>::iterator::operator*() {
	return *(this->nodePtr->data);
}
// Indirect member access operator
template <typename T>
T* SplayTree<T>::iterator::operator->() const {
	return this->nodePtr->data;
}
// Equality operator
template <typename T>
bool SplayTree<T>::iterator::operator==(const iterator& rhs) const {
	if (nodePtr == rhs.nodePtr) {
		return true;
	}
	else {
		return false;
	}
}
// Inequality operator
template <typename T>
bool SplayTree<T>::iterator::operator!=(const iterator& rhs) const {
	if (nodePtr == rhs.nodePtr) {
		return false;
	}
	else {
		return true;
	}
}

// SPLAY TREE ITERATOR HELPERS
template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::begin() {	// Returns beginning of tree
	Node* beginPtr = endNode;
	if (root != endNode) {
		Node* currNode = root;
		while (currNode->left->data != nullptr) {
			currNode = currNode->left;
		}
		beginPtr = currNode;
	}
	return SplayTree<T>::iterator(beginPtr, endNode);
}
template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::end() {	// Returns end of tree
	Node* endPtr = endNode;
	return SplayTree<T>::iterator(endPtr, endNode);
}

// ==================================== SPLAY TREE FUNCTIONS ====================================
// Constructor
template <typename T>
SplayTree<T>::SplayTree() {
	endNode = new Node();
	root = endNode;
}
template <typename T>
SplayTree<T>::SplayTree(T& data) {
	// Initialize endNode if not done so
	endNode = new Node();
	// Add root node
	root = new Node(&data);
	// Add end node and assign to end
	root->left = endNode;
	root->right = endNode;
	endNode->parent = root;
	// Adjust size accordingly
	numNodes++;
}
// Return true if SplayTree is empty, else return false
template <typename T>
bool SplayTree<T>::empty() const {
	if (this->numNodes > 0) {
		return true;
	}
	else {
		return false;
	}
}
// Returns size (number of elements) of SplayTree
template <typename T>
unsigned int SplayTree<T>::size() const {
	return numNodes;
}
// Returns root node's stored value
template <typename T>
T& SplayTree<T>::peek() const {
	return *(root->data);
}
// Adjusts maxNode Node pointer to point to max value, assigns to endNode parent
template <typename T>
void SplayTree<T>::adjustMax() {
	Node* currNode = root; 
	while (currNode->right != endNode) {
		currNode = currNode->right;
	}
	maxNode = currNode;
	endNode->parent = maxNode;
}
// Performs left rotation on given node
template <typename T>
void SplayTree<T>::rotateLeft(Node* N) {
	cout << "Left" << endl;
	Node* oldNLeft = N->left;
	N->left = N->parent;
	N->parent->right = oldNLeft;
	Node* newNParent = N->parent->parent;
	N->parent->parent = N;
	N->parent = newNParent;
}
// Performs right rotation on given node
template <typename T>
void SplayTree<T>::rotateRight(Node* N) {
	cout << "Right" << endl;
	Node* oldNRight = N->right;
	N->right = N->parent;
	N->parent->left = oldNRight;
	Node* newNParent = N->parent->parent;
	N->parent->parent = N;
	N->parent = newNParent;
}
// Splays node according to appropriate splay/rotation operations
template <typename T>
void SplayTree<T>::splay(Node* N) {
	cout << N << endl;
	if (N != nullptr) {
		while (N->parent != nullptr) {
			cout << "Need to see" << endl;
			// If node parent's parent == nullptr
			if (N->parent->parent == nullptr) {
				// Perform zig (right) rotation
				if (N->parent->left == N) {
					rotateRight(N);
					
				}
				// Perform zag (left) rotation
				else {
					rotateLeft(N);
					
				}
			}
			else {
				// Perform zig-...
				if (N->parent->left == N) {
					//. . . zig(right - right) rotation
					if (N->parent->parent->left == N->parent) {
						rotateRight(N->parent);
						rotateRight(N);
					}
					//. . . zag(right - left) rotation
					else if (N->parent->parent->right == N->parent) {
						rotateRight(N->parent);
						rotateLeft(N);
					}
				}
				// Perform zag-...
				else if (N->parent->right == N) {
					//. . . zag(left - left) rotation
					if (N->parent->parent->right == N->parent) {
						rotateLeft(N->parent);
						rotateLeft(N);
					}
					//. . . zig(left - right) rotation
					else if (N->parent->parent->left == N->parent) {
						rotateLeft(N->parent);
						rotateLeft(N);
					}
				}
			}
		}
	}	
}
// Inserts node with given value in tree
// Proceeds to splay tree after inserting node w/ respect to node inserted
template <typename T>
bool SplayTree<T>::insert(T& val) {
	T* data = new T(val);
	Node* newNode = new Node(data);
	newNode->left = endNode;
	newNode->right = endNode;
	if (root == endNode) {
		root = newNode;
		root->count++;
		numNodes++;
		return true;
	}
	else {
		Node* currNode = root;
		while (currNode != endNode) {
			// Check if currNode->data equals val
			if (*(currNode->data) == val) {
				currNode->count++;
				return true;
			}
			// If not check if currNode is less than
			else if (*(currNode->data) < val) {
				if (currNode->left == endNode) {
					currNode->left = newNode;
					newNode->parent = currNode;
					newNode->count++;
					numNodes++;
					splay(newNode);
					adjustMax();
					return true;
				}
				else {
					currNode = currNode->left;
				}
			}
			// Else is greater than
			else {
				if (currNode->right == endNode) {
					currNode->right = newNode;
					newNode->parent = currNode;
					newNode->count++;
					numNodes++;
					splay(newNode);
					adjustMax();
					return true;
				}
				else {
					currNode = currNode->right;
				}	
			}
		}
	}
	return false;
}
// Finds Node with given value and returns iterator to that node
// Proceeds to splay tree after finding node w/ respect to node inserted
template <typename T>
typename SplayTree<T>::iterator SplayTree<T>::find(T& val) {
	Node* currNode = this->root;
	while (currNode != endNode) {
		if (*(currNode->data) == val) {
			break;
		}
		else if (*(currNode->data) < val) {
			currNode = currNode->left;
		}
		else {
			currNode = currNode->right;
		}
	}
	splay(currNode);
	return iterator(currNode, endNode);
}
// Finds node of given value and returns the count of elements within that node
template <typename T>
unsigned int SplayTree<T>::count(T& val) {
	return find(val).nodePtr->count;
}
// Erases given value from the tree
template <typename T>
void SplayTree<T>::erase(T& val) {
	if (root == nullptr || root == endNode) {
		return;
	}
	else {
		Node* toRemove = find(val).nodePtr;
		if (toRemove == endNode || toRemove == nullptr) {
			return;
		}
		Node* leftRoot = toRemove->left;
		Node* rightRoot = toRemove->right;
		if (leftRoot == nullptr) {
			delete toRemove;
			root = rightRoot;
		}
		else {
			root = leftRoot;
			while (root->right != endNode && root->right != nullptr) {
				root = root->right;
			}
			root->right = rightRoot;
			delete toRemove;
		}
	}
	numNodes--;
}
// Clear
template <typename T>
void SplayTree<T>::clear() {
	while (root != endNode || root != nullptr) {
		erase(*(root->data));
	}
}
// Destructor
template <typename T>
SplayTree<T>::~SplayTree() {
	clear();
	delete endNode;
}
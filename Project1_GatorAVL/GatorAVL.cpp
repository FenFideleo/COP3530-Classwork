/*
	Project 1: Gator AVL
	
	Student: Erik Meurrens

*/

#include <cctype>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*================================ STUDENT STRUCT FOR AVL TREE ===============================*/
// Struct for Student objects to put into AVL tree
struct Student {
	string name;
	unsigned int ID;

	// Default Student constructor
	Student(string name = "null", unsigned int ID = -1) {
		this->name = name;
		this->ID = ID;
	}

	// Overloaded comparison operators
	bool operator==(const Student& rhs) {	// Compare IDs for equality
		return this->ID == rhs.ID;
	}
	bool operator==(const unsigned int& ID) {
		return this->ID == ID;
	}
	bool operator==(const string& name) {	// Compare names for equality
		return this->name == name;
	}
	bool operator!=(const Student& rhs) {	// Compare IDs for inequality
		return this->ID != rhs.ID;
	}
	bool operator!=(const unsigned int& ID) {
		return this->ID != ID;
	}
	bool operator!=(const string& name) {	// Compare names for inequality
		return this->name != name;
	}
	bool operator<(const Student& rhs) {		// Check if ID is less than
		return this->ID < rhs.ID;
	}
	bool operator>(const Student& rhs) {		// Check if ID is greater than
		return this->ID > rhs.ID;
	}
};

/*================================ AVL TREE CLASS ===============================*/
class GatorAVLTree {
	// Private Node struct to store student data
	struct Node {
		Student student;
		Node* left;
		Node* right;
		unsigned int height;

		// Default constructor
		Node(Student data = Student()) : height(1), left(nullptr), right(nullptr)
		{
			this->student = data;
			this->left = left;
			this->right = right;
		}
	};

	/*----PRIVATE MEMBERS----*/
	unsigned int numNodes;
	Node* root;

	/*----PRIVATE HELPER FUNCTIONS----*/
	// Returns balance factor of node using height of left subtree minus height of right subtree
	int checkBalance(Node* root) {
		if (!root->left)
			return 0 - root->right->height;
		else if (!root->right)
			return root->left->height - 0;
		else
			return root->left->height - root->right->height;
	}
	// Performs height adjustments on all nodes leading to selected node
	void adjustHeight(Node* root, Node* selected) {
		if (selected->student < root->student){
			adjustHeight(root->left, selected);
		}
		else if (selected->student > root->student){
			adjustHeight(root->right, selected);
		}
		unsigned int arr[2];
		if (root->left)
			arr[0] = root->left->height;
		else
			arr[0] = 0;

		if (root->right)
			arr[1] = root->right->height;
		else
			arr[1] = 0;

		if (arr[0] >= arr[1])
			root->height = arr[0] + 1;
		else
			root->height = arr[1] + 1;
	}
	// Performs left rotation on given node
	void rotateLeft(Node* root) {
		Node* newChild = new Node(*root);
		Node* dead;	// me :)
		newChild->right = root->right->left;
		dead = root->right;
		*root = *root->right;
		root->left = newChild;
		delete dead;

		// Adjust heights
		adjustHeight(this->root, newChild);
	}
	// Performs right rotation on given node
	void rotateRight(Node* root) {
		Node* newChild = new Node(*root);
		Node* dead;
		newChild->left = root->left->right;
		dead = root->left;
		*root = *root->left;
		root->right = newChild;
		delete dead;

		// Adjust heights
		adjustHeight(this->root, newChild);
	}
	// Performs left right rotation on given node
	void rotateLeftRight(Node* root) {
		rotateLeft(root->left);
		rotateRight(root);
	}
	// Performs right left rotation on given node
	void rotateRightLeft(Node* root) {
		rotateRight(root->right);
		rotateLeft(root);
	}
	// Determine appropriate rotation and calls on appropriate function
	void rotate(Node* root, int balanceFactor) {
		// If subtree is left heavy
		if (balanceFactor >= 2) {
			if (checkBalance(root->left) <= -1) {		// If left child is right heavy 
				rotateLeftRight(root);
			}
			else {										// If left child is left heavy
				rotateRight(root);
			}
		}
		// If subtree is right heavy
		else if (balanceFactor <= -2) {
			if (checkBalance(root->right) >= 1) {		// If right child is left heavy
				rotateRightLeft(root);
			}
			else {										// If right child is right heavy
				rotateLeft(root);
			}
		}
		else {
			cout << "Something went wrong. You shouldn't be here. . . " << endl;
		}
	}
	// Helps public insert function by allowing for recursive navigation of tree for insertion
	Node* helpInsert(Node* root, Node* newNode) {
		// If tree is empty
		if (!this->root) {
			this->root = newNode;
			numNodes++;
			return newNode;
		}
		// Else if ID of root == newNode ID, return currently existing node
		else if (root->student == newNode->student)
			return root;
		else {
			// newNode's ID is less than root; go down left subtree
			if (newNode->student < root->student) {
				// If root's left node is unoccupied, assign newNode to it
				if (!root->left) {
					root->left = newNode;
					if (!root->right) {
						root->height++;
					}
					numNodes++;
					return newNode;
				}
				// Else use recursion and check resultant node to determine next instructions
				else {
					unsigned int preInsertHeight = root->left->height;
					Node* checkNode = helpInsert(root->left, newNode);
					if (checkNode != newNode)	// There was no change to tree
						return checkNode;
					else {						// newNode was inserted, adjust height and balance factor
						int balanceFactor = checkBalance(root);
						if (balanceFactor >= 1 && root->left->height != preInsertHeight)
							root->height++;
						if (!(-1 <= balanceFactor && balanceFactor <= 1))
							rotate(root, balanceFactor);
						return checkNode;
					}
				}
			}
			// newNode's ID is greater than root; go down right subtree
			else {
				// If root's right node is unoccupied, assign newNode to it
				if (!root->right) {
					root->right = newNode;
					if (!root->left) {
						root->height++;
					}
					numNodes++;
					return newNode;
				}
				// Else use recursion and check resultant node to determine next instructions
				else {
					unsigned int preInsertHeight = root->right->height;
					Node* checkNode = helpInsert(root->right, newNode);
					if (checkNode != newNode)	// There was no change to tree
						return checkNode;
					else {						// newNode was inserted, adjust height and balance factor
						int balanceFactor = checkBalance(root);
						if (balanceFactor <= -1 && root->right->height != preInsertHeight)
							root->height++;
						if (!(-1 <= balanceFactor && balanceFactor <= 1))
							rotate(root, balanceFactor);
						return checkNode;
					}
				}
			}
		}
	}
	// Used to recursively find all students matching name argument, adding them to passed in foundStudents vector
	void findStudents(Node* root, string& name, vector<Student>& foundStudents) const {
		if (root) {
			if (root->student == name) {
				foundStudents.push_back(root->student);
			}
			findStudents(root->left, name, foundStudents);
			findStudents(root->right, name, foundStudents);
		}
	}
	// Removes Node of given ID from tree and returns root
	Node* removeNode(Node* root, unsigned int ID) {
		// Stuff that at this point I can't even fully understand myself
		// I used my notes
		if (root == nullptr) {	// Item not in tree
			return nullptr;
		}
		else if (ID < root->student.ID) {
			root->left = removeNode(root->left, ID);
			if (root->left)
				adjustHeight(this->root, root->left);
		}
		else if (ID > root->student.ID) {
			root->right = removeNode(root->right, ID);
			if (root->right)
				adjustHeight(this->root, root->right);
		}
		else {
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				numNodes--;
				return nullptr;
			}
			else if (!(root->left && root->right)) {
				if (root->left) {
					Node* temp = root->left;
					delete root;
					numNodes--;
					if (root == this->root)
						this->root = temp;
					root = temp;
					return root;
				}
				else if (root->right) {
					Node* temp = root->right;
					delete root;
					numNodes--;
					if (root == this->root)
						this->root = temp;
					root = temp;
					return root;
				}
			}
			else if (!root->right->left) {
				Node* newParent = root->right;
				Node* newChild = root->left;
				delete root;
				numNodes--;
				if (root == this->root)
					this->root = newParent;
				root = newParent;
				root->left = newChild;
				adjustHeight(this->root, root);
				return root;
			}
			else {
				// Find leftmost node in left subtree of right child
				for (Node* swapParent = root->right; swapParent != nullptr; swapParent = swapParent->left) {
					if (swapParent->left->left == nullptr) {
						// Copy data into root's data and remove by setting parent to reference it's right child
						*root = *swapParent->left;
						Node* temp = swapParent->left->right;
						delete swapParent->left;
						numNodes--;
						swapParent->left = temp;
						adjustHeight(this->root, temp);

						return root;
					}
				}
				
			}
		}

		return root;
	}
	// Finds and returns Student object matching the Nth position in an inorder traversal of the tree
	Student& findStudent(Node* root, unsigned int N) {
		static unsigned int counter = 0;
		// Use inorder traversal to navigate to N and return value
		if (root) {
			findStudent(root->left, N);
			if (counter == N) {
				counter = 0;
				return root->student;
			}
			else {
				counter++;
			}
			findStudent(root->right, N);
		}
	}
	void clear(Node* root) {
		// Performs postorder traversal to delete all nodes
		if (root) {
			clear(root->left);
			clear(root->right);
			delete root;
			numNodes--;
		}
	}
public:
	/*----PUBLIC FUNCTIONS----*/
	// Default constructor
	GatorAVLTree(Node* root = nullptr) : numNodes(0) {
		this->root = root;
		if (root != nullptr) {
			numNodes++;
		}
	}
	// Insert new Student object into AVL tree
	bool insert(Student& student) {
		// Make a new node pointer using student data
		Node* newNode = new Node(student);
		// Call private, overloaded helper insert function to perform recursion
		if (helpInsert(this->root, newNode) == newNode)
			return true;							// If newNode is returned, then successful
		else
			return false;							// If existing node returned, then unsuccessful
	}
	// Searches for and returns Student object based on ID
	Student search(unsigned int ID) const{
		Node* root = this->root;
		while (root) {
			if (ID == root->student.ID) {
				return root->student;
			}
			else if (ID < root->student.ID) {
				root = root->left;
			}
			else {
				root = root->right;
			}
		}
		return Student();
	}
	// Searches for students with matching name, returning a vector of all Student objects with that name
	vector<Student> search(string name) const {
		vector<Student> foundStudents;
		// Use preorder traversal to access every element
		findStudents(root, name, foundStudents);
		return foundStudents;
	}
	// Removes Student object from tree according to ID number
	bool remove(unsigned int ID) {
		unsigned int numNodesPreRemoval = numNodes;
		removeNode(this->root, ID);
		// Node not found
		if (numNodes == numNodesPreRemoval) {
			return false;
		}
		// Node found, deleted
		else {
			return true;
		}
	}
	// Prints inorder traversal of student names within AVL tree
	void printInorder(Node* root = nullptr) const {
		static unsigned int callNum = 0;					// Keeps track of how many nodes have been printed
		if (root == nullptr && callNum == 0) {
			root = this->root;
			callNum++;
		}
		if (root) {
			printInorder(root->left);
			cout << root->student.name;
			if (callNum < numNodes) {
				cout << ", ";
				callNum++;
			}
			else {
				cout << endl;
				callNum = 0;
				return;
			}
			printInorder(root->right);
		}
	}
	// Prints preorder traversal of student names within AVL tree
	void printPreorder(Node* root = nullptr) const {
		static unsigned int callNum = 0;					// Keeps track of how many nodes have been printed
		if (root == nullptr && callNum == 0) {
			root = this->root;
			callNum++;
		}
		if (root) {	
			cout << root->student.name;
			if (callNum < numNodes) {
				cout << ", ";
				callNum++;
			}
			else {
				cout << endl;
				callNum = 0;
				return;
			}
			printPreorder(root->left);
			printPreorder(root->right);
		}
	}
	// Prints postorder traversal of student names within AVL tree
	void printPostorder(Node* root = nullptr) const {
		static unsigned int callNum = 0;					// Keeps track of how many nodes have been printed
		if (root == nullptr && callNum == 0) {
			root = this->root;
			callNum++;
		}
		if (root) {
			printPostorder(root->left);
			printPostorder(root->right);
			cout << root->student.name;
			if (callNum < numNodes) {
				cout << ", ";
				callNum++;
			}
			else {
				cout << endl;
				callNum = 0;
				return;
			}
		}
	}
	// Prints number of existing levels in AVL tree
	void printLevelCount() const {
		cout << root->height << endl;
	}
	// Removes the Student object node at index N of an inorder traversal of the tree
	bool removeInorder(int N) {
		if (N > numNodes) {
			return false;
		}
		else {
			// Use inorder traversal to get to Node
			// Call remove function to remove Node
			return remove(findStudent(this->root, N).ID);
		}	
	}

	~GatorAVLTree() {
		// Delete and clear all nodes
		clear(this->root);
		this->root = nullptr;
	}
};


/*================================ MAIN METHOD ===============================*/
int main() {
	GatorAVLTree GatorAVL;

	// Prepare string stream to parse commands
	istringstream in;
	string cmdLine;
	string instruction;
	
	unsigned int numInstructions;
	getline(cin, instruction);
	numInstructions = stoi(instruction);

	for (unsigned int i = 0; i < numInstructions; i++) {
		// Read command and determine continued execution accordingly
		getline(cin, cmdLine);
		in.clear();
		in.str(cmdLine);
		getline(in, instruction, ' ');
		
		// Determine next execution from instruction
		if (instruction == "insert") {				// insert student node
			bool meetsCriteria = true;
			string arguments;
			string name;
			unsigned int ID;

			getline(in, arguments);
			// Store name and check if name consists of letters and spaces
			name = arguments.substr(0, arguments.rfind("\"") + 1);
			arguments.erase(0, arguments.rfind("\"") + 2);
			name.erase(0, 1);				// Remove first quotation mark
			name.erase(name.size() - 1);	// Remove second quotation mark
			for (unsigned int i = 0; i < name.length(); i++) {
				// If char at i is not a space or an alphabetical character
				if (!(isalpha(name.at(i)) || isspace(name.at(i)))) {
					meetsCriteria = false;
					break;
				}		
			}
			if (!meetsCriteria) {
				cout << "unsuccessful" << endl;
				continue;
			}
			
			// Check if UFID satisfies criteria (8 digits)
			getline(in, arguments, ' ');
			if (arguments.length() != 8)
				meetsCriteria = false;
			try {
				ID = stoi(arguments);
			}
			catch (invalid_argument&) {
				meetsCriteria = false;
			}
			if (!meetsCriteria) {
				cout << "unsuccessful" << endl;
				continue;
			}

			// Create Student object with info from input
			Student newStudent(name, ID);

			// Call GatorAVL.insert command and add Student object
			meetsCriteria = GatorAVL.insert(newStudent);
			
			if (meetsCriteria) {
				cout << "successful" << endl;
			}
			else {
				cout << "unsuccessful" << endl;
			}
		}
		else if (instruction == "remove") {			// remove student node
			bool successful = true;
			string argument;
			unsigned int ID;

			getline(in, argument, ' ');
			try {
				ID = stoi(argument);
				successful = GatorAVL.remove(ID);
			}
			catch (invalid_argument&) {
				successful = !successful;
			}

			if (successful) {
				cout << "successful" << endl;
			}
			else {
				cout << "unsuccessful" << endl;
			}

		}
		else if (instruction == "search") {			// search for student in tree
			bool successful = true;
			string argument;

			getline(in, argument);
			// Check if argument is a potential name
			if (argument.at(0) == '\"' && argument.at(argument.size()-1) == '\"') {
				argument.erase(0, 1);					// Remove first quotation mark
				argument.erase(argument.size() - 1);	// Remove second quotation mark
				string name = argument;
				vector<Student> foundStudents;

				foundStudents = GatorAVL.search(name);
				if (foundStudents.size() == 0) {
					successful = !successful;
				}
				else {
					for (unsigned int i = 0; i < foundStudents.size(); i++) {
						cout << setw(8) << setfill('0') << foundStudents.at(i).ID << endl;
						cout.copyfmt(ios(NULL));
					}
				}
			}

			// Check if argument is a potential ID
			else {
				Student foundStudent;
				unsigned int ID = -1;
				try {
					ID = stoi(argument);
				}
				catch (invalid_argument&) {/*Ignored*/ }
				if (ID != -1) {
					foundStudent = GatorAVL.search(ID);
				}
				if (foundStudent.ID == -1) {
					successful = !successful;
				}
				else {
					cout << foundStudent.name << endl;
				}
			}

			if (!successful) {
				cout << "unsuccessful" << endl;
			}
		}
		else if (instruction == "printInorder") {	// print inorder traversal of tree
			GatorAVL.printInorder();
		}
		else if (instruction == "printPreorder") {	// print preorder traversal of tree
			GatorAVL.printPreorder();
		}
		else if (instruction == "printPostorder") {	// print postorder traversal of tree
			GatorAVL.printPostorder();
		}
		else if (instruction == "printLevelCount") {// printLevelCount
			GatorAVL.printLevelCount();
		}
		else if (instruction == "removeInorder") {	// remove Nth GatorID from inorder list
			bool successful = true;
			string argument;
			unsigned int N;

			getline(in, argument, ' ');
			try {
				N = stoi(argument);
				successful = GatorAVL.removeInorder(N);
			}
			catch (invalid_argument&) {
				successful = !successful;
			}

			if (successful) {
				cout << "successful" << endl;
			}
			else {
				cout << "unsuccessful" << endl;
			}
		}
		else {										// Invalid command
			cout << "Invalid command" << endl;
		}
	}
	
	return 0;
}
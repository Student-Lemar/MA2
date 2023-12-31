/#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {
		Node<T>* current = this->_root;
		int x = 0;
		while (x==0){
			if (current == NULL){
				x = 1;
			}
			if (!current->left == NULL){
				current = current->left;
			}
			else if (!current->right == NULL){
				current = current->right;
			}
			else if (current->right == NULL && current->left == NULL){
				delete Node;
				current = _root;
			}
		}
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		cout << "TODO: Implement printLevelOrder" << endl;
		Node<T>* current = this->_root;
		int x = 0;
		int pos = 1;
		string array [height()];
		array[pos] = std::to_string(current->value);
		while (x==0){
			if (!current->left == NULL){
				pos += 1;
				current = current->left;
				array[pos] = std::to_string(current->value);
			}
			else if (!current->right == NULL){
				pos += 1;
				current = current->right;
				array[pos] = std::to_string(current->value);
			}
			else if (current->right == NULL && current->left == NULL){
				pos -= 1;
				current = current->parent;
				if (!current->left == NULL){
					delete current->left;
				}
				else if (!current->right == NULL){
					delete current->right;
				}
			}
			else if (current == NULL){
				x = 1;
			}
		}
		for (int i = 1; i <= sizeof(array); i++){
			cout << array[i] << endl;
		}
		return;
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {
		Node<T>* current = this->_root;
		int x = 0;
		string path = path + to_string(current->value);
		while (x==0){
			if (!current->right == NULL){
				current = current->right;
				path = path + " " + std::to_string(current->value);
			}
			else{
				return path;
			}
		}
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T value) {
		Node<T>* current = this->_root;
		int x = 0;
		while (x == 0){
			if (current->value == value){
				return true;
			}
			else if (current->value > value){
				current = current->left;
			}
			else if (current->value < value){
				current = current->right;
			}
			else{
				return false;
			}
		}
		return numeric_limits<T>::min();
	}
};

#endif


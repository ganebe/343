#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "nodedata.h"
using namespace std;


class BinTree{
	friend ostream & operator <<(ostream &, const BinTree &);
public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	//operator overload
	BinTree& operator=(const BinTree &);
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;
	bool insert(NodeData*);
	bool retrieve(const NodeData &, NodeData* &) const;
	int getHeight(const NodeData &) const;
	void bstreeToArray(NodeData* []);
	void arrayToBSTree(NodeData* []);
	void displaySideways() const;			// provided below, displays the tree sideways

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree
	

// utility functions
    void inorderHelper(Node*) const;
    void sideways(Node*, int) const;			// provided below, helper for displaySideways()
	bool retrieveHelper(Node*, const NodeData& , NodeData*) const;
	void deleteHelper(Node* &);
};

#endif
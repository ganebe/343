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
		NodeData* data = NULL;						// pointer to data object
		Node* left = NULL;							// left subtree pointer
		Node* right = NULL;						// right subtree pointer
	};
	Node* root;								// root of the tree
	

// utility functions
    void inorderHelper(Node*, ostream&) const;
    void sideways(Node*, int) const;			// provided below, helper for displaySideways()
	bool retrieveHelper(Node*, const NodeData& , NodeData*) const;
	bool equalHelper(const Node*, const Node*)const;
	void makeEmpty();
	void makeEmptyHelper(Node*&);
	void nodeCopyHelper(Node* &,const Node* &);
	bool exist(const Node* &, const NodeData &, Node*&) const;
	int  getHeightHelper(Node* &)const;
	void bstreeToArrayHelper(Node*, NodeData* [], int&);
};

#endif
#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "nodedata.h"
using namespace std;

// ------------------------------------------------bintree.h -------------------------------------------------------
// CSS 343 B Au 23
// Created on 10/14/2023
// Last Modified on 10/21/2023
// Created by Vince Nguyen and Lok Yin Wong 
// --------------------------------------------------------------------------------------------------------------------
// This header file contains the class BinTree. The class has different methods and functions to create a tree by reading
// the values from a file. The class should be able to assign, delete, insert, retrieve, turn the array to a binary search tree,
// turn the binary search tree to an array and determine whether or not two objects are equal or not with the help from helper functions.
// --------------------------------------------------------------------------------------------------------------------
// The class should be able to display the proper tree from the file it is reading from
// --------------------------------------------------------------------------------------------------------------------

class BinTree{
	friend ostream& operator <<(ostream&, const BinTree&);  //print the tree inorder, each Nodedata is seprate with a space and ends with a endl.
public:
	//constructors
	BinTree();								//default constructor
	BinTree(BinTree&);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	//operator overload
	BinTree& operator=(const BinTree&);	
	bool operator==(const BinTree&) const;		//return true only if two trees have same data and structure, otherwise return false
	bool operator!=(const BinTree&) const;		//return true whenever there is a differnce between two trees, otherwise return true
	//functions
	bool insert(NodeData*);						//insert a Nodedata to the tree when there is no duplicate and return true,otherwise return false.
	bool retrieve(const NodeData&, NodeData* &) const;
	int getHeight(const NodeData&);			//return 0 when the given Nodedata is not found, otherwise return it's greatest height
	void bstreeToArray(NodeData* []);		//stores all Node from the current BinTree to the NodeData* array using inorder traversal, empty the current BinTree when done.
	void arrayToBSTree(NodeData* []);		//builds a balanced BinTree using the Nodes from the NodeData*array, the array will fill with nullptrs when done.
	void displaySideways() const;			//displays the tree sideways
	void makeEmpty();						//clear all nodes in the tree and release memory
	bool isEmpty() const;					// true if tree is empty, otherwise false
private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree
	

// utility functions and helper functions
    void inorderHelper(Node*, ostream&) const;	//helper for operator <<
    void sideways(Node*, int) const;			//helper for displaySideways()
	bool retrieveHelper(Node*, const NodeData&, NodeData* &) const; //helper for retrieve
	bool equalHelper(const Node*, const Node*)const; //heleper for operator ==
	void makeEmptyHelper(Node*&);				//helper for makeEmpty()
	void nodeCopyHelper(Node* &, const Node*); //helper for operator=

	//helper for getHeight(const NodeData &), to find out if the NodeData passed in actually cotains in the tree
	//it's actually very similar to retriveHelper, we created this extra fucntion since
	//we required to implement getHeight for genereal binary tree
	bool exist(Node* &, const NodeData&, Node*&) const;
	int  getHeightHelper(Node* &)const;		//helper for getHeight(const NodeData &)
	void bstreeToArrayHelper(Node*, NodeData* [], int&);	//heleper for bstreeToArray(NodeData* [])
	void arrayToBstreeHelper(int, int, NodeData* [],Node* &);	//helper for arrayToBSTree(NodeData* [])
};

#endif
#include "bintree.h"


// ------------------------------------------------bintree.cpp -------------------------------------------------------
// CSS 343 B Au 23
// Created on 10/14/2023
// Last Modified on 10/21/2023
// Created by Vince Nguyen and Lok Yin Wong 
// --------------------------------------------------------------------------------------------------------------------
// This file has the implementation of the different methods and functions from the header file. The methods and functions
// that have helper functions will be above each other to know that they are together. The class BinTree should be able to 
// to assign, delete, insert, retrieve, turn the array to a binary search tree, turn the binary search tree to an array 
// and determine whether or not two objects are equal or not with the help from helper functions.
// --------------------------------------------------------------------------------------------------------------------
// The class should be able to display the proper tree from the file it is reading from
// --------------------------------------------------------------------------------------------------------------------


//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}


//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const
{
	if (current != NULL)
	{
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

//------------------------- << overload ---------------------------------
// Displays the tree to the console
//-------------------------------------------------------------------------
ostream& operator <<(ostream& out, const BinTree& other)
{
   other.inorderHelper(other.root, out); //Inorder traversal by calling helper function
   out << endl; //adds an extra line after the whole tree is printed
   return out; //Return output
}

//------------------------- inorderHelper ---------------------------------
// Helper function to help print out the tree from inorder method
//-------------------------------------------------------------------------
void BinTree::inorderHelper(Node* node, ostream& out) const
{
	if (node == nullptr) //Checks if node is nullptr 
	{
		return;
	}
	inorderHelper(node->left, out); //Helper function call on left side of tree
	out << *(node->data) << " "; // Prints data
	inorderHelper(node->right, out); // Helper function on right side of tree
}

//------------------------- retrieve ---------------------------------
// Looks for the node in the tree using a helper function
//-------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData& current, NodeData* &checker) const
{
    checker = nullptr; // Initialize checker to nullptr

    if (root == nullptr) //Checks if tree is empty
    {
        return false;
    }

    return retrieveHelper(root, current, checker); //Helper function to look for node
}


//------------------------- retrieveHelper ---------------------------------
// Helper function that checks to see if the node is in the tree
//-------------------------------------------------------------------------
bool BinTree::retrieveHelper(Node* current, const NodeData& currData, NodeData* &checker) const
{
	if (current == nullptr) //Checks if current is nullptr
	{
		return false; 
	}

	if (currData == *(current->data)) //Compares data
	{
		checker = current->data; //Set checker to the data
		return true; 
	}
	else if (currData < *(current->data)) //If data is less
	{
		return retrieveHelper(current->left, currData, checker); // Go in the left subtree
	}
	else
	{
		return retrieveHelper(current->right, currData, checker); // Go in the right subtree
	}
}

//------------------------- Assignment operator ---------------------------------
// Sets the lhs = rhs
//-------------------------------------------------------------------------
BinTree& BinTree::operator =(const BinTree& rhs)
{
    if(this == &rhs) //Checks if lhs == rhs
	{
		return *this;
	}

	makeEmpty();
	if(rhs.root != NULL) //If root of rhs is not nullptr
	{
		root = new Node; //Create new root node
	}
	nodeCopyHelper(root, rhs.root); //Helper function to copy the nodes of rhs
	return *this; //return object
}

//------------------------- nodeCopyHelper---------------------------------
// Helper function to set the lhs = rhs
//-------------------------------------------------------------------------

void BinTree::nodeCopyHelper(Node* & current_Node, const Node* rhs){
	if(rhs == NULL) //If rhs is empty
	{
		return;
	}
	else
	{
			current_Node->data = new NodeData(*(rhs->data)); //Allocate memory and sets current data to rhs->data
			if(rhs->left != NULL) //If left node of rhs is not nullptr
			{
				current_Node->left = new Node; //Creates new node for left side of current
				nodeCopyHelper(current_Node->left, rhs->left); //Helper function to copy leftside of rhs to current
			}
			else
			{
				current_Node->left = NULL; 
			}
			if(rhs->right != NULL) //If right side of rhs is not nullptr
			{
				current_Node->right = new Node;//Creates new node for right side of current
				nodeCopyHelper(current_Node->right, rhs->right); // Helper function to copy rightside of rhs to current
			}
			else
			{
				current_Node->right = NULL;
			}
			return;
	}

}
//------------------------- bstreeToArray ---------------------------------
// Turns the bstree to an array with the help of a helper function
//-------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData *arr[])
{
	int index = 0; //Initialize index to 0
	bstreeToArrayHelper(root, arr, index); //Helper function to turn bstree to an array
	makeEmpty();
}
//------------------------- bstreeToArrayHelper ---------------------------------
// Helper function to turn the bstree to an array
//-------------------------------------------------------------------------
void BinTree::bstreeToArrayHelper(Node* node, NodeData* arr[], int& index)
{
	if (node == nullptr) //Checks if node is equal to nullptr
	{
		return;
	}
	bstreeToArrayHelper(node->left, arr, index); //Go through left side of tree
	arr[index] = node->data; //Copies data from the current node to the index of the array
	index++; //Increment index of array
	node->data = nullptr; //Set current data to nullptr
	bstreeToArrayHelper(node->right, arr, index); //Go through the right side of tree
}

//------------------------- no equality operator ---------------------------------
// Checks to see if two objects are not equal to each other
//-------------------------------------------------------------------------
bool BinTree::operator !=(const BinTree& other) const
{
    return !(*this == other); //Checks if two objects are not equal to each other
}

//------------------------- equality operator ---------------------------------
// Checks to see if two objects are equal to each other using the helper function
//-------------------------------------------------------------------------
bool BinTree::operator ==(const BinTree& other) const
{
    return equalHelper(root, other.root); //Calls helper function to check if two objects are equal
}
//------------------------- equalHelper ---------------------------------
// Helper function that comapres two objects to see if they are equal or not
//-------------------------------------------------------------------------
bool BinTree::equalHelper(const Node* current, const Node* other) const
{
   if (current == nullptr && other == nullptr) //Checks if both objects are nullptr
   {
	return true;
   }

   if (current == nullptr || other == nullptr) //Checks if one object or the other is nullptr
   {
	return false;
   }

   if(current != nullptr && other != nullptr) //If both objects do not equal nullptr
   {
	return (*current->data == *other->data) && equalHelper(current->left, other->left) && equalHelper(current->right,other->right); //Compares the data,left side of tree, and right side of tree
   }

   return false;
}

//------------------------- isEmpty ---------------------------------
// Checks to see if the tree is empty or not
//-------------------------------------------------------------------------
bool BinTree::isEmpty() const
{

    if(root == NULL) //Checks if root is nullptr
	{
        return true;
    }
	else //root is not nullptr
	{
        return false;
    }

}

//------------------------- makeEmpty ---------------------------------
// Deletes the tree with the helper function
//-------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	makeEmptyHelper(root); //Calls helper function to delete tree
	root = NULL; //Set root to nullptr
}

//------------------------- makeEmptyHelper ---------------------------------
// Helper function to delete the tree
//-------------------------------------------------------------------------
void BinTree::makeEmptyHelper(Node* & delete_node)
{
	if(delete_node == NULL) //If node is nullptr
	{
		return;
	}
	else
	{
		makeEmptyHelper(delete_node->left); //Go through left side of tree
		makeEmptyHelper(delete_node->right); //Go through right side of tree
		delete delete_node->data; //Delete the nodes data
		delete delete_node; //Delete the node
		delete_node = NULL; //Set node to nullptr
		return;
	}
}
//------------------------- Default constructor ---------------------------------
// Sets root to nullptr
//-------------------------------------------------------------------------
BinTree::BinTree()
{
    root = NULL; //Sets root to nullptr
}
//------------------------- copy constructor ---------------------------------
// Makes a deep copy of the object
//-------------------------------------------------------------------------
BinTree::BinTree(BinTree& rhs)
{
	root = NULL; //Sets root to nullptr
	*this = rhs; //Copy lhs = rhs
}
//------------------------- Destructor ---------------------------------
// Deletes the tree by calling makeEmpty function
//-------------------------------------------------------------------------
BinTree::~BinTree()
{
	makeEmpty(); //Helper function to delete tree
}
//------------------------- insert ---------------------------------
// Inserts a new node
//-------------------------------------------------------------------------
bool BinTree::insert(NodeData* input_data)
{
    if(root == NULL) //Checks if root is nullptr
	{
		Node* temp = new Node; //Create new temp node
		temp->data = new NodeData(*input_data); //Allocate memory and set temp->data to input->data
		temp->left = NULL; //Set left side of temp to nullptr
		temp->right = NULL; //Set right side of temp to nullptr
		root = temp; // Set root to temp
		delete input_data; //Delete input_data
		return true;
	}
	else
	{
		Node * current;
		Node * next;
		current = root;
		next = NULL;
		bool is_insert = false;

		while(!is_insert)
		{
			if(*current->data == *input_data) //If the data trying to insert exists
			{
				return false;
			}
			else if(*current->data > *input_data) //If current data is less than
			{
				next = current->left; //Go to left
				if(next == NULL) //If left side is nullptr
				{
					current->left = new Node; //Create new node
					current->left->data = new NodeData(*input_data); //Set the left side data to input_data
					current->left->left = NULL; //Set left of new node to nullptr
					current->left->right = NULL; //Set right of new node to nullptr
					delete input_data; //Delete data
					return true;
				}
				current = next;
			}
			else
			{
				next = current->right; //Go to right side
				if(next == NULL) //If right side is nullptr
				{
					current->right = new Node; //Create new node
					current->right->data = new NodeData(*input_data); //Set the right side data to input_data
					current->right->left = NULL; //Set left of new node to nullptr
					current->right->right = NULL; //Set right of new node to nullptr
					delete input_data; //Delete data
					return true;
				}
				current = next;
			}
		}
		
	}
	return false; 
}

//------------------------- getHeight ---------------------------------
// Gets the height of the tree at a specific node
//-------------------------------------------------------------------------
int BinTree::getHeight(const NodeData& search_target)
{
	Node * target_pointer;
	target_pointer = NULL;

	if(exist(root, search_target,target_pointer) == false){
		return 0;
	}
	else
	{
		return getHeightHelper(target_pointer);
	}

}
//------------------------- exist ---------------------------------
// 
//-------------------------------------------------------------------------
bool BinTree::exist(Node* & tree, const NodeData& search_target, Node* & target_location) const
{
	if(tree == NULL)
	{
		return false;
	}
	else
	{

		if(search_target == *(tree->data) )
		{
			target_location = tree;
			return true;
		}

		return exist(tree->left, search_target, target_location) || exist(tree->right, search_target, target_location);
	}
}
//------------------------- getHeightHelper ---------------------------------
// Helper function that calculates the height of the tree
//-------------------------------------------------------------------------
int BinTree::getHeightHelper(Node* & location)const
{
	if(location == NULL)
	{
		return 0;
	}

	if(location->left == NULL && location->right == NULL)
	{
		return 1;
	}
	else
	{
		return 1 + max(getHeightHelper(location->left), getHeightHelper(location->right) );
	}

}

//------------------------- arrayToBSTree---------------------------------
// Turns the array into a bstree using a helper function
//-------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* arr[])
{
	int arr_size = 0;
	//count number of Nodedata inside the arr
	//assuming the arr stores the noddData continuously 
	for(int i = 0; i < 100; i++)
	{
		if(arr[i] != NULL)
		{
			arr_size++;
		}
	}

	makeEmpty();

	if( (arr_size - 1) >= 0)
	{
		root = new Node;
	}

	arrayToBstreeHelper(0, arr_size - 1, arr, root);

	//clear the array after the tree is build
	for(int i = 0; i < 100; i++)
	{
		if(arr[i] != NULL)
		{
		delete arr[i];
		arr[i] = NULL;
		}
	}
}
//------------------------- arrayToBstreeHelper ---------------------------------
// Helper function to turn an array into a bstree
//-------------------------------------------------------------------------
void BinTree::arrayToBstreeHelper(int low, int high, NodeData* arr[], Node* & insert_node)
{
	if(high < low)
	{
		return;
	}
	
	if(high == low)
	{
		insert_node->data = new NodeData(*arr[high]);
		insert_node->left = NULL;
		insert_node->right = NULL;
		return;
	}
	
	int mid = (high + low)/2;
	insert_node->data = new NodeData;
	*insert_node->data = *arr[mid];

	if( (high - low) == 1 )
	{
	insert_node->right = new Node;
	arrayToBstreeHelper(high, high, arr, insert_node->right);
	insert_node->left = NULL;
	return;
	}

	insert_node->right = new Node;
	insert_node->left = new Node;
	arrayToBstreeHelper(low, mid - 1, arr, insert_node->left);
	arrayToBstreeHelper(mid + 1, high, arr, insert_node->right);
	return;
}
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
	if (current != nullptr)
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
   out << endl; 						//adds an extra line after the whole tree is printed
   return out; 							//Return output
}

//------------------------- inorderHelper ---------------------------------
// Helper function to help print out the tree from inorder method
//-------------------------------------------------------------------------

void BinTree::inorderHelper(Node* node, ostream& out) const
{
	if (node == nullptr)			 //Checks if node is nullptr 
	{
		return;
	}
	inorderHelper(node->left, out); //Helper function call on left side of tree
	out << *(node->data) << " "; 	// Prints data
	inorderHelper(node->right, out); // Helper function on right side of tree
}

//------------------------- retrieve ---------------------------------
// Looks for the node in the tree using a helper function
//-------------------------------------------------------------------------

bool BinTree::retrieve(const NodeData& current, NodeData* &checker) const
{
    checker = nullptr; 		// Initialize checker to nullptr

    if (root == nullptr) 	//Checks if tree is empty
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
	if (current == nullptr) 			//Checks if current is nullptr
	{
		return false; 
	}

	if (currData == *(current->data)) //Compares data
	{
		checker = current->data; 		//Set checker to the data
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
    if(this == &rhs) 		//Checks if lhs == rhs
	{
		return *this;
	}

	makeEmpty();
	if(rhs.root != nullptr) 	//If root of rhs is not nullptr
	{
		root = new Node; 		//Create new root node
	}
	nodeCopyHelper(root, rhs.root); //Helper function to copy the nodes of rhs
	return *this; 				//return object
}

//------------------------- nodeCopyHelper---------------------------------
// Helper function to set the lhs = rhs
//-------------------------------------------------------------------------

void BinTree::nodeCopyHelper(Node* & current_Node, const Node* rhs){
	if(rhs == nullptr) 						//If rhs is empty
	{
		return;
	}
	else
	{
			current_Node->data = new NodeData(*(rhs->data)); //Allocate memory and sets current data to rhs->data
			if(rhs->left != nullptr) 				//If left node of rhs is not nullptr
			{
				current_Node->left = new Node; 	//Creates new node for left side of current
				nodeCopyHelper(current_Node->left, rhs->left); //Helper function to copy leftside of rhs to current
			}
			else
			{
				current_Node->left = nullptr; 
			}
			if(rhs->right != nullptr) 				//If right side of rhs is not nullptr
			{
				current_Node->right = new Node;//Creates new node for right side of current
				nodeCopyHelper(current_Node->right, rhs->right); // Helper function to copy rightside of rhs to current
			}
			else
			{
				current_Node->right = nullptr;
			}
			return;
	}

}
//------------------------- bstreeToArray ---------------------------------
// Turns the bstree to an array with the help of a helper function
//-------------------------------------------------------------------------

void BinTree::bstreeToArray(NodeData *arr[])
{
	int index = 0; 							//Initialize index to 0
	bstreeToArrayHelper(root, arr, index); //Helper function to turn bstree to an array
	makeEmpty();
}
//------------------------- bstreeToArrayHelper ---------------------------------
// Helper function to turn the bstree to an array
//-------------------------------------------------------------------------

void BinTree::bstreeToArrayHelper(Node* node, NodeData* arr[], int& index)
{
	if (node == nullptr) 						//Checks if node is equal to nullptr
	{
		return;
	}

	bstreeToArrayHelper(node->left, arr, index); //Go through left side of tree
	arr[index] = node->data; 					//Copies data from the current node to the index of the array
	index++; 									//Increment index of array
	node->data = nullptr; 						//Set current data to nullptr
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
   if(current == nullptr && other == nullptr) //Checks if both objects are nullptr
   {
	return true;
   }

   if(current == nullptr || other == nullptr) //Checks if one object or the other is nullptr
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

    if(root == nullptr) //Checks if root is nullptr
	{
        return true;
    }
	else 			//root is not nullptr
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
	root = nullptr; 			//Set root to nullptr
}

//------------------------- makeEmptyHelper ---------------------------------
// Helper function to delete the tree
//-------------------------------------------------------------------------

void BinTree::makeEmptyHelper(Node* & delete_node)
{
	if(delete_node == nullptr) 				//If node is nullptr
	{
		return;
	}
	else
	{
		makeEmptyHelper(delete_node->left); //Go through left side of tree
		makeEmptyHelper(delete_node->right); //Go through right side of tree
		delete delete_node->data; 			//Delete the nodes data
		delete delete_node; 				//Delete the node
		delete_node = nullptr; 				//Set node to nullptr
		return;
	}
}

//------------------------- Default constructor ---------------------------------
// Sets root to nullptr
//-------------------------------------------------------------------------

BinTree::BinTree()
{
    root = nullptr; //Sets root to nullptr
}

//------------------------- copy constructor ---------------------------------
// Makes a deep copy of the object
//-------------------------------------------------------------------------

BinTree::BinTree(BinTree& rhs)
{
	root = nullptr; //Sets root to nullptr
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
    if(root == nullptr) //Checks if root is nullptr
	{
		Node* temp = new Node; 					//Create new temp node
		temp->data = new NodeData(*input_data); //Allocate memory and set temp->data to input->data
		temp->left = nullptr; 						//Set left side of temp to nullptr
		temp->right = nullptr; 					//Set right side of temp to nullptr
		root = temp; 							// Set root to temp
		delete input_data; 						//Delete input_data
		return true;
	}
	else
	{
		Node * current;
		Node * next;
		current = root;
		next = nullptr;
		bool is_insert = false;

		while(!is_insert)
		{
			if(*current->data == *input_data) 					//If the data trying to insert exists
			{
				return false;
			}
			else if(*current->data > *input_data) 					//If current data is less than
			{
				next = current->left; 								//Go to left
				if(next == nullptr) 									//If left side is nullptr
				{
					current->left = new Node; 						//Create new node
					current->left->data = new NodeData(*input_data); //Set the left side data to input_data
					current->left->left = nullptr; 					//Set left of new node to nullptr
					current->left->right = nullptr; 					//Set right of new node to nullptr
					delete input_data; 								//Delete data
					return true;
				}
				current = next;
			}
			else
			{
				next = current->right; 								//Go to right side
				if(next == nullptr) 									//If right side is nullptr
				{
					current->right = new Node; 						//Create new node
					current->right->data = new NodeData(*input_data); //Set the right side data to input_data
					current->right->left = nullptr; 					//Set left of new node to nullptr
					current->right->right = nullptr; 					//Set right of new node to nullptr
					delete input_data; 								//Delete data
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
	target_pointer = nullptr;

	if(exist(root, search_target,target_pointer) == false) //If the node does not exist
	{
		return 0;
	}
	else
	{
		return getHeightHelper(target_pointer); 		//Return node if it does exist
	}

}

//------------------------- exist ---------------------------------
// 
//-------------------------------------------------------------------------

bool BinTree::exist(Node* & tree, const NodeData& search_target, Node* & target_location) const
{
	if(tree == nullptr) 						//If the tree is nullptr
	{
		return false;
	}
	else
	{

		if(search_target == *(tree->data)) //If the data equals each other
		{
			target_location = tree; 		//Sets target to where node is
			return true;
		}

		return exist(tree->left, search_target, target_location) || exist(tree->right, search_target, target_location); //If not look in left tree to see if it's there or right tree
	}
}

//------------------------- getHeightHelper ---------------------------------
// Helper function that calculates the height of the tree
//-------------------------------------------------------------------------

int BinTree::getHeightHelper(Node* & location)const
{
	if(location == nullptr) 									//If node is nullptr
	{
		return 0;
	}

	if(location->left == nullptr && location->right == nullptr) //If the left and right side are both nullptr
	{
		return 1;
	}
	else
	{
		return 1 + max(getHeightHelper(location->left), getHeightHelper(location->right)); //Get max height by going left and right of tree
	}

}

//------------------------- arrayToBSTree---------------------------------
// Turns the array into a bstree using a helper function
//-------------------------------------------------------------------------

void BinTree::arrayToBSTree(NodeData* arr[])
{
	int arr_size = 0; 				//Set array size to 0
	for(int i = 0; i < 100; i++)
	{
		if(arr[i] != nullptr) 			//If the index value is not nullptr
		{
			arr_size++; 			//Increment size
		}
	}

	makeEmpty(); //Delete tree

	if((arr_size - 1) >= 0) 		//Checks if atleast 1 element exists
	{
		root = new Node;
	}

	arrayToBstreeHelper(0, arr_size - 1, arr, root); //Helper function to construct bstree

	
	for(int i = 0; i < 100; i++)	//clear the array after the tree is build
	{
		if(arr[i] != nullptr)
		{
		delete arr[i];
		arr[i] = nullptr;
		}
	}
}

//------------------------- arrayToBstreeHelper ---------------------------------
// Helper function to turn an array into a bstree
//-------------------------------------------------------------------------

void BinTree::arrayToBstreeHelper(int low, int high, NodeData* arr[], Node* & insert_node)
{
	if(high < low) 					//If no element
	{
		return;
	}
	
	if(high == low) 				//If an element exists add a node
	{
		insert_node->data = new NodeData(*arr[high]);
		insert_node->left = nullptr;
		insert_node->right = nullptr;
		return;
	}
	
	int mid = (high + low)/2; 		//Calculate middle index
	insert_node->data = new NodeData;
	*insert_node->data = *arr[mid]; //Allocate memory to set insert_data->data to the array value in the middle

	if((high - low) == 1) 			//If there are only two elements
	{
		insert_node->right = new Node; //Create new node for right side
		arrayToBstreeHelper(high, high, arr, insert_node->right); //Add to the right side of the tree
		insert_node->left = nullptr; 	//Set leftside to nullptr
		return;
	}

	insert_node->right = new Node; //New node for right side of tree
	insert_node->left = new Node; //New node for left side of tree
	arrayToBstreeHelper(low, mid - 1, arr, insert_node->left); //Inserts left half of the array
	arrayToBstreeHelper(mid + 1, high, arr, insert_node->right); //Inserts right half of the array
	return;
}
#include "bintree.h"

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}


bool BinTree::retrieve(const NodeData &current, NodeData *&checker) const
{
    return retrieveHelper(root, current, checker);
}

bool BinTree::retrieveHelper(Node *node, const NodeData &current, NodeData *checker) const
{
    if (node == nullptr)
	{
		checker = nullptr;
		return false;
	}

	if (current== *(node->data))
	{
		checker = node->data;
		return true;
	}

	if (current < *(node->data))
	{
		return retrieveHelper(node->left, current, checker);

	}
	if(current > *(node->data))
	{
	 retrieveHelper(node->right, current, checker);
	}
}


#include "bintree.h"

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const{
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const{
	if (current != NULL){
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--){
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


bool BinTree::isEmpty() const{
    if(root == NULL){
        return true;
    }else{
        return false;
    }
}

BinTree::BinTree(){
    root = NULL;
}

bool BinTree::insert(NodeData * input_data){
    if(root == NULL){
		Node* temp = new Node;
		temp->data = new NodeData(*input_data);
		temp->left = NULL;
		temp->right = NULL;
		root = temp;
		return true;
	}else{
		Node * current;
		Node * next;
		current = root;
		next = NULL;
		bool is_insert = false;
		while(!is_insert){
			if(*current->data == *input_data){
				return false;
			}else if(*current->data < *input_data){
				next = current->left;
				if(next == NULL){
					current->left = new Node;
					current->left->data = new NodeData(*input_data);
					current->left->left = NULL;
					current->left->right = NULL;
					return true;
				}
				current = next;
			}else{
				next = current->right;
				if(next == NULL){
					current->right = new Node;
					current->right->data = new NodeData(*input_data);
					current->right->left = NULL;
					current->right->right = NULL;
					return true;
				}
				current = next;
			}
		}
		
	}

	return false; //something went wrong if this line get excute
}

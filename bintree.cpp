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

ostream &operator<<(ostream &out, const BinTree &other)
{
   other.inorderHelper(other.root, out);
   return out;
}

void BinTree::inorderHelper(Node *node, ostream& out) const
{
	if (node == nullptr)
	{
		return;
	}
	inorderHelper(node->left, out);
	cout << *(node->data);
	inorderHelper(node->right, out);
}

bool BinTree::retrieve(const NodeData &current, NodeData *&checker) const
{
    if(root != nullptr)
	{
		retrieveHelper(root, current, checker);
		if(checker != nullptr)
		{
			if (*checker == current)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}



bool BinTree::retrieveHelper(Node *node, const NodeData &current, NodeData *checker) const
{
    if (node == nullptr)
	{
		checker = nullptr;
	}

	if (current == *(node->data))
	{
		checker = node->data;
	}

	if (current < *(node->data))
	{
		retrieveHelper(node->left, current, checker);
	}
	if(current > *(node->data))
	{
	 	retrieveHelper(node->right, current, checker);
	}
}

BinTree &BinTree::operator=(const BinTree & rhs)
{
    if(*this == rhs){
		return *this;
	}
	makeEmpty();
	nodeCopyHelper(root,rhs.root);
	return *this;	
}

void BinTree::nodeCopyHelper(Node* & current_Node,const Node* & rhs){
	if(rhs == NULL){
		return;
	}else{
		if(current_Node == NULL){  //create a new node if it is root;
			current_Node = new Node;
		}
			current_Node->data = new NodeData(rhs->data);
			if(rhs->left == NULL && rhs->left == NULL){
				return;
			}
			if(rhs->left != NULL){
				current_Node->left = new Node;
				nodeCopyHelper(current_Node->left, rhs->left);
			}
			if(rhs->right != NULL){
				current_Node->right = new Node;
				nodeCopyHelper(current_Node->right, rhs->right);
			}
	}

	return;
}

void BinTree::bstreeToArray(NodeData *arr[])
{
	int index = 0;
	bstreeToArrayHelper(root, arr, index);
	makeEmpty();
}

void BinTree::bstreeToArrayHelper(Node * node, NodeData *arr[], int& index)
{
	if (node == nullptr)
	{
		return;
	}
	bstreeToArrayHelper(node->left, arr, index);
	arr[index] = new NodeData(*(node->data));
	index++;
	bstreeToArrayHelper(node->right, arr, index);
}

bool BinTree::operator==(const BinTree &other) const
{
    return equalHelper(root, other.root);
}

bool BinTree::operator!=(const BinTree &other) const
{
    return !(*this == other);
}

bool BinTree::equalHelper(const Node *current, const Node *other) const
{
   if (current == nullptr && other == nullptr)
   {
	return true;
   }

   if (current == nullptr || other == nullptr)
   {
	return false;
   }

   if(current != nullptr && other != nullptr)
   {
	return (*current->data == *other->data) && equalHelper(current->left, other->left) && equalHelper(current->right,other->right);
   }

   return false;
}


bool BinTree::isEmpty() const
{
    if(root == NULL){
        return true;
    }else{
        return false;
    }
}

void BinTree::makeEmpty()
{
	makeEmptyHelper(root);
}

void BinTree::makeEmptyHelper(Node *& delete_node)
{
	if(delete_node == NULL){
		return;
	}else{
		makeEmptyHelper(delete_node->left);
		makeEmptyHelper(delete_node->right);
		delete delete_node->data;
		delete delete_node;
		delete_node = NULL;
		return;
	}
}

BinTree::BinTree()
{
    root = NULL;
}

BinTree::BinTree(const BinTree & rhs)
{
	*this = rhs;
}

BinTree::~BinTree()
{
	makeEmpty();
}

bool BinTree::insert(NodeData *input_data)
{
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
			}else if(*current->data > *input_data){
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


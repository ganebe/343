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
   out << endl;
   return out;
}

void BinTree::inorderHelper(Node *node, ostream& out) const
{
	if (node == nullptr)
	{
		return;
	}
	inorderHelper(node->left, out);
	out << *(node->data) << " ";
	inorderHelper(node->right, out);
}

bool BinTree::retrieve(const NodeData &current, NodeData *&checker) const
{
    checker = nullptr; // Initialize check to nullptr

    if (root == nullptr) // Tree is empty
    {
        return false;
    }

    return retrieveHelper(root, current, checker);
}



bool BinTree::retrieveHelper(Node *current, const NodeData &currData, NodeData *checker) const
{
	if (current == nullptr)
	{
		return false; // Data not found
	}

	if (currData == *(current->data))
	{
		checker = current->data;
		return true; // Data found
	}
	else if (currData < *(current->data))
	{
		return retrieveHelper(current->left, currData, checker); // Search in the left subtree
	}
	else
	{
		return retrieveHelper(current->right, currData, checker); // Search in the right subtree
	}
}

BinTree &BinTree::operator =(const BinTree & rhs)
{
    if(this == &rhs){
		return *this;
	}

	makeEmpty();
	if(rhs.root != NULL){
		root = new Node;
	}
	nodeCopyHelper(root, rhs.root);
	return *this;	
}

void BinTree::nodeCopyHelper(Node* & current_Node, const Node* rhs){
	if(rhs == NULL){
		return;
	}else{
			current_Node->data = new NodeData(*(rhs->data));
			if(rhs->left != NULL){
				current_Node->left = new Node;
				nodeCopyHelper(current_Node->left, rhs->left);
			}else{
				current_Node->left = NULL;
			}
			if(rhs->right != NULL){
				current_Node->right = new Node;
				nodeCopyHelper(current_Node->right, rhs->right);
			}else{
				current_Node->right = NULL;
			}
			return;
	}

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
	arr[index] = node->data;
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
	root = NULL;
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

BinTree::BinTree( BinTree & rhs)
{
	root = NULL;
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


int BinTree::getHeight(const NodeData & search_target){
	Node * target_pointer;
	target_pointer = NULL;
	if(exist(root, search_target,target_pointer) == false){
		return 0;
	}else{
		return getHeightHelper(target_pointer);
	}
}

bool BinTree::exist( Node* & tree, const NodeData & search_target, Node* & target_location) const{
	if(tree == NULL){
		return false;
	}else{
		if(search_target == *(tree->data) ){
			target_location = tree;
			return true;
		}

		return exist(tree->left, search_target, target_location) || exist(tree->right, search_target, target_location);
	}
}

int BinTree::getHeightHelper(Node* & location)const{
	if(location == NULL){
		return 0;
	}
	if(location->left == NULL && location->right == NULL){
		return 1;
	}else{
		return 1 + max( getHeightHelper(location->left), getHeightHelper(location->right) );
	}
}


void BinTree::arrayToBSTree(NodeData* arr[]){
	int arr_size = 0;
	for(int i = 0; i < 100; i++){
		if(arr[i] != NULL){
			arr_size++;
		}
	}
	makeEmpty();
	if( (arr_size - 1) >= 0){
		root = new Node;
	}
	root = NULL;
	arrayToBstreeHelper(0, arr_size - 1, arr, root);
}

void BinTree::arrayToBstreeHelper(int low, int high, NodeData* arr[], Node* & insert_node){
	if(high > low){
		return;
	}
	if(high == low){
		insert_node->data = new NodeData(*arr[high]);
		return;
	}
	int mid = (high + low)/2;
	insert_node->data = new NodeData(*arr[mid]);
	if( (high - low) == 1 ){
		insert_node->right = new Node;
		arrayToBstreeHelper(high, high, arr, insert_node->right);
	}
	insert_node->right = new Node;
	insert_node->left = new Node;
	arrayToBstreeHelper(low, mid - 1, arr, insert_node->left);
	arrayToBstreeHelper(mid + 1, high, arr, insert_node->right);
	return;
}
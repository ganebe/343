#include "nodedata.h"
#include "bintree.h"
#include "iostream"
#include "string"

using namespace std;

void initArray(NodeData*[]);             

const int ARRAYSIZE = 100;


int main(){

    NodeData ndA("a");
    NodeData ndAB("ab");
    NodeData ndAC("ac");
    BinTree  A,B;
    bool is_equal = A==B;
    if(is_equal == true){
        cout << "A:" << endl;
        A.displaySideways();
        cout << "B:" << endl;
        B.displaySideways();
        cout << " A == B";
    }
    return 0;
}

void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = nullptr;
}

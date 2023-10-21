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
    BinTree  A;
    A.insert(&ndA);
    A.insert(&ndAB);
    A.insert(&ndAC);
    A.displaySideways();
    cout << A << endl;
    NodeData* ndArray[ARRAYSIZE];
    initArray(ndArray);
    A.bstreeToArray(ndArray);
    A.arrayToBSTree(ndArray);
    A.displaySideways();
    cout << A << endl;
    cout << "after array to bstree and bstree to array" << endl;
    cout << "chagne A to B, ab to bb ac to cc" << endl;
    ndA = ndAB;
    ndAB = ndAB;
    ndAC = ndAB;
    A.displaySideways();
    cout << A << endl; 
    cout << ndA << ndAB << ndAC << endl;
    BinTree C(A);
    for(int i = 0 ; i < 2 ; i++){
        NodeData g("g");
        C.insert(&g);
    }
    /*
    NodeData* nde;
    nde = new NodeData("e");
    cout << "comparing c and a" <<endl;
    C.insert(nde);
    A.displaySideways();
    cout << A << endl; 
    C.displaySideways();
    cout << C << endl;
    
    delete nde;
    cout << "after deleting nde pointer" << endl;
    C.displaySideways();
    cout << C << endl;
    */
    return 0;
}

void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}

#include "bintree.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
NodeData *n = new NodeData;
n->setData("hello");
BinTree A;

A.insert(n);

A.displaySideways();
}

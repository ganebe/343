#include "bintree.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
NodeData *n = new NodeData;
ifstream file;
file.open("data2.txt");
n->setData(file);
BinTree A;

A.insert(n);

A.displaySideways();
}

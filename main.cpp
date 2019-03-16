#include <iostream>
#include <cstdlib>
#include "Tree.hpp"
using namespace std;


int main() {
    int TreeData[16] = { 50,76,21,1,32,64,15,52,14,100,83,2,3,70,87,80 };
    BTree* myTree;
    myTree = new BTree();
    cout<< "Printing tree"<<endl;
    myTree->printInOrder();
    for(int i =0 ;i<16 ; i++){
        myTree->Add_Num(TreeData[i]);
    }
    myTree->Add_Num(5);
    myTree->Add_Num(4);
    myTree->Add_Num(6);
    cout<< "Printing tree in order"<<endl;
    myTree->printInOrder();
    cout<<"\nParent\n";
    myTree->parent(5);
    cout<<myTree->parent(5)->data;
    cout<<"\nleft\n";
    cout<<myTree->left(5);
    cout<<"\nright\n";
    cout<<myTree->right(5);
    cout<<"\nSmalletst : "<<myTree->Smallest()<<"\n";
    myTree->remove(1);
    cout<<"\nSmalletst : "<<myTree->Smallest();
    return 0;
}
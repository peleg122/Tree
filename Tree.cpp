//
// Created by Peleg on 15/03/2019.
//

#include <iostream>
#include <cstdlib>
#include "Tree.hpp"
using namespace std;



BTree::BTree() {
    root_node = NULL;
}
BTree::~BTree() {
    removeRoot(root_node);
}
void BTree::removeRoot(TreeNode* node) {
    if(node != NULL){
        if(node->child_left != NULL){
            removeRoot(node->child_left);
        }if(node->child_right != NULL){
            removeRoot(node->child_right);
        }
        delete node;
    }
}

BTree::TreeNode* BTree::Create_Node(int data){
    TreeNode* node = new TreeNode;
    node->data = data;
    node->child_left= NULL;
    node->child_right = NULL;
    counter++;

    return node;
}
void BTree::insert(int data) {
    insertPrivate(root_node, data);

}
void BTree::insertPrivate(TreeNode* node, int data) {
    if(root_node == NULL){
        root_node = Create_Node(data);
    }
    else if(node->data > data){
        if(node->child_left != NULL){
            insertPrivate(node->child_left, data);
        } else{
            node->child_left= Create_Node(data);
        }
    }else if(node->data < data){
        if(node->child_right != NULL){
            insertPrivate(node->child_right, data);
        } else{
            node->child_right= Create_Node(data);
        }
    }else{
        cout<<"the key " <<data<< " is alread in the tree!"<<endl;
    }
}
void BTree::print() {
    printInOrderPrivate(root_node);
}
void BTree::printInOrderPrivate(TreeNode* node) {
    if(root_node != NULL){
        if(node->child_left != NULL){
            printInOrderPrivate(node->child_left);
        }
        cout<< node->data <<" ";
        if(node->child_right != NULL){
            printInOrderPrivate(node->child_right);
        }
    } else{
        cout<<"Empty Tree"<<endl;
    }
}
BTree::TreeNode* BTree::parentChild(int data) {
    return parentPrivate(root_node,data);
}
BTree::TreeNode* BTree::target(TreeNode *node, int data) {
    TreeNode* temp = NULL;
    while(node!= NULL){
        if(data <node->data){
            temp = node;
            node = node->child_left;
        }else if( data > node->data){
            temp = node;
            node = node->child_right;
        }else{
            return temp;
        }
    }
}
int BTree::parent(int data){
    if(target(root_node, data) != NULL){
        return target(root_node, data)->data;
    }else{
        return -1;
    }

}


BTree::TreeNode* BTree::parentPrivate(TreeNode* node, int data) {
    if(node != NULL) {
        if (node->data == data) {
            return node;
        } else {
            if (node->data > data) {
                return parentPrivate(node->child_left, data);
            } else {
                return parentPrivate(node->child_right, data);
            }
        }
    }else{
        return NULL;
    }
}
int BTree::left(int data) {
    return leftPrivate(parentChild(data) , data);
}

int BTree::leftPrivate(BTree::TreeNode *node, int data) {
    if(node!= NULL){
        if(node->child_left!= NULL){
            return node->child_left == NULL ? -1 : node->child_left->data;
        } else{
            return -1;
        }
    }else{
        cout<<"Left Child Missing"<<endl;
    }
}
int BTree::right(int data) {
    return rightPrivate(parentChild(data) , data);
}

int BTree::rightPrivate(BTree::TreeNode *node, int data) {
    if(node!= NULL){
        if(node->child_right!= NULL){
            return node->child_right == NULL ? -1 : node->child_right->data;
        } else{
            return -1;
        }
    }else{
        cout<<"Right Child Missing"<<endl;
    }
}

void BTree::remove(int data){
    cout<<"Removing numer : " << data<< "...";
    removePrivate(root_node, data);
}
void BTree::removePrivate(TreeNode* node, int data){
   if(root_node != NULL){
       if(root_node->data == data){
           removeRootData();
       }else{
           if(node->data > data && node->child_left != NULL){
               node->child_left->data == data ?
               removeData(node, node->child_left, true) :
               removePrivate(node->child_left, data);
           }else if(node->data < data && node->child_right != NULL){
               node->child_right->data == data ?
               removeData(node, node->child_right, false) :
               removePrivate(node->child_right, data);
           }else{
               cout<<data << "not in the tree";
           }
       }
   }else{
       cout<< "Empty Tree!"<<endl;
   }
}
void BTree::removeRootData() {
    if(root_node != NULL){
        TreeNode* delNode = root_node;
        int rootData = root_node->data;
        int smallestDataOnRight;

        //case 1 - 0 children
        if(root_node->child_left == NULL && root_node->child_right ==NULL){
            root_node = NULL;
            counter--;
            delete delNode;
        } // case 2 - 1 child;
        else if(root_node->child_left == NULL && root_node->child_right != NULL){
            root_node = root_node->child_right;
            delNode->child_right = NULL;
            counter--;
            delete delNode;
        }else if(root_node->child_right == NULL && root_node->child_left != NULL){
            root_node = root_node->child_left;
            delNode->child_left = NULL;
            counter--;
            delete delNode;
        }// case 3 - 2 children
        else{
            smallestDataOnRight = SmallestPrivate(root_node->child_right);
            removePrivate(root_node, smallestDataOnRight);
            root_node->data=smallestDataOnRight;
        }
    }else{
        cout<< "Tree root is empty"<< endl;
    }
}

void BTree::removeData(TreeNode *node, TreeNode *removeNode, bool left) {
    if(root_node != NULL){
        TreeNode* delNode;
        int remData = removeNode->data;
        int smallestInRight;
        if(removeNode->child_left == NULL && removeNode->child_right == NULL){
            delNode = removeNode;
            left == true ? node->child_left = NULL :
                    node->child_right = NULL;
            counter--;
            delete delNode;
        }else if(removeNode->child_left == NULL && removeNode->child_right != NULL){
            left == true ? node->child_left = removeNode->child_right :
                    node->child_right = removeNode->child_right;
            removeNode->child_right = NULL;
            delNode = removeNode;
            counter--;
            delete delNode;
        }else if(removeNode->child_left != NULL && removeNode->child_right == NULL){
            left == true ? node->child_left = removeNode->child_left :
                    node->child_right = removeNode->child_left;
            removeNode->child_left = NULL;
            delNode = removeNode;
            counter--;
            delete delNode;
        }else{
            smallestInRight = SmallestPrivate(removeNode->child_right);
            removePrivate(removeNode , smallestInRight);
            removeNode->data = smallestInRight;
        }
    }
}
int BTree::Smallest() {
    return SmallestPrivate(root_node);
}
int BTree::SmallestPrivate(TreeNode* node) {
    if(root_node == NULL){
        cout<<"Empty Tree!"<<endl;
        return -1;
    }else{
        if(node->child_left != NULL){
            return SmallestPrivate(node->child_left);
        }else{
            return node->data;
        }
    }
}
int BTree::size(){
    return sizePrivate();
}
int BTree::sizePrivate(){
    /*if(node !=NULL){
        if(node->child_left != NULL){
            sizePrivate(node->child_left);
        }if(node->child_right != NULL){
            sizePrivate(node->child_right);
        }
        counter++;
    }*/
    return counter;
}
bool BTree::contains(int data){
    return containsPrivate(root_node, data);
}
bool BTree::containsPrivate(TreeNode* node, int data) {
    if(node !=NULL){
        if(node->data== data){
            return true;
        }else if(node->data > data){
            containsPrivate(node->child_left, data);
        }else if(node->data < data){
            containsPrivate(node->child_right, data);
        }
    }else{
        return false;
    }
}

int BTree::root() {
    return rootPrivate();
}
int BTree::rootPrivate() {
    if(root_node != NULL) {
        return root_node->data;
    }else{
        return -1;
    }
}
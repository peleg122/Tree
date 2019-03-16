//
// Created by Peleg on 15/03/2019.
//

#include <iostream>
#include <cstdlib>
#include "Tree.hpp"
using namespace std;



BTree::BTree() {
    root = NULL;
}
BTree::~BTree() {
    if(root!=NULL){
        //remove(root->child_left);
        //remove(root->child_right);
        delete root;
    }
}

BTree::TreeNode* BTree::Create_Node(int data){
    TreeNode* node = new TreeNode;
    node->data = data;
    node->child_left= NULL;
    node->child_right = NULL;

    return node;
}
void BTree::Add_Num(int data) {
    Add_Num_Private(root, data);
}
void BTree::Add_Num_Private(TreeNode* node, int data) {
    if(root == NULL){
        root = Create_Node(data);
    }
    else if(node->data > data){
        if(node->child_left != NULL){
            Add_Num_Private(node->child_left, data);
        } else{
            node->child_left= Create_Node(data);
        }
    }else if(node->data < data){
        if(node->child_right != NULL){
            Add_Num_Private(node->child_right, data);
        } else{
            node->child_right= Create_Node(data);
        }
    }else{
        cout<<"the key " <<data<< " is alread in the tree!"<<endl;
    }
}
void BTree::printInOrder() {
    printInOrderPrivate(root);
}
void BTree::printInOrderPrivate(TreeNode* node) {
    if(root != NULL){
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
BTree::TreeNode* BTree::parent(int data) {
    return parentPrivate(root,data);
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
    return leftPrivate(parent(data) , data);
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
    return rightPrivate(parent(data) , data);
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
    removePrivate(root, data);
}
void BTree::removePrivate(TreeNode* node, int data){
   if(root != NULL){
       if(root->data == data){
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
    if(root != NULL){
        TreeNode* delNode = root;
        int rootData = root->data;
        int smallestDataOnRight;

        //case 1 - 0 children
        if(root->child_left == NULL && root->child_right ==NULL){
            root = NULL;
            delete delNode;
        } // case 2 - 1 child;
        else if(root->child_left == NULL && root->child_right != NULL){
            root = root->child_right;
            delNode->child_right = NULL;
            delete delNode;
        }else if(root->child_right == NULL && root->child_left != NULL){
            root = root->child_left;
            delNode->child_left = NULL;
            delete delNode;
        }// case 3 - 2 children
        else{
            smallestDataOnRight = SmallestPrivate(root->child_right);
            removePrivate(root, smallestDataOnRight);
            root->data=smallestDataOnRight;
        }
    }else{
        cout<< "Tree root is empty"<< endl;
    }
}
/*void BTree::removeData(TreeNode* node, TreeNode* removeNode, bool left){
    if(root !=NULL){
        TreeNode* delNode;
        int remData = removeNode->data;
        int smallestOnRight;
        if(removeNode->child_left == NULL && removeNode->child_right != NULL){
            delNode = removeNode;
            left == true ? node->child_left = NULL : node->child_right = NULL;
            delete delNode;
        }else if(removeNode->child_left == NULL && removeNode->child_right != NULL){
            left == true ? node->child_left = removeNode->child_right : node->child_right = removeNode->child_right;
            removeNode->child_right = NULL;
            delNode = removeNode;
            delete delNode;
        }else if(removeNode->child_right == NULL && removeNode->child_left != NULL){
            left == true ? node->child_left = removeNode->child_left : node->child_right = removeNode->child_left;
            removeNode->child_left = NULL;
            delNode = removeNode;
            delete delNode;
        }else {
            smallestOnRight =SmallestPrivate(removeNode->child_right);
            removePrivate(removeNode ,smallestOnRight);
            removeNode->data = smallestOnRight;
        }
    }else{
        cout<< "Tree is empty!"<<endl;
    }
}*/
void BTree::removeData(TreeNode *node, TreeNode *removeNode, bool left) {
    if(root != NULL){
        TreeNode* delNode;
        int remData = removeNode->data;
        int smallestInRight;
        if(removeNode->child_left == NULL && removeNode->child_right == NULL){
            delNode = removeNode;
            left == true ? node->child_left = NULL :
                    node->child_right = NULL;
            delete delNode;
        }else if(removeNode->child_left == NULL && removeNode->child_right != NULL){
            left == true ? node->child_left = removeNode->child_right :
                    node->child_right = removeNode->child_right;
            removeNode->child_right = NULL;
            delNode = removeNode;
            delete delNode;
        }else if(removeNode->child_left != NULL && removeNode->child_right == NULL){
            left == true ? node->child_left = removeNode->child_left :
                    node->child_right = removeNode->child_left;
            removeNode->child_left = NULL;
            delNode = removeNode;
            delete delNode;
        }else{
            smallestInRight = SmallestPrivate(removeNode->child_right);
            removePrivate(removeNode , smallestInRight);
            removeNode->data = smallestInRight;
        }
    }
}
int BTree::Smallest() {
    return SmallestPrivate(root);
}
int BTree::SmallestPrivate(TreeNode* node) {
    if(root == NULL){
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
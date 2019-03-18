//
// Created by Peleg on 15/03/2019.
//

#include <iostream>
#include <cstdlib>
#include "Tree.hpp"
using namespace std;
using namespace ariel;



Tree::Tree() {
    root_node = NULL;
}
Tree::~Tree() {
    removeRoot(root_node);
}
void Tree::removeRoot(TreeNode* node) {
    if(node != NULL){
        if(node->child_left != NULL){
            removeRoot(node->child_left);
        }if(node->child_right != NULL){
            removeRoot(node->child_right);
        }
        delete node;
    }
}

Tree::TreeNode* Tree::Create_Node(int data){
    TreeNode* node = new TreeNode;
    node->data = data;
    node->child_left= NULL;
    node->child_right = NULL;
    counter++;

    return node;
}
void Tree::insert(int data) {
    insertPrivate(root_node, data);

}
void Tree::insertPrivate(TreeNode* node, int data) {
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
        throw std::invalid_argument( "Data Found already!" );
        cout<<"the data " <<data<< " is alread in the tree!"<<endl;
    }
}
void Tree::print() {
    printInOrderPrivate(root_node);
}
void Tree::printInOrderPrivate(TreeNode* node) {
    if(root_node != NULL){
        if(node->child_left != NULL){
            printInOrderPrivate(node->child_left);
        }
        cout<< node->data <<" ";
        if(node->child_right != NULL){
            printInOrderPrivate(node->child_right);
        }
    } else{
        throw std::invalid_argument( "Empty Tree" );
        cout<<"Empty Tree"<<endl;
    }
}
Tree::TreeNode* Tree::parentChild(int data) {
    return parentPrivate(root_node,data);
}
Tree::TreeNode* Tree::target(TreeNode *node, int data) {
    TreeNode* temp = NULL;
    while(node!= NULL){
        if(data <node->data){
            temp = node;
            node = node->child_left;
        }else if( data > node->data){
            temp = node;
            node = node->child_right;
        }else{
            throw std::invalid_argument( "No Parent!" );
            return temp;
        }
    }
}
int Tree::parent(int data){
    if(target(root_node, data) != NULL){
        return target(root_node, data)->data;
    }else{
        throw std::invalid_argument( "No Parent!" );
        return -1;
    }

}


Tree::TreeNode* Tree::parentPrivate(TreeNode* node, int data) {
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
        throw std::invalid_argument( "No Parent!" );
        return NULL;
    }
}
int Tree::left(int data) {
    return leftPrivate(parentChild(data) , data);
}

int Tree::leftPrivate(TreeNode *node, int data) {
    if(node!= NULL){
        if(node->child_left!= NULL){
            return node->child_left == NULL ? throw std::invalid_argument( "Left Child missing" ) : node->child_left->data;
        } else{
            throw std::invalid_argument( "Left Child missing" );
        }
    }else{
        throw std::invalid_argument( "Left Child missing" );
    }
}
int Tree::right(int data) {
    return rightPrivate(parentChild(data) , data);
}

int Tree::rightPrivate(TreeNode *node, int data) {
    if(node!= NULL){
        if(node->child_right!= NULL){
            return node->child_right == NULL ? throw std::invalid_argument( "Right Child missing" ) : node->child_right->data;
        } else{
            std::invalid_argument( "Right Child missing" );
            //return -1;
        }
    }else{
        throw std::invalid_argument( "Right child missing" );
    }
}

void Tree::remove(int data){
    cout<<"Removing numer : " << data<< "...";
    removePrivate(root_node, data);
}
void Tree::removePrivate(TreeNode* node, int data){
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
               throw std::invalid_argument( "Not in Tree" );
           }
       }
   }else{
       throw std::invalid_argument( "Tree is Empty" );
   }
}
void Tree::removeRootData() {
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
        throw std::invalid_argument( "Tree Root Missing" );
    }
}

void Tree::removeData(TreeNode *node, TreeNode *removeNode, bool left) {
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
int Tree::Smallest() {
    return SmallestPrivate(root_node);
}
int Tree::SmallestPrivate(TreeNode* node) {
    if(root_node == NULL){
        throw std::invalid_argument( "Empty Tree!" );
        return -1;
    }else{
        if(node->child_left != NULL){
            return SmallestPrivate(node->child_left);
        }else{
            return node->data;
        }
    }
}
int Tree::size(){
    return sizePrivate();
}
int Tree::sizePrivate(){
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
bool Tree::contains(int data){
    return containsPrivate(root_node, data);
}
bool Tree::containsPrivate(TreeNode* node, int data) {
    if(node !=NULL){
        if(node->data== data){
            return true;
        }else if(node->data > data){
            containsPrivate(node->child_left, data);
        }else if(node->data < data){
            containsPrivate(node->child_right, data);
        }
    }else{
        throw std::invalid_argument( "Not Contains!" );
        return false;
    }
}

int Tree::root() {
    return rootPrivate();
}
int Tree::rootPrivate() {
    if(root_node != NULL) {
        return root_node->data;
    }else{
        throw std::invalid_argument( "No Root!" );
        return -1;
    }
}

//
// Created by Peleg on 16/03/2019.
//

#ifndef TRY1_TREE_H
#define TRY1_TREE_H

#endif //TRY1_TREE_H
//
// Created by Peleg on 15/03/2019.
//

class BTree{
private:
    struct TreeNode{
        int data;
        TreeNode* child_left;
        TreeNode* child_right;
    };
    TreeNode* root;
    void Add_Num_Private(TreeNode* node ,int data);
    void printInOrderPrivate(TreeNode* node);
    TreeNode* parentPrivate(TreeNode* node ,int data);
    int leftPrivate(TreeNode* node, int data);
    int rightPrivate(TreeNode* node, int data);
    void removePrivate(TreeNode* node, int data);
    void removeRootData();
    void removeData(TreeNode* node, TreeNode* removeNode, bool left);
    int SmallestPrivate(TreeNode* node);
public:
    BTree();
    ~BTree();
    TreeNode* Create_Node(int data);
    void Add_Num(int data);
    void printInOrder();
    TreeNode* parent(int data);
    int left(int data);
    int right(int data);
    void remove(int data);
    int Smallest();

};

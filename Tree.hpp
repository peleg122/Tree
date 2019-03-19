//
// Created by Peleg on 16/03/2019.
//

#ifndef TRY1_TREE_H
#define TRY1_TREE_H

#endif //TRY1_TREE_H
//
// Created by Peleg on 15/03/2019.
//
namespace ariel{
    class Tree{
    private:
        int counter = 0;
        struct TreeNode{
            int data;
            TreeNode* child_left;
            TreeNode* child_right;
        };
        TreeNode* root_node;
        void insertPrivate(TreeNode* node ,int data);
        void printInOrderPrivate(TreeNode* node);
        TreeNode* parentPrivate(TreeNode* node ,int data);
        int leftPrivate(TreeNode* node, int data);
        int rightPrivate(TreeNode* node, int data);
        void removePrivate(TreeNode* node, int data);
        void removeRootData();
        void removeData(TreeNode* node, TreeNode* removeNode, bool left);
        int SmallestPrivate(TreeNode* node);
        void removeRoot(TreeNode* node);
        int sizePrivate();
        TreeNode* target(TreeNode* node, int data);
        bool containsPrivate(TreeNode* node,int data);
        int rootPrivate();
    public:
        Tree();
        ~Tree();
        TreeNode* Create_Node(int data);
        void insert(int data);
        void print();
        TreeNode* parentChild(int data);
        int parent(int data);
        int left(int data);
        int right(int data);
        void remove(int data);
        int Smallest();
        int size();
        bool contains(int data);
        int root();

    };
};

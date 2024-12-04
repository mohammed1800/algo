#include <iostream>  

using namespace std; 

struct TreeNode { 

    int value; 

    TreeNode* left; 

    TreeNode* right; 

    TreeNode(int val) { 

        value = val; 

        left = nullptr; 

        right = nullptr; 

    } 

}; 

class BinaryTree { 

public: 

    TreeNode* root; 

 

    BinaryTree() { 

        root = nullptr; 

    } 

 

 

    void insert(int value); 

    TreeNode* insertRecursive(TreeNode* node, int value); 

 

    bool search(int value); 

    bool searchRecursive(TreeNode* node, int value); 

}; 

void BinaryTree::insert(int value) { 

    root = insertRecursive(root, value); 

} 

 

TreeNode* BinaryTree::insertRecursive(TreeNode* node, int value) { 

 

    if (node == nullptr) { 

        return new TreeNode(value); 

    } 

 

   

    if (value < node->value) { 

        node->left = insertRecursive(node->left, value); 

    } else { 

        node->right = insertRecursive(node->right, value); 

    } 

    return node; 

} 

bool BinaryTree::search(int value) { 

    return searchRecursive(root, value); 

} 

bool BinaryTree::searchRecursive(TreeNode* node, int value) { 

  

    if (node == nullptr) { 

        return false; 

    } 

 

    if (node->value == value) { 

        return true; 

    } 

    if (value < node->value) { 

        return searchRecursive(node->left, value); 

    } else { 

        return searchRecursive(node->right, value); 

    } 

} 

 

int main() { 

    BinaryTree tree; 

    tree.insert(50); 

    tree.insert(30); 

    tree.insert(20); 

    tree.insert(40); 

    tree.insert(70); 

    tree.insert(60); 

    tree.insert(80); 

    int searchKey = 40; 

    if (tree.search(searchKey)) { 

        cout << "Found key " << searchKey << " in the tree." << endl; 

    } else { 

        cout << "Key " << searchKey << " not found in the tree." << endl; 

    } 

 

    searchKey = 90; 

    if (tree.search(searchKey)) { 

        cout << "Found key " << searchKey << " in the tree." << endl; 

    } else { 

        cout << "Key " << searchKey << " not found in the tree." << endl; 

    } 

 

    return 0; 

} 
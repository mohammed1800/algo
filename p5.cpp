#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BTreeNode {
public:
    vector<int> keys;  // Store keys
    vector<BTreeNode*> children;  // Store child pointers
    bool leaf;  // True if leaf node
    int t;  // Minimum degree (defines the range for number of keys)
    
    // Constructor to create a node
    BTreeNode(int t, bool leaf);
    
    // Function to insert a new key in this node
    void insertNonFull(int key);
    
    // Function to split a child node
    void splitChild(int i, BTreeNode* y);
    
    // Function to traverse the tree
    void traverse();
    
    // Function to search a key in the subtree rooted at this node
    BTreeNode* search(int key);
    
    // Function to delete a key from the subtree rooted at this node
    void remove(int key);
    
    // Function to get the index of the first key greater than or equal to the key
    int findKey(int key);
};

// BTree class represents the B-Tree
class BTree {
public:
    BTreeNode* root;
    int t;  // Minimum degree (defines the range for number of keys)

    // Constructor to create an empty B-Tree
    BTree(int t);
    
    // Function to traverse the tree
    void traverse() {
        if (root != nullptr) root->traverse();
    }
    
    // Function to insert a new key
    void insert(int key);
    
    // Function to search a key
    BTreeNode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }
    
    // Function to delete a key
    void remove(int key) {
        if (root == nullptr) return;
        root->remove(key);
        
        // If the root has no keys, make the first child as the new root
        if (root->keys.empty()) {
            BTreeNode* tmp = root;
            if (root->leaf) {
                root = nullptr;
            } else {
                root = root->children[0];
            }
            delete tmp;
        }
    }
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;
    this->keys.reserve(2 * t - 1);
    this->children.reserve(2 * t);
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;
    
    // If this is a leaf node, insert the key into the appropriate position
    if (leaf) {
        keys.push_back(0);  // Create space for the new key
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > key)
            i--;
        i++;
        
        // If the child is full, split it
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);
            
            // After splitting, the middle key of the child moves up, compare the new key with the middle key
            if (keys[i] < key)
                i++;
        }
        
        children[i]->insertNonFull(key);
    }
}

// Split the child of this node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->keys.resize(t - 1);
    
    // Copy the last (t - 1) keys of y to z
    copy(y->keys.begin() + t, y->keys.end(), z->keys.begin());
    
    // If y is not a leaf, copy the last t children of y to z
    if (!y->leaf) {
        z->children.resize(t);
        copy(y->children.begin() + t, y->children.end(), z->children.begin());
    }
    
    // Reduce the number of keys in y
    y->keys.resize(t - 1);
    y->children.resize(t);
    
    // Move all the children of this node to the right
    children.insert(children.begin() + i + 1, z);
    
    // Insert the middle key of y into this node
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// Traverse the tree and print all keys
void BTreeNode::traverse() {
    int i = 0;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf)
            children[i]->traverse();
        cout << keys[i] << " ";
    }
    
    if (!leaf)
        children[i]->traverse();
}

// Search for a key in the tree
BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i])
        i++;
    
    if (i < keys.size() && keys[i] == key)
        return this;
    
    if (leaf)
        return nullptr;
    
    return children[i]->search(key);
}

// Find the index of the first key greater than or equal to key
int BTreeNode::findKey(int key) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < key)
        ++idx;
    return idx;
}

// Constructor for BTree
BTree::BTree(int t) {
    root = new BTreeNode(t, true);
    this->t = t;
}

// Insert a new key in the B-Tree
void BTree::insert(int key) {
    // If root is full, split it and create a new root
    if (root->keys.size() == 2 * t - 1) {
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(root);
        s->splitChild(0, root);
        
        // New root has two children, insert the key into the appropriate child
        s->insertNonFull(key);
        
        root = s;
    } else {
        root->insertNonFull(key);
    }
}

int main() {
    BTree tree(3);  // A B-Tree with minimum degree 3 (each node can have at most 5 keys)
    
    // Insert elements into the B-Tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);
    
    // Print the tree
    cout << "Traversal of the B-Tree:\n";
    tree.traverse();
    cout << endl;
    
    // Search for a key
    int key = 12;
    BTreeNode* result = tree.search(key);
    if (result != nullptr) {
        cout << "Key " << key << " found in the tree.\n";
    } else {
        cout << "Key " << key << " not found in the tree.\n";
    }
    
    return 0;
}

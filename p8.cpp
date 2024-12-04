#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// A node in the Suffix Tree
class SuffixTreeNode {
public:
    map<char, SuffixTreeNode*> children; // Map of children
    int start, *end;                      // Start and end of substring
    int suffixLink;                       // Suffix link for Ukkonen's algorithm (if used)

    // Constructor to initialize the node
    SuffixTreeNode(int start, int* end) : start(start), end(end), suffixLink(-1) {}
};

// Suffix Tree class
class SuffixTree {
public:
    string text;                        // The input string
    SuffixTreeNode* root;               // The root of the tree
    int size;                           // Length of the string
    vector<int> suffixLinks;            // To store suffix links (if using Ukkonen’s algorithm)
    
    // Constructor to initialize the Suffix Tree with a string
    SuffixTree(string inputText) {
        text = inputText + "$"; // Append a special character to avoid matching the string itself
        size = text.size();
        root = new SuffixTreeNode(-1, nullptr);  // Create a root node
    }
    
    // Build the Suffix Tree (naive approach)
    void build() {
        // Insert all suffixes into the Suffix Tree
        for (int i = 0; i < size; ++i) {
            insertSuffix(i);
        }
    }

    // Insert a suffix into the tree starting from the given index
    void insertSuffix(int index) {
        SuffixTreeNode* currentNode = root;
        int start = index;
        
        for (int i = index; i < size; ++i) {
            char currentChar = text[i];
            
            // If there is no child for this character, create a new node
            if (currentNode->children.find(currentChar) == currentNode->children.end()) {
                int* end = new int(i);
                SuffixTreeNode* newNode = new SuffixTreeNode(start, end);
                currentNode->children[currentChar] = newNode;
                return;
            } else {
                currentNode = currentNode->children[currentChar];
            }
        }
    }

    // Traverse the Suffix Tree and print all substrings
    void printTree() {
        printTreeRecursive(root);
    }

private:
    // Recursive function to print all substrings in the tree
    void printTreeRecursive(SuffixTreeNode* node) {
        // If the node is a leaf, print the substring represented by the node
        if (node->children.empty()) {
            cout << text.substr(node->start, *node->end - node->start + 1) << endl;
        }
        
        // Recur for all children
        for (auto& child : node->children) {
            printTreeRecursive(child.second);
        }
    }
};

// Main function to test the Suffix Tree
int main() {
    string inputText;
    cout << "Enter a string to build the Suffix Tree: ";
    cin >> inputText;
    
    // Create a Suffix Tree object
    SuffixTree tree(inputText);
    
    // Build the Suffix Tree
    tree.build();
    
    // Print all substrings from the Suffix Tree
    cout << "Substrings in the Suffix Tree: " << endl;
    tree.printTree();
    
    return 0;
}

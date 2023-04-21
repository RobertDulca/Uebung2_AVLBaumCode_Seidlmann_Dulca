#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        root = new Node;
        root->key = key;
        root->left = nullptr;
        root->right = nullptr;
    } else if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

void traverse(Node* root) {
    if (root != nullptr) {
        traverse(root->left);
        cout << root->key << " ";
        traverse(root->right);
    }
}

int main() {
    Node* root = nullptr;
    ifstream file("input.txt");
    int key;
    while (file >> key) {
        root = insert(root, key);
    }
    file.close();
    traverse(root);
    return 0;
}


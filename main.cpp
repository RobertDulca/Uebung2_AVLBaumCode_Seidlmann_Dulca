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
    string command, filename;
    cout << "Please enter the command in the format: treecheck filename" << endl;
    cin >> command >> filename;
    if (command != "treecheck") {
        cout << "Invalid command: " << command << endl;
        return 1;
    }

    Node* root = nullptr;
    ifstream file(filename);
    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "File is empty." << endl;
        return 1;
    }
    int key;
    while (file >> key) {
        root = insert(root, key);
    }
    file.close();
    traverse(root);
    return 0;
}



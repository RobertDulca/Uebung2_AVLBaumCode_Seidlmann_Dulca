#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

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

int height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

vector<pair<int,int>> TreeList;
int sumKeys = 0;
int maxKey = 0;
int minKey = 10000000;

void checkAVLHelper(Node* root, bool& isAVL) {
    if (root == nullptr) {
        return;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int balanceFactor = abs(leftHeight - rightHeight);
    //cout << "Node " << root->key << ": balance factor = " << abs(balanceFactor) << endl;
    TreeList.push_back(make_pair(root->key,balanceFactor));
    if(root->key > maxKey)
        maxKey = root->key;
    if (root->key < minKey)
        minKey = root->key;
    sumKeys += root->key;
    if (abs(balanceFactor) > 1) {
        isAVL = false;
    }
    checkAVLHelper(root->left, isAVL);
    checkAVLHelper(root->right, isAVL);
}

bool checkAVL(Node* root) {
    bool isAVL = true;
    checkAVLHelper(root, isAVL);
    return isAVL;
}

Node* search(Node* root, int key) {
    Node* node = root;
    vector<int> path;
    while (node != nullptr) {
        path.push_back(node->key);
        if (node->key == key) {
            cout << key << " found ";
            for (int i = 0; i < path.size() - 1; i++) {
                cout << path[i] << ", ";
            }
            cout << endl;
            return node;
        } else if (node->key < key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    cout << key << " not found!" << endl;
}

bool searchSubtree(Node* root, Node* subtree) {
    if (subtree == nullptr) {
        return true;
    }
    if (root == nullptr) {
        return false;
    }
    if (root->key == subtree->key) {
        return searchSubtree(root->left, subtree->left) && searchSubtree(root->right, subtree->right);
    }
    return searchSubtree(root->left, subtree) || searchSubtree(root->right, subtree);
}


int main() {
    string command, filename;
    cout << "Please enter the command in the format: treecheck filename searchValue" << endl;
    cin >> command >> filename;
    int searchValue;
    cin >> searchValue;
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

    Node* result = search(root, searchValue);
    if (result != nullptr) {
        cout << "Found value " << searchValue << " in tree." << endl;
    } else {
        cout << "Could not find value " << searchValue << " in tree." << endl;
    }

    traverse(root);
    cout << endl;
    bool isAVL = checkAVL(root);
    for (int i = TreeList.size()-1; i >= 0; --i) {
        cout << "Node " << TreeList[i].first << ": balance factor = " << TreeList[i].second << endl;
    }
    if (isAVL) {
        cout << "AVL : yes" << endl;
    } else {
        cout << "AVL: no" << endl;
    }
    float avgKeys = static_cast<float>(sumKeys) / static_cast<float>(TreeList.size());
    cout << "min: " << minKey << ", max: " << maxKey << ", avg: " << avgKeys;

    string subtree_filename;
    cout << "\nEnter the subtree filename: ";
    cin >> subtree_filename;

    string subtree_filepath = subtree_filename + ".txt";

    ifstream subtree_input(subtree_filepath);
    if (!subtree_input) {
        cerr << "\nError opening file: " << subtree_filename << endl;
        return 1;
    }

    Node* subtree_root = nullptr;
    int subtree_key;
    while (subtree_input >> subtree_key) {
        subtree_root = insert(subtree_root, subtree_key);
    }
    subtree_input.close();

    if (!searchSubtree(root, subtree_root)) {
        cout << "\nSubtree not found!" << endl;
    }
    else{
        cout << "\nSubtree found!" << endl;
    }

    return 0;
}

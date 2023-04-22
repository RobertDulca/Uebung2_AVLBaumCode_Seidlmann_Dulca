#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

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
    cout << endl;
    bool isAVL = checkAVL(root);
    for (int i = size(TreeList)-1; i >= 0; --i) {
        cout << "Node " << TreeList[i].first << ": balance factor = " << TreeList[i].second << endl;
    }
    if (isAVL) {
        cout << "AVL : yes"<< endl;
    } else {
        cout << "AVL: no" << endl;
    }
    float avgKeys = static_cast<float> (sumKeys)/ static_cast<float>(size(TreeList));
    cout<< "min: "<<minKey<<", max: "<<maxKey<<", avg: "<< avgKeys;
    return 0;
}

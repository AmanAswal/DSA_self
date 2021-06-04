#include<iostream>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    int bal = 0;
    int height = 0;

    TreeNode(int val)
        this->val = val;
};

void updateBalanceAndHeight(TreeNode* node){ // O(1)
    if(node == nullptr) return;

    int lh = -1;
    int rh = -1;

    if(node->left != nullptr) lh = node->left->height;
    if(node->right != nullptr) rh = node->right->height;

    node->bal = lh - rh;
    node->height = max(lh, rh) + 1;
}

TreeNode* rightRotation(TreeNode* A){   // O(1)
    TreeNode* B = A->right;
    TreeNode* BkaLeft = B->left;

    B->left = A;
    A->right = BkaLeft;

    updateBalanceAndHeight(A);
    updateBalanceAndHeight(B);

    return B;
}

TreeNode* leftRotation(TreeNode* A){ // O(1)
    TreeNode* B = A->left;
    TreeNode* BkaRight = B->right;

    B->right = A;
    A->left = BkaRight;

    updateBalanceAndHeight(A);
    updateBalanceAndHeight(B);

    return B;
}

TreeNode* getRotation(TreeNode* node){
    updateBalanceAndHeight(node);

    if(node->bal == 2){ // ll, lr
        if(node->left->bal == 1){ //ll
            return rightRotation(node);
        }
        else{ // lr

        }
    }
    else if(node->bal == -2){ // rr, rl
        if(node->right->bal == -1){ //rr
            return leftRotation(node);
        }
        else{ // rl  

        }
    }

    return node;
}

// basic BST =========================================================================


// height of tree
int heightOfTree(TreeNode* root){
    if(root == nullptr) return -1;

    return max(heightOfTree(root->left), heightOfTree(root->right)) + 1;
}


// maximum
int maximumEle(TreeNode* root){

    TreeNode* curr = root;
    while(curr->right != nullptr)
        curr = curr->right;

    return curr->val;
}

// minimum
int minimumEle(TreeNode* root){

    TreeNode* curr = root;
    while(curr->left != nullptr)
        curr = curr->left;

    return curr->val;
}

// recursive
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root == nullptr) 
        return new TreeNode(val);

    if(root->val > val)
        root->left = insertIntoBST(root->left, val);
    else
        root->right = insertIntoBST(root->right, val);
    
    return getRotation(root);
}

// 450. Delete Node in a BST
TreeNode* deleteNode(TreeNode* root, int key) {
    if(root == nullptr)
        return nullptr;

    if(root->val > key)
        root->left = deleteNode(root->left, key);
    else if(root->val < key)
        root->right = deleteNode(root->right, key);
    else{
        if(root->left == nullptr || root->right == nullptr) // one child
            return root->left != nullptr ? root->left : root->right;

        int maxValue = maximumEle(root->left);  
        root->val = maxValue;

        root->left = deleteNode(root->left, maxValue);
    }
    return getRotation(root);
}


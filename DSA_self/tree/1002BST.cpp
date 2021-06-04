#include<iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// height of tree
int heightOfTree(TreeNode* root){
    if(root == nullptr) return -1;

    return max(heightOfTree(root->left), heightOfTree(root->right)) + 1;
}

// size of tree
int size(TreeNode* root){
    if(root == nullptr) return 0;

    return size(root->left) + size(root->right) + 1;
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

bool findData(TreeNode* root, int data){
    TreeNode* curr = root;

    while(curr != nullptr){
        if(curr->val == data)
            return true;
        else if(curr->val > data)
            curr = curr->left;
        else   
            curr = curr->right;
    }
    return false;
}

bool findData2(TreeNode* root, int data){
    if(root == nullptr) return false;
    if(root->val == data) return true;

    if(root->val > data) 
        return findData2(root->left, data);
    else
        return findData2(root->right, data);
}

// 701. Insert into a Binary Search Tree
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root == nullptr) 
        return new TreeNode(val);

    TreeNode* curr = root;
    TreeNode* newNode = new TreeNode(val);

    while(curr != nullptr){
        if(curr->val > val){
            if(curr->left == nullptr){
                curr->left = newNode;
                break;
            }
            curr = curr->left;
        }
        else{
            if(curr->right == nullptr){
                curr->right = newNode;
                break;
            }
            curr = curr->right;
        }    
    }
    return root;
}

// recursive
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root == nullptr) 
        return new TreeNode(val);

    if(root->val > val)
        root->left = insertIntoBST(root->left, val);
    else
        root->right = insertIntoBST(root->right, val);
    
    return root;
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
    return root;
}

// 235. Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* curr = root;
    while(curr != nullptr){
        if(curr->val > p->val && curr->val > q->val)
            curr = curr->left;
        else if(curr->val < p->val && curr->val < q->val)
            curr = curr->right;
        else    
            return curr;
    }
    return nullptr;
}

// 108. Convert Sorted Array to Binary Search Tree
TreeNode* createBST(vector<int> &arr, int si, int ei){
    if(si > ei) return nullptr;

    int mid = (si + ei) / 2;
    TreeNode* node = new TreeNode(arr[mid]);
    node->left = createBST(arr, si, mid - 1);
    node->right = createBST(arr, mid + 1, ei);
    return node;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return createBST(nums, 0, nums.size() - 1);
}

int main()
{
    return 0;
}
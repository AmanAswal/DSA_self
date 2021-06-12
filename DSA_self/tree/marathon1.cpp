#include<iostream>
#include<vector>

using namespace std;

class TreeNode{
public:
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int val){
        this->val = val;
    }
};

// 98. Validate Binary Search Tree
TreeNode* prev = nullptr;
bool isValidBST(TreeNode* root) {
    if(root == nullptr) return true;

    if(!isValidBST(root->left)) return false;

    if(prev != nullptr && prev->val >= root->val) return false;
    prev = root;

    if(!isValidBST(root->right)) return false;

    return true;
}

// 99. Recover Binary Search Tree
TreeNode* prev = nullptr;
TreeNode* a = nullptr;
TreeNode* b = nullptr;

void recoverTree_helper(TreeNode* root) {
    if(root == nullptr) return;

    recoverTree_helper(root->left);

    if(prev != nullptr && prev->val > root->val){
        b = root;
        if(a == nullptr) a = prev;
        else return;
    }
    prev = root;
    recoverTree_helper(root->right);
}

void recoverTree(TreeNode* root){
    recoverTree_helper(root);
    if(a != nullptr){
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}

// pred & succ in BT and BST also ceil and floor

// BST also ceil and floor
void predSuccInBST(TreeNode* root, int data){
    TreeNode* curr = node;
    TreeNode* pred = nullptr;
    TreeNode* succ = nullptr;

    while(curr != nullptr){

        if(curr->val == data){
            if(curr->left != nullptr){
                pred = curr->left;
                while(pred->right != nullptr) 
                    pred = prev->right;
            }
            if(curr->right != nullptr){
                succ = curr->right;
                while(succ->left != nullptr)
                    succ = succ->left;
            }
            break;
        }
        else if(curr->val > data){
            succ = curr;
            curr = curr->left;
        }
        else if (curr->val < data){
            pred = curr;
            curr = curr->right;
        }
    }
}

// binary tree pred & succ
TreeNode* pred = nullptr;
TreeNode* prev = nullptr;
TreeNode* succ = nullptr;
void predSuccInBinaryTree(TreeNode* root, int data){
    if(root == nullptr) return;
    
    predSuccInBinaryTree(root->left, data);

    if(pred == nullptr && root->val == data)
        pred = prev;
    
    if(prev != nullptr && prev->val == data && succ == nullptr)
        succ = root;
    
    prev = root;
    predSuccInBinaryTree(root->right, data);    
}

// 173. Binary Search Tree Iterator
stack<TreeNode*> st;
    BSTIterator(TreeNode* root) {
        addAllLeft(root);
    }
        
    void addAllLeft(TreeNode* node){
        if(node == nullptr) return;
        TreeNode* curr = node;
        while(curr != nullptr){
            st.push(curr);
            curr = curr->left;
        }
    }
    
    int next() {
        TreeNode* rn = st.top();
        st.pop();
        addAllLeft(rn->right);
        return rn->val;
    }
    
    bool hasNext() {
        return st.size() != 0;
    }
};

// 105. Construct Binary Tree from Preorder and Inorder Traversal
TreeNode* buildTree_(vector<int>& preorder, int psi, int pei, vector<int>& inorder, int isi, int iei) {
    if(psi > pei) return nullptr;

    TreeNode* node = new TreeNode(preorder[psi]);
    int idx = isi;
    while(inorder[idx] != preorder[psi]) idx++;
    int tnel = idx - isi;

    node->left = buildTree_(preorder, psi + 1, psi + tnel, inorder, isi, idx - 1);
    node->right = buildTree_(preorder, tnel + psi + 1, pei, inorder, idx + 1, iei);

    return node;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int n = preorder.size();
    return buildTree_(preorder, 0, n - 1, inorder, 0, n - 1);
}

// 106. Construct Binary Tree from Inorder and Postorder Traversal
TreeNode* buildTree_helper(vector<int>& inorder,int isi, int iei, vector<int>& postorder, int psi, int pei) {
    if(psi > pei) return nullptr;

    TreeNode* node = new TreeNode(postorder[pei]);
    int idx = isi;
    while(inorder[idx] != postorder[pei]) idx++;
    int tnel = idx - isi;

    node->left = buildTree_helper(inorder, isi, idx - 1, postorder, psi, psi + tnel - 1);
    node->right = buildTree_helper(inorder, idx + 1, iei, postorder, psi + tnel, pei - 1);

    return node;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = inorder.size();
    return buildTree_helper(inorder, 0, n - 1, postorder, 0, n - 1);
}

// 889. Construct Binary Tree from Preorder and Postorder Traversal
TreeNode* constructFromPrePost_(vector<int>& pre, int prsi, int prei, vector<int>& post, int posi, int poei) {
    if(prsi > prei) return nullptr;
    TreeNode* node = new TreeNode(pre[prsi]);

    if(prsi == prei) return node;

    int idx = posi;
    while(pre[prsi + 1] != post[idx]) idx++;
    int tnel = idx - posi + 1;

    node->left = constructFromPrePost_(pre, prsi + 1, tnel + prsi, post, posi, idx);
    node->right = constructFromPrePost_(pre, prsi + tnel + 1, prei, post, idx + 1, poei - 1);

    return node;
}

TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    int n = pre.size();
    return constructFromPrePost_(pre, 0, n - 1, post, 0, n - 1);
}

// 1008. Construct Binary Search Tree from Preorder Traversal
int idx = 0;
TreeNode* bstFromPreorder_(vector<int>& preorder, int lb, int rb) {
    if(idx == preorder.size() || preorder[idx] < lb || preorder[idx] > rb) return nullptr;

    TreeNode* node = new TreeNode(preorder[idx++]);

    node->left = bstFromPreorder_(preorder, lb, node->val);
    node->right = bstFromPreorder_(preorder, node->val, rb);

    return node;
}

TreeNode* bstFromPreorder(vector<int>& preorder) {
    int lb = -(int)1e8;
    int rb = (int)1e8;

    return bstFromPreorder_(preorder, lb, rb);
}

// 114. Flatten Binary Tree to Linked List
// O(n^2)
TreeNode* getTail(TreeNode* node){
    if(node == nullptr) return nullptr;
    TreeNode* curr = node;

    while(curr->left != nullptr)
        curr = curr->left;
    
    return curr;
}

void flatten_01(TreeNode* root) {
    if(root == nullptr) return;

    flatten_01(root->left);
    flatten_01(root->right);

    TreeNode* tail = getTail(root->left);
    if(tail != nullptr){
        tail->right = root->right;
        root->right = root->left;
        root->left = nullptr;
    }
}

// O(n)
TreeNode* flatten_02(TreeNode* node){
    if(node == nullptr || (node->left == nullptr && node->right == nullptr)) return node;

    TreeNode* leftTail = flatten_02(node->left);
    TreeNode* rightTail = flatten_02(node->right);

    if(leftTail != nullptr){
        leftTail->right = node->right;
        node->right = node->left;
        node->left = nullptr;
    }
    return rightTail != nullptr ? rightTail : leftTail;
}

void flatten(TreeNode* root) {
    if(root == nullptr) return;
    flatten_02(root);
}

// 426. Convert Binary Search Tree to Sorted Doubly Linked List 
Node* dummy = new Node(-1);
Node* prev = dummy;
void treeToDoublyList_helper(Node* root){
    if(root == nullptr) return;

    treeToDoublyList_helper(root->left);

    root->left = prev;
    prev->right = root;
    
    prev = root;

    treeToDoublyList_helper(root->right);
}

Node* treeToDoublyList(Node* root){
    if(root == nullptr) return nullptr;
    treeToDoublyList_helper(root);
    
    Node* head = dummy->right;
    head->left = nullptr;
    dummy->right = nullptr;

    head->left = prev;
    prev->right = head;

    return head;
}

// 297 (both array and string)
// we do pre order traversal

// array
// serialize
void serialize_helper(TreeNode* root, vector<int> &ans){
    if(root == nullptr){
        ans.push_back(-1);
        return;
    }

    ans.push_back(root->val);

    serialize_helper(root->left, ans);
    serialize_helper(root->right, ans);
}

vector<int> serialize(TreeNode* root){
    vector<int> ans;
    serialize_helper(root);
    return ans;
}

// deserialize
int idx = 0;
TreeNode* deserialize(vector<int> &arr){
    if(idx == arr.size() || arr[idx] == -1) {
        idx++;
        return nullptr;
    }

    TreeNode* node = new TreeNode(arr[idx++]);

    node->left = deserialize(arr);
    node->right = deserialize(arr);

    return node;
}

// morris traversal (in and pre)
TreeNode* rightMost(TreeNode* next, TreeNode* curr){
    while(next->right != nullptr && next->right != curr)
        next = next->right;

    return next;
}

// INORDER
void morrisInorderTraversal(TreeNode* root){
    TreeNode* curr = root;

    while(curr != nullptr){
        TreeNode* next = curr->left;

        if(next == nullptr){    // print and move right
            cout << curr->val << " ";
            curr = curr->right;
        }
        else{
            TreeNode* rightMost = rightMost(next, curr);
            if(rightMost->right == nullptr){ // create thread and move left
                rightMost->right = curr;
                curr = curr->left;
            }
            else{  // break thread, print and move right
                cout << curr->val << " ";
                rightMost->right = nullptr;
                curr = curr->right;
            }
        }
    }
}

// preorder
void morrisInorderTraversal(TreeNode* root){
    TreeNode* curr = root;

    while(curr != nullptr){
        TreeNode* next = curr->left;

        if(next == nullptr){    // print and move right
            cout << curr->val << " ";
            curr = curr->right;
        }
        else{
            TreeNode* rightMost = rightMost(next, curr);
            if(rightMost->right == nullptr){ // create thread and move left
                rightMost->right = curr;
                cout << curr->val << " ";
                curr = curr->left;
            }
            else{  // break thread, print and move right
                rightMost->right = nullptr;
                curr = curr->right;
            }
        }
    }
}

// traversal using stack (in, pre, post)

// 1008
// 1008 (postorder)
// level order traversel 

// 108
// 235

int main(){

}
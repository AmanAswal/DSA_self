#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


bool find(TreeNode* node, TreeNode* data){
    if(node == nullptr) return false;
    if(node == data) return true;

    return find(node->left, data) || find(node->right, data);
}

// node to root path
bool nodeToRootPath(TreeNode* node, TreeNode* data, vector<TreeNode*>& ans){
    if(node == nullptr) return false;

    if(node == data){
        ans.push_back(node);
        return true;
    }

    bool res = false;

    res = nodeToRootPath(node->left, data, ans) || nodeToRootPath(node->right, data, ans);
    
    if(res) 
        ans.push_back(node);
    
    return res;
}

// node to root path 2
vector<TreeNode*> nodeToRootPath2(TreeNode* node, TreeNode* data){
    if(node == nullptr) return {};

    if(node == data){
        vector<TreeNode*> ans;
        ans.push_back(node);
        return ans;
    }

    vector<TreeNode*> left = nodeToRootPath2(node->left, data);
    if(left.size() > 0){
        left.push_back(node);
        return left;
    }

    vector<TreeNode*> right = nodeToRootPath2(node->right, data);
    if(right.size() > 0){
        right.push_back(node);
        return right;
    }

    return {};
}


// 236. Lowest Common Ancestor of a Binary Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    vector<TreeNode*> list1; 
    vector<TreeNode*> list2;

    nodeToRootPath(root, p, list1);
    nodeToRootPath(root, q, list2);


    TreeNode* LCA = nullptr;

    int i = list1.size() - 1;
    int j = list2.size() - 1;

    while(i >= 0 && j >= 0){
        if(list1[i] != list2[j]) break;
        LCA = list1[i];
        i--;
        j--;
    }
    return LCA;
}

// Kdown
void kDown(TreeNode* node, TreeNode* block, int k, vector<TreeNode*> &ans){
    if(node == nullptr || node == block || k < 0) return;

    if(k == 0){
        ans.push_back(node);
        return;
    }

    kDown(node->left, block, k - 1, ans);
    kDown(node->right, block, k - 1, ans);
}


// 863. All Nodes Distance K in Binary Tree
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    vector<TreeNode*> list;
    nodeToRootPath(root, target, list);

    vector<int> res;
    TreeNode* blockNode = nullptr;
    for(int i = 0; i < list.size(); i++){
        kDown(list[i], blockNode, k - i, res);
        blockNode = list[i];
    }
    return res;
}

// node to root distance w.r.t edges
int nodeToRootPathDistance(TreeNode* root, TreeNode* data){
    if(root == nullptr) return -1;

    if(root == data) return 0;

    int lans = nodeToRootPathDistance(root->left, data);
    if(lans != -1){
        return lans + 1;
    }

    int rans = nodeToRootPathDistance(root->right, data);
    if(rans != -1){
        return rans + 1;
    }

    return -1;
}


// 863. All Nodes Distance K in Binary Tree
int distanceK2_(TreeNode* root, TreeNode* target, int k, vector<int>& ans) {
    if(root == nullptr) return -1;

    if(root == target){
        kDown(root, nullptr, k , ans);
        return 1;
    }

    int lans = distanceK2_(root->left, target, k , ans);
    if(lans != -1){
        kDown(root, root->left, k - lans, ans);
        return lans + 1;
    }

    int rans = distanceK2_(root->right, target, k, ans);
    if(rans != -1){
        kDown(root, root->right, k - rans, ans);
        return rans + 1;
    }
    return -1;
}

vector<int> distanceK2(TreeNode* root, TreeNode* target, int k) {
    vector<int> ans;
    distanceK2_(root, target, k, ans);
    return ans;
}

// height of tree
int heightOfTree(TreeNode* root){
    if(root == nullptr) return -1;

    return max(heightOfTree(root->left), heightOfTree(root->right)) + 1;
}


// diameter of tree ( in terms of edges )
// max(d1, d2, h1 + h2 + 2);
int diameterOfBinaryTree_01(TreeNode* root){
    if(root == nullptr) return -1;

    int leftDia = diameterOfBinaryTree_01(root->left);
    int rightDia = diameterOfBinaryTree_01(root->right);

    int leftHeight = heightOfTree(root->left);
    int rightHeight = heightOfTree(root->right);


    return max(max(leftDia, rightDia), leftHeight + rightHeight + 2);
}

// method 2 i.e {dia,height}
vector<int> diameterOfBinaryTree_02(TreeNode* root){
    if(root == nullptr) return {-1, -1};

    vector<int> leftAns = diameterOfBinaryTree_02(root->left);

    vector<int> rightAns = diameterOfBinaryTree_02(root->right);

    vector<int> ans(2, 0);
    ans[0] = max(max(leftAns[0], rightAns[0]), leftAns[1] + rightAns[1] + 2);
    ans[1] = max(leftAns[1], rightAns[1]) + 1;

    return ans;
}

// method 3 i.e using Diameter as refernce and global variable or pass it as reference
int maxDia = 0;
int diameterOfBinaryTree_03(TreeNode* root){
    if(root == nullptr) return -1;

    int lh = diameterOfBinaryTree_03(root->left);
    int rh = diameterOfBinaryTree_03(root->right);

    maxDia = max(maxDia, lh + rh + 2);

    return max(lh, rh) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    if(root == nullptr) return 0;
    // return diameterOfBinaryTree_02(root)[0];
    diameterOfBinaryTree_03(root);
    return maxDia;
}

// 112. Path Sum
bool hasPathSum(TreeNode* root, int targetSum) {
    if(root == nullptr) return false;

    if(root->left == nullptr && root->right == nullptr){
        if(targetSum - root->val == 0) return true;
        else return false;
    }

    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}

// 113. Path Sum II
void pathSum_(TreeNode* root, int targetSum, vector<int> &smallAns , vector<vector<int>> &ans) {
    if(root == nullptr) return;

    if(root->left == nullptr && root->right == nullptr){
        if(targetSum - root->val == 0) {
            smallAns.push_back(root->val);
            ans.push_back(smallAns);
        }
        return;
    }
    smallAns.push_back(root->val);
    pathSum_(root->left, targetSum - root->val, smallAns, ans);
    pathSum_(root->right, targetSum - root->val, smallAns, ans);
    smallAns.pop_back();
}   

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> ans;
    vector<int> smallAns;

    pathSum_(root, targetSum, smallAns, ans);
    return ans;
}

// Maximum Path Sum between 2 Leaf Nodes 
// https://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
int maxLeafToLeaf = -(int)1e9;
int maxPathSum_(Node* root){
    if(root == nullptr) return -(int)1e9;
    if(root->left == nullptr && root->right == nullptr) return root->data;

    int leftNodeToLeaf = maxPathSum_(root->left);
    int rightNodeToLeaf = maxPathSum_(root->right);

    if(root->left != nullptr && root->right != nullptr)
        maxLeafToLeaf = max(maxLeafToLeaf, leftNodeToLeaf + root->data + rightNodeToLeaf);
    
    return max(leftNodeToLeaf, rightNodeToLeaf) + root->data;
}

int maxPathSum(Node* root){
    maxPathSum_(root);
    return maxLeafToLeaf;
}


// 124. Binary Tree Maximum Path Sum
int maxPathSum_(TreeNode* root, int &maxNTN) {
    if(root == nullptr) return 0;
    
    int leftMaxPathSum = maxPathSum_(root->left, maxNTN);
    int rightMaxPathSum = maxPathSum_(root->right, maxNTN);

    int maxSumTillRoot = max(leftMaxPathSum, rightMaxPathSum) + root->val;

    maxNTN = max(max(maxNTN, maxSumTillRoot), max(root->val, leftMaxPathSum + root->val + rightMaxPathSum));

    return max(root->val, maxSumTillRoot);
}

int maxPathSum(TreeNode* root) {
    int maxNTN = -(int)1e9;
    maxPathSum_(root, maxNTN);
    return maxNTN;
}

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
TreeNode* a = nullptr;
TreeNode* b = nullptr;
TreeNode* prev = nullptr;
bool recoverTree_(TreeNode* root) {
    if(root == nullptr) return true;

    if(!recoverTree_(root->left)) return false;
    
    if(prev != nullptr && prev->val > root->val){
        b = root;
        if(a == nullptr) a = prev;
        else return false;
    }
    prev = root;
    if(!recoverTree_(root->right)) return false;

    return true;
}

void recoverTree(TreeNode* root) {
    recoverTree_(root);
    if(a != nullptr){
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
}

// predessor and successor
// binary tree O(n)
class allSolPair{
    TreeNode* prev = nullptr;
    TreeNode* pred = nullptr;
    TreeNode* succ = nullptr;
}

void allSolution(TreeNode* node, int data, allSolPair pair){
    if(node == nullptr) return;

    allSolution(node->left, data, pair);

    if(node->val == data && pair.pred == nullptr)
        pair.pred = pair.prev;

    if(pair.prev != nullptr && pair.prev->val == data && succ == nullptr)
        pair.succ = node;

    pair->prev = node;

    allSolution(node->right, data, pair);
}


// predecesor and succesor in BST - O(logn)
// ceil and floor
void predSuccInBST(TreeNode* node, int data){
    TreeNode* curr = node;
    TreeNode* pred = nullptr;
    TreeNode* succ = nullptr;
    
    bool isDataPresent = false;

    while(curr != null){

        if(curr->val == data){
            isDataPresent = true;
            if(curr->left != nullptr){
                pred = curr->left;
                while(pred->right != nullptr)
                    pred = pred->right;
            }

            if(curr->right != nullptr){
                succ = curr->right;
                while(succ->left != nullptr)
                    succ = succ->left;
            }
            break;
        }
        else if(curr->val < data){
            pred = curr;
            curr = curr->left;
        }
        else{
            succ = curr;
            curr = curr->right;
        }
    }
    if(isDataPresent) // real pred & succ
    if(!isDataPresent) // ceil and floor 
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

//  510. Inorder Successor in BST II #510

/*
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

Node* InorderSuccessor(Node* node){

    if(node->right != nullptr){
        node = node->right;
        while(node->left != nullptr) node = node->left;

        return node;
    }
    else{
        while(node != null){
            if(node->parent != nullptr && node->parent->left == node) 
                return node->parent;
            
            node = node->parent;
        }
    }
    return nullptr;
}


// construction

// T => avg: O(nlogn), worst : O(n^2)

// 105. Construct Binary Tree from Preorder and Inorder Traversal
// psi = preorder starting index, isi = inorder starting index
TreeNode* buildTree_(vector<int>& preorder, int psi, int pei, vector<int>& inorder, int isi, int iei) {
    if(psi > pei) return nullptr;

    TreeNode* node = new TreeNode(preorder[psi]);
    int idx = isi;

    while(inorder[idx] != preorder[psi])
        idx++;

    int tnel = idx - isi;   // total no of elements

    node->left = buildTree_(preorder, psi + 1, psi + tnel, inorder, isi, idx - 1);

    node->right = buildTree_(preorder, psi + tnel + 1 , pei, inorder, idx + 1, iei);

    return node;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildTree_(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

// 106. Construct Binary Tree from Inorder and Postorder Traversal
TreeNode* buildTree_helper(vector<int>& inorder, int isi, int iei, vector<int>& postorder, int psi, int pei) {
    if(psi > pei) return nullptr;

    TreeNode* node = new TreeNode(postorder[pei]);
    
    int idx = isi;
    while(inorder[idx] != postorder[pei]) idx++;

    int tnel = idx - isi;

    node->left = buildTree_helper(inorder, isi, idx - 1, postorder, psi, psi + tnel - 1);
    node->right = buildTree_helper(inorder, idx + 1, iei, postorder, pei + tnel, pei - 1);

    return node;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return buildTree_helper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
}

// 889. Construct Binary Tree from Preorder and Postorder Traversal
TreeNode* prePostTree(vector<int>& pre, int psi, int pei, vector<int>& post, int ppsi, int ppei) {
    if(psi > pei) return nullptr;

    TreeNode* node = new TreeNode(pre[psi]);

    if(psi == pei)
        return node;
    
    int idx = ppsi;
    while(post[idx] != pre[psi + 1])
        idx++;

    int tnel = idx - ppsi + 1;

    node->left = prePostTree(pre, psi + 1, psi + tnel, post, ppsi, idx); 
    node->right = prePostTree(pre, psi + tnel + 1, pei, post, idx + 1, ppei);

    return node;
}

TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    int n = pre.size();

    return prePostTree(pre, 0, n - 1, post, 0, n - 1);        
}

// 1008. Construct Binary Search Tree from Preorder Traversal
TreeNode* bstFromPreorder(vector<int>& preorder) {
        
}

// 114. Flatten Binary Tree to Linked List
// O(n^2)
TreeNode* getTailNode(TreeNode* root){
    if(root == nullptr) return nullptr;
    TreeNode* curr = root;
    while(curr->right != nullptr)
        curr = curr->right;

    return curr;
}

void flatten(TreeNode* root) {
    if(root == nullptr) return;

    flatten(root->left);
    flatten(root->right);
    TreeNode* tail = getTailNode(root->left);
    if(tail != nullptr){
        tail->right = root->right;
        root->right = root->left;
        root->left = nullptr;
    }
}

// O(n)
TreeNode* flatten_(TreeNode* node){
    if(node == nullptr || node->left == nullptr && node->right == nullptr) 
        return node;

    TreeNode* leftTail = flatten_(node->left);
    TreeNode* rightTail = flatten_(node->right);

    if(leftTail != nullptr){
        leftTail->right = node->right;
        node->right = node->left;
        node->left = nullptr;
    }

    return rightTail != nullptr ? rightTail : leftTail;
}

void flatten(TreeNode* root) {
    if(root == nullptr) return;
    flatten_(root);
}


// LeetCode 426. Convert Binary Search Tree to Sorted Doubly Linked List
Node* dummy = new Node(-1);
Node* prev = dummy;

void treeToDoublyList_(Node* root){
    if(root == nullptr) return;

    treeToDoublyList_(root->left);

    root->left = prev;
    prev->right = root;

    prev = root;

    treeToDoublyList_(root->right);
}

Node* treeToDoublyList(Node* root){
    if(root == nullptr) return nullptr;
    treeToDoublyList_(root);
    
    Node* head = dummy->right;
    head->left = nullptr;
    dummy->right = nullptr;

    prev->right = head;
    head->left = prev;
}

// https://www.geeksforgeeks.org/convert-a-binary-tree-to-a-circular-doubly-link-list/
    Node* dummy = new Node();
    Node* prev = dummy;
    
    void treeToDoublyList_(Node* root){
        if(root == nullptr) return;
    
        treeToDoublyList_(root->left);
    
        root->left = prev;
        prev->right = root;
    
        prev = root;
    
        treeToDoublyList_(root->right);
    }
    
    Node* bTreeToCList(Node* root){
        if(root == nullptr) return nullptr;
        treeToDoublyList_(root);
        
        Node* head = dummy->right;
        head->left = nullptr;
        dummy->right = nullptr;
    
        prev->right = head; // making circular
        head->left = prev;

        return head;
    }

// https://www.geeksforgeeks.org/in-place-convert-a-given-binary-tree-to-doubly-linked-list/
    Node* dummy = new Node();
    Node* prev = dummy;
    
    void treeToDoublyList_(Node* root){
        if(root == nullptr) return;
    
        treeToDoublyList_(root->left);
    
        root->left = prev;
        prev->right = root;
    
        prev = root;
    
        treeToDoublyList_(root->right);
    }
    
    Node* bToDLL(Node* root){
        if(root == nullptr) return nullptr;
        treeToDoublyList_(root);
        
        Node* head = dummy->right;
        head->left = nullptr;
        dummy->right = nullptr;
    
        return head;
    }



int main()
{
    return 0;
}

// 5 
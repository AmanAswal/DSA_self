#include<iostream>
#include<queue>
#include<unordered_map>

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

int size(TreeNode* root){
    return (root == nullptr) ? 0 : size(root->left) + size(root->right) + 1;
}

// in terms of root
int height(TreeNode* root){
    return (root == nullptr) ? -1 : max(height(root->left),height(root->right)) + 1;
}

bool find(TreeNode* root, TreeNode* data){
    if(root == nullptr) return false;
    if(root == data) return true;

    return find(root->left, data) || find(root->right, data);
}

// level order traversal
void bfs(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() > 0){
        TreeNode* rn = que.front();
        que.pop();

        cout << rn->val << " ";

        if(rn->left != nullptr) que.push(rn->left);
        if(rn->right != nullptr) que.push(rn->right);
    }
}

// level order traversal - Linewise
void bfs_linewise(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() > 0){
        int size = que.size();
        while(size-- > 0){
            TreeNode* rn = que.front();
            que.pop();

            cout << rn->val << " ";

            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
    }
}

// left view
void leftView(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() > 0){
        int size = que.size();
        cout << que.front()->val << " ";
        while(size-- > 0){
            TreeNode* rn = que.front();
            que.pop();

            // cout << rn->val << " ";

            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
    }
}

// right view
void rightView(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() > 0){
        int size = que.size();
        cout << que.back()->val << " ";
        while(size-- > 0){
            TreeNode* rn = que.front();
            que.pop();

            // cout << rn->val << " ";

            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
    }
}

// vertical order traversal
class vPair{
public:
    int hl = 0;
    TreeNode* node = nullptr;

    vPair(TreeNode* node, int hl){
        this->hl = hl;
        this->node = node;
    }
};

vector<vector<int>> verticalOrderTraversal(TreeNode* root){
    if(root == nullptr) return {};
    queue<vPair> que;
    unordered_map<int, vector<int>> map;
    int minHL= 0, maxHL = 0;

    que.push(vPair(root, 0));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();

            map[rp.hl].push_back(rp.node->val);

            minHL = min(minHL, rp.hl);
            maxHL = max(maxHL, rp.hl);

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1));
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1));
        }
    }

    vector<vector<int>> ans;

    while(minHl <= maxHL){
        ans.push_back(map[minHL++]);
    }
    return ans;
}

// vertical order traversal using width.
// {minHL, maxHL}
void width(TreeNode* root, int hl, vector<int> &maxMin){
    if(root == nullptr) return;

    maxMin[0] = min(maxMin[0], hl);
    maxMin[1] = max(maxMin[1], hl);

    width(root->left, hl - 1, maxMin);
    width(root->right, hl + 1, maxMin);
}

vector<vector<int>> verticalOrderTraversal_2(TreeNode* root){
    if(root == nullptr) return {};
    vector<int> maxMin(2, 0);
    width(root, 0, maxMin);
    int len = maxMin[1] - maxMin[0] + 1;
    vector<vector<int>> ans(len);

    queue<vPair> que;
    que.push(vPair(root, -maxMin[0]));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();

            ans[rp.hl] = rp.node->val;  // storing ans

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, hl - 1));
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, hl + 1));
        }
    }
    return ans;
}

// vertical order sum
vector<vector<int>> verticalOrderSum(TreeNode* root){
    if(root == nullptr) return {};
    vector<int> maxMin(2, 0);
    width(root, 0, maxMin);
    int len = maxMin[1] - maxMin[0] + 1;
    vector<vector<int>> ans(len);

    queue<vPair> que;
    que.push(vPair(root, -maxMin[0]));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();

            ans[rp.hl] += rp.node->val;  // storing ans

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1));
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1));
        }
    }
    return ans;
}

// top view
vector<int> topView(TreeNode* root){
    if(root == nullptr) return {};
    vector<int> maxMin(2, 0);
    width(root, 0, maxMin);
    int len = maxMin[1] - maxMin[0] + 1;
    vector<int> ans(len, -(int)1e9);

    queue<vPair> que;
    que.push(vPair(root, -maxMin[0]));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();

            if(ans[rp.hl] == -(int)1e9) ans[rp.hl] = rp.node->val;

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1));
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1));
        }
    }
    return ans;
}

// bottom view
vector<int> bottomView(TreeNode* root){
    if(root == nullptr) return {};
    vector<int> maxMin(2, 0);
    width(root, 0, maxMin);
    int len = maxMin[1] - maxMin[0] + 1;
    vector<int> ans(len, 0);

    queue<vPair> que;
    que.push(vPair(root, -maxMin[0]));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();

            ans[rp.hl] = rp.node->val;

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1));
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1));
        }
    }
    return ans;
}

// Diagonal Order Of A Binarytree - clockwise
vector<vector<int>> diagonalOrder(TreeNode *root){
    if(root == nullptr) return {};
    queue<TreeNode*> que;
    vector<vector<int>> ans;

    que.push(root);

    while(que.size() != nullptr){
        int size = que.size();
        vector<int> smallAns;
        while(size-- > 0){
            TreeNode* rn = que.front(); que.pop();

            while(rn != nullptr){
                smallAns.push_back(rn->val);
                if(rn->left != nullptr) que.push(rn->left);

                rn = rn->right;
            }
        }
        ans.push_back(smallAns);
    }
    return ans;
}

// Diagonal Order Of A Binarytree - anticlockwise
vector<vector<int>> diagonalOrder(TreeNode *root){
    if(root == nullptr) return {};
    queue<TreeNode*> que;
    vector<vector<int>> ans;

    que.push(root);

    while(que.size() != nullptr){
        int size = que.size();
        vector<int> smallAns;
        while(size-- > 0){
            TreeNode* rn = que.front(); que.pop();

            while(rn != nullptr){
                smallAns.push_back(rn->val);
                if(rn->right != nullptr) que.push(rn->right);

                rn = rn->left;
            }
        }
        ans.push_back(smallAns);
    }
    return ans;
}

////////////////////////////////////////////======================================================

// 543. Diameter of Binary Tree
int diameterOfBinaryTree_01(TreeNode* root) {
    if(root == nullptr) return -1;

    int leftDia = diameterOfBinaryTree_01(root->left);
    int rightDia = diameterOfBinaryTree_01(root->right);

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return max(max(leftDia, rightDia), leftHeight + rightHeight + 2);
} 

// 2nd method
// ans[] = {dia, height};
vector<int> diameterOfBinaryTree_02(TreeNode* root){
    if(root == nullptr) return {-1, -1};

    vector<int> leftAns = diameterOfBinaryTree_02(root->left);
    vector<int> rightAns = diameterOfBinaryTree_02(root->right);

    vector<int> ans(2, 0);

    ans[0] = max(max(leftAns[0], rightAns[0]), leftAns[1] + rightAns[1] + 2);
    ans[1] = max(leftAns[1], rightAns[1]) + 1;

    return ans;
}

// 3rd method
// using diameter as reference
int maxDia = -(int)1e9;
int diameterOfBinaryTree_03(TreeNode* root){
    if(root == nullptr) return -1;

    int lh = diameterOfBinaryTree_03(root->left);
    int rh = diameterOfBinaryTree_03(root->right);

    maxDia = max(maxDia, lh + rh + 2);

    return max(lh, rh) + 1;
}

int diameterOfBinaryTree(TreeNode* root){
    if(root == nullptr) return -1;
    // vector<int> ans(2, 0);
    // return diameterOfBinaryTree_02(root)[0];
    // diameterOfBinaryTree_01(root);   

    diameterOfBinaryTree_03(root);
    return maxDia;
}

// node to root path
bool nodeToRootPath(TreeNode* root, TreeNode* data, vector<TreeNode*> &arr){
    if(root == nullptr) return false;

    if(root == data){
        arr.push_back(root);
        return true;
    }
    bool flag = false;
    
    flag = nodeToRootPath(root->left, data, arr) || nodeToRootPath(root->right, data, arr);

    if(flag) 
        arr.push_back(root);
    
    return flag;
}

// k down
void kDown(TreeNode* root, TreeNode* block, int k, vector<TreeNode*> &arr){
    if(root == nullptr || k < 0 || root == block) return;
    
    if(k == 0){
        arr.push_back(root);
        return;
    }

    kDown(root->left, block, k - 1, arr);
    kDown(root->right, block, k - 1, arr);
}

// 863. All Nodes Distance K in Binary Tree
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    if(root == nullptr) return {};
    vector<TreeNode*> nodeToRoot;
    nodeToRootPath(root, target, nodeToRoot);

    vector<int> ans;
    TreeNode* blockNode = nullptr;
    for(int i = 0; i < nodeToRoot.size(); i++){
        kDown(nodeToRoot[i], blockNode, k - i, ans);
        blockNode = nodeToRoot[i];
    }
    return ans;
}

// method 2

// w.r.t edge
int nodeToRootDistance(TreeNode* root, TreeNode* data){
    if(root == nullptr) return -1;

    if(root == data) return 0;

    int lans = nodeToRootDistance(root->left, data);
    if(lans != -1)
        return lans + 1;
    

    int rans = nodeToRootDistance(root->right, data);
    if(rans != -1)
        return rans + 1; 

    return -1;
}

int distanceK2_(TreeNode* root, TreeNode* target, int k, vector<int> &ans) {
    if(root == nullptr) return -1;

    if(root == target){
        kDown(root, nullptr, k, ans);
        return 1;
    }

    int lans = distanceK2_(root->left, target, k, ans);
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

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    if(root == nullptr) return {};
    vector<int> ans;
    distanceK2_(root, target, k, ans);
    return ans;
}


int main()
{
    return 0;
}
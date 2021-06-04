#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>

using namespace std;

class TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(){};

    TreeNode(int val){
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// level order traversal
void levelOrderTraversal(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() != 0){
        TreeNode* rn = que.front(); que.pop();
        cout << rn->val << " ";

        if(rn->left != nullptr) que.push(rn->left);
        if(rn->right != nullptr) que.push(rn->right);
    }
}

// level order traversal LINEWISE
void levelOrderTraversalLinewise_01(TreeNode* root){
    queue<TreeNode*> que;
    queue<TreeNode*> childQue;
    que.push(root);

    int level = 0;
    cout << "Level " << level << " -> ";

    while(que.size() != 0){
        TreeNode* rn = que.front(); que.pop();
        cout << rn->val << " ";

        if(rn->left != nullptr) childQue.push(rn->left);
        if(rn->right != nullptr) childQue.push(rn->right);

        if(que.size() == 0){
            if(childQue.size() == 0){
                cout << endl;
                cout << "Level " << ++level << " -> ";
            }
            queue<TreeNode*> temp = que;
            que = childQue;
            childQue = temp;
        }        
    }
}

void levelOrderTraversalLinewise_02(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);
    int level = 0;

    while(que.size() != 0){
        int size = que.size();
        cout << "Level " << level++ << " -> ";
        while(size--){
            TreeNode* rn = que.front(); que.pop();
            cout << rn->val << " ";

            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
        cout << endl;
    }
}

// 102. Binary Tree Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    if(root == nullptr) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() != 0){
        int size = que.size();
        vector<int> smallAns;
        while(size-- > 0){
            TreeNode* rn = que.front(); que.pop();
            smallAns.push_back(rn->val);

            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
        ans.push_back(smallAns);
    }        
    return ans;
}

// left view
void leftView(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() != 0){
        int size = que.size();
        cout << que.front()->val << endl;
        while(size-- > 0){
            TreeNode* rn = que.front(); que.pop();
            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
    }
}

// right view
void rightView(TreeNode* root){
    queue<TreeNode*> que;
    que.push(root);

    while(que.size() != 0){
        int size = que.size();
        cout << que.back()->val << endl;
        while(size-- > 0){
            TreeNode* rn = que.front(); que.pop();
            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
    }
}

// 199. Binary Tree Right Side View
vector<int> rightSideView(TreeNode* root) {
    if(root == nullptr) return {};
    queue<TreeNode*> que;
    que.push(root);
    vector<int> ans;
        
    while(que.size() != 0){
        int size = que.size();
        ans.push_back(que.back()->val);
        while(size-- > 0){
            TreeNode* rn = que.front(); que.pop();
            if(rn->left != nullptr) que.push(rn->left);
            if(rn->right != nullptr) que.push(rn->right);
        }
    }
    return ans;
}

// width of binary tree
void widthOfTree_(TreeNode* root, int hl, vector<int>& minMax){
    if(root == nullptr) return;

    minMax[0] = min(minMax[0], hl); // hl = horizontal level
    minMax[1] = max(minMax[1], hl);

    widthOfTree_(root->left, hl - 1, minMax);
    widthOfTree_(root->right, hl + 1, minMax);
}

int widthOfTree(TreeNode* node){
    vector<int> minMax(2, 0);   // {minHL, maxHL}
    widthOfTree_(root, 0, minMax);
    int width = minMax[1] - minMax[0] + 1;
    return width;
}

// vertical order pair
class vPair{
public:
    TreeNode* node = nullptr;
    int hl = 0;

    vPair(TreeNode* node, int hl){  
        this->node = node;
        this->hl = hl;
    }
};

vector<vector<int>> verticalOrderTraversal(TreeNode* root){
    queue<vPair> que;
    unordered_map<int, vector<int>> map;
    int minHL = 0, maxHL = 0;
    vector<vector<int>> ans;

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

    for(int i = minHL; i <= maxHL; i++){
        ans.push_back(map[i]);
    }
    return ans;
}

// 2nd method
void width(TreeNode* root, int hl, vector<int>& ans){
    if(root == nullptr) return;

    ans[0] = min(ans[0], hl);
    ans[1] = max(ans[1], hl);

    width(root->left, hl - 1, ans);
    width(root->right, hl + 1, ans);
}


vector<vector<int>> verticalOrderTraversal_2(TreeNode* root){
    if(root == nullptr) return {};

    vector<int> minMax(2,0);
    width(root, 0, minMax);
    int len = minMax[1] - minMax[0] + 1;
    vector<vector<int>> ans(len);

    queue<vPair> que;
    que.push(vPair(root, abs(minMax[0])));   // we always start from the min value of tree, i.e (left side width)

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();

            int hl = rp.hl; // storing ans
            TreeNode* node = rp.node;   // storing ans

            ans[hl] += node->val;   // storing ans

            // checking for left child and right child
            if(node->left != nullptr) que.push(vPair(node->left, hl - 1));
            if(node->right != nullptr) que.push(vPair(node->right, hl + 1));
        }
    }
    return ans;
}

// Vertical Order Sum Of A Binarytree
vector<int> verticalOrderSum(TreeNode *root)
{
    vector<int> minMax(2, 0);
    width(root, 0, minMax);
    int len = minMax[1] - minMax[0] + 1;

    vector<int> ans(len, 0);

    queue<vPair> que;

    que.push(vPair(root, abs(minMax[0])));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();  // pickup pair and pop it from queue

            ans[rp.hl] += rp.node->val; // make answer

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1)); // call left child
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1)); // call right child
        }
    }
    return ans;
}

// Top View Of A Binarytree
vector<int> TopView(TreeNode *root){
    vector<int> minMax(2, 0);
    width(root, 0, minMax);
    int len = minMax[1] - minMax[0] + 1;

    vector<int> ans(len, -(int)1e9);

    queue<vPair> que;

    que.push(vPair(root, abs(minMax[0])));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();  // pickup pair and pop it from queue

            if(ans[rp.hl] == -(int)1e9) ans[rp.hl] = rp.node->val; // make answer

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1)); // call left child
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1)); // call right child
        }
    }
    return ans;
}

// Bottom View Of A Binarytree
vector<int> BottomView(TreeNode *root){
    vector<int> minMax(2, 0);
    width(root, 0, minMax);
    int len = minMax[1] - minMax[0] + 1;

    vector<int> ans(len, 0);

    queue<vPair> que;

    que.push(vPair(root, abs(minMax[0])));

    while(que.size() != 0){
        int size = que.size();
        while(size-- > 0){
            vPair rp = que.front(); que.pop();  // pickup pair and pop it from queue

            ans[rp.hl] = rp.node->val; // make answer

            if(rp.node->left != nullptr) que.push(vPair(rp.node->left, rp.hl - 1)); // call left child
            if(rp.node->right != nullptr) que.push(vPair(rp.node->right, rp.hl + 1)); // call right child
        }
    }
    return ans;
}


// Diagonal Order Of A Binarytree
vector<vector<int>> diagonalOrder(TreeNode *root){
    if(root == nullptr) return {};
    queue<TreeNode*> que;
    vector<vector<int>> ans;
    
    que.push(root);

    while(que.size() != 0){     // diagonal no. 
        int size = que.size();
        vector<int> smallAns;
        while(size-- > 0){  // here size = no. of components, help to traverse each component of that particular diagonal
            TreeNode* rn = que.front(); que.pop();

            while(rn != nullptr){   // traverse each component
                smallAns.push_back(rn->val);
                if(rn->left != nullptr) que.push(rn->left);

                rn = rn->right;
            }
        }
        ans.push_back(smallAns);
    }
    return ans;
}

// Diagonal Order (anti-clock Wise) Of A Binarytree
vector<vect or<int>> diagonalOrder(TreeNode *root){
    if(root == nullptr) return {};
    queue<TreeNode*> que;
    que.push(root);

    vector<vector<int>> ans;

    while(que.size() != 0){     // diagonal no. 
        int size = que.size();
        vector<int> smallAns;
        while(size-- > 0){  // here size = no. of components, help to traverse each component of that particular diagonal
            TreeNode* rn = que.front(); que.pop();

            while(rn != nullptr){   // traverse each component
                smallAns.push_back(rn->val);
                if(rn->right != nullptr) que.push(rn->right);

                rn = rn->left;
            }
        }
        ans.push_back(smallAns);
    }
    return ans;
}


int main(){
    return 0;
}
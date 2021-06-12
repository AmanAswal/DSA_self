#include<iostream>
#include<vector>

using namespace std;

class Node{
public:
    int val = 0;
    vector<Node*> childs;

    Node(int val){
        this->val = val;
    }
}

int size(Node* root){
    // if(root == null) return 0;
    int sz = 0;
    for(Node* child : root->childs){
        sz += size(child);
    }
    return sz + 1;
}

// on the basis of edge
int height(Node* root){
    int h = -1;
    for(Node* child : root->childs){
        h = max(h, height(child));
    }
    return h + 1;
}

int maximum(Node* node){
    int maxEle = node->val;
    for(Node* child : childs){
        maxEle = max(maxEle, maximum(child));
    }
    return maxEle;
}

bool find(Node* node, int data){
    if(node->val == data) return true;

    for(Node* child : childs){
        if(find(child, data)) return true;
    }
    return false;
}

//node to root path
bool nodeToRootPath(Node* root, int data, vector<Node*> ans){
    if(root->val == data){
        ans.push_back(root);
        return true;
    }

    bool res = false;
    for(Node* child : root->childs){
        res = res || nodeToRootPath(root, data, ans);
        // if(res) break;
    }

    if(res) 
        ans.push_back(root);

    return res;
}

vector<Node*> nodeToRootPath(Node* root){
    vector<Node*> ans;

    nodeToRootPath(root, data, ans);
    return ans;
}

// LCA 
Node* LCA(Node* node, int d1, int d2){
    vector<Node*> l1;
    vector<Node*> l2;

    nodeToRootPath(node, d1, l1);
    nodeToRootPath(node, d2, l2);

    int i = l1.size() - 1;
    int j = l2.size() - 1;
    Node* LCA = nullptr;

    while(i >= 0 && j >= 0){
        if(l1[i] != l2[j]) break;

        LCA = l1[i];
        i--;
        j--;
    }
    return LCA;
}

// // BURNING TREE
// void kDown(Node* root, Node blockNode, int time, vector<vector<int>> &ans){
//     if(root == blockNode) return;

//     ans[time].push_back(root->val);

//     for(Node* child: root->childs){

//     }
// }

// vector<vector<int>> distanceK(Node* root, int target, int k){
//     vector<Node*> list;
//     nodeToRootPath(root, target, list);

//     vector<vector<int>> ans;
//     Node* blockNode = nullptr;

//     for(int i = 0; i < list.size(); i++){

//     }
//     return ans;
// }

// LEVEL ORDER TRAVERSAL
// RIGHT VIEW
// LEFT VIEW
// ONLY


// mirror
bool isMirror(Node* node1, Node* node2){
    if(node1->childs.size() != node2->childs.size()) return false;

    if(node1->val != node2->val) return false;

    for(int i=0, j = node1.childs.size() - 1; j >= 0; i++, j--){
        Node* child1 = node1->childs[i];
        Node* child2 = node2->childs[j];

        if(!isMirror(child1, child2))
            return false;
    }
    return true;
}

// isomorphic
bool isIsomorphic(Node* node1, Node* node2){
    if(node1->childs.size() != node2->childs.size()) return false;

    for(int i=0, j = node1.childs.size() - 1; j >= 0; i++, j--){
        Node* child1 = node1->childs[i];
        Node* child2 = node2->childs[j];

        if(!isIsomorphic(child1, child2))
            return false;
    }
    return true;
}

// flattern
Node* flattern(Node* node){

    int n = node->childs.size();
    Node* lchild = node->childs[n - 1];
    Node* gTail = flattern(lchild);

    for(int i = n - 2; i >= 0; i--){
        Node* tempTail = flattern(node->childs[i]);
        tempTail->childs.push_back(node->childs[i + 1]);
        node->childs.pop
    }
}

// diagonal

int main(){
    return 0;
}
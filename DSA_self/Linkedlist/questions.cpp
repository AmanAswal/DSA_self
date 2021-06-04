#include<iostream>
#include<vector>

using namespace std;

class ListNode{
public:
    int val = 0;
    ListNode* next = nullptr;

    ListNode(int val){
        this->val = val;
    }
};


//  138. Copy List with Random Pointer

// method 1: using hashmap, tc : O(2n), sc : O(n)
Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> map;
        Node* curr = head;
        
        Node* nHead = new Node(-1);
        Node* prev = nHead;
        
        while(curr != nullptr){
            Node* node = new Node(curr->val);
            prev->next = node;
            
            map[curr] = node;           
            
            prev = prev->next;
            curr = curr->next;
        }
        nHead = nHead->next;
        
        Node* c1 = head;
        Node* c2 = nHead;
        
        while(c1 != nullptr){
            c2->random = (c1->random != nullptr) ? map[c1->random] : nullptr;
            
            c1 = c1->next;
            c2 = c2->next; 
        }
        return nHead;
    }

int main(){
    return 0;
}
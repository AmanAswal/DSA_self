#include<iostream>
using namespace std;

class ListNode{
public:
    int val = 0;
    ListNode* next = nullptr;

    ListNode(int val){
        this->val = val;
    }
};

// global
ListNode* head = nullptr;

ListNode* addFirst(int val){
    ListNode* node = new ListNode(val);
    if(head == nullptr){
        node = head;
    }
    else{
        node->next = head;
        head = node;
    }
    return head;
}

ListNode* addLast(int val){
    ListNode* node = new ListNode(val);
    if(head == nullptr){
        node = head;
    }
    else{
        ListNode* last = head;
        while(last->next != nullptr)
            last = last->next;
        
        last->next = node;
    }
    return head;
}


ListNode* removeFirst(){
    if(head == nullptr) return nullptr;

    ListNode* nHead = head;
    nHead = head->next;

    head->next = nullptr;
    delete head;

    return nHead;
}

ListNode* removeLast(){
    if(head == nullptr) return nullptr;

    ListNode* curr = head;
    while(curr->next->next != nullptr)
        curr = curr->next;
    
    ListNode* temp = curr->next;
    curr->next = nullptr;
    delete temp;
    return head;
}

int getFirst(ListNode* head){
    if(head == nullptr) return -1;
    return head->val;
}

int getLast(ListNode* head){
    if(head == nullptr) return -1;
    ListNode* curr = head;
    while(curr->next != nullptr) curr = curr->next;

    return curr->val;
}

void display(ListNode* head){
    if(head == nullptr) return;

    ListNode* curr = head;
    while(curr != nullptr){
        cout << curr->val << " ";
        curr = curr->next;
    }
}

int size(ListNode* head){
    if(head == nullptr) return 0;

    int count = 0;
    ListNode* curr = head;

    while(curr != nullptr){
        count++;
        curr = curr->next;
    }
    return count;
}

int main(){

}





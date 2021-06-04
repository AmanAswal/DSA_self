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

// Reverse A Linkedlist
ListNode *reverse(ListNode *head){
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* curr = head;
    ListNode* prev = nullptr;
    ListNode* forw = nullptr;

    while(curr != nullptr){
        forw = curr->next;  //backup
        
        curr->next = prev; // connection
        
        prev = curr;
        curr = forw;    // move
    }
    return prev;
}

// Middle Of A Linked List
ListNode *midNode(ListNode *head){
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* slow = head;
    ListNode* fast = head;

    while(fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Palindrome Linkedlist
bool isPalindrome(ListNode *head){
    if(head == nullptr || head->next == nullptr) return true;

    ListNode* mid = midNode(head);
    ListNode* nHead = mid->next;
    mid->next = nullptr;

    nHead = reverse(nHead);

    ListNode* c1 = head;
    ListNode* c2 = nHead;
    ListNode* f1 = nullptr;
    ListNode* f2 = nullptr;

    bool res = true;
    while(c1 != nullptr && c2 != nullptr){
        f1 = c1->next;    // backup
        f2 = c2->next;
        

        if(c1->val != c2->val){
            res = false;
            break;
        }

        c1 = f1;
        c2 = f2;    
    }

    // re-constructing original list
    nHead = reverse(nHead);
    mid->next = nHead;
    return res;
}

// Fold Of Linkedlist
void fold(ListNode *head){
    if(head == nullptr || head->next == nullptr) return;

    ListNode* mid = midNode(head);
    ListNode* nHead = mid->next;
    mid->next = nullptr;

    nHead = reverse(nHead);

    ListNode* c1 = head;
    ListNode* c2 = nHead;
    ListNode* f1 = nullptr;
    ListNode* f2 = nullptr;

    while(c1 != nullptr && c2 != nullptr){
        f1 = c1->next;
        f2 = c2->next;

        c1->next = c2;
        c2->next = f1;

        c1 = f1;
        c2 = f2;
    }
}

// Unfold Of Linkedlist
void unfold(ListNode *head){
    if(head == nullptr || head->next == nullptr) return;
    ListNode* nHead = head->next;
    ListNode* c1 = head;
    ListNode* c2 = nHead;

    while(c2 != nullptr && c2->next != nullptr){
        c1->next = c2->next;
        c1 = c1->next;

        c2->next = c1->next;
        c2 = c2->next;
    }
    nHead = reverse(nHead);
    c1->next = nHead;
}

// Merge Two Sorted Linkedlist
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2){
    if(l1 == nullptr || l2 == nullptr)
        return (l1 == nullptr) ? l2 : l1;

    ListNode* dummy = new ListNode(-(int)1e8);
    ListNode* itr = dummy;
    ListNode* c1 = l1;
    ListNode* c2 = l2;

    while(c1 != nullptr && c2 != nullptr){
        if(c1->val <= c2->val){
            itr->next = c1;
            c1 = c1->next;
        }
        else{
            itr->next = c2;
            c2 = c2->next;
        }
        itr = itr->next;
    }

    itr->next = (c1 == nullptr) ? c2 : c1;

    return dummy->next;
}

// Mergesort Linkedlist
ListNode *mergeSort(ListNode *head){
    if(head == nullptr || head->next == nullptr) return head;
    
    ListNode* mid = midNode(head);
    ListNode* nHead = mid->next;
    mid->next = nullptr;

    ListNode* l1 = mergeSort(head);
    ListNode* l2 = mergeSort(nHead);

    return mergeTwoLists(l1, l2); 
}

// Merge K Sorted Linkedlist
ListNode *mergeKLists_(vector<ListNode *> &lists, int si, int ei){
    if(si > ei) return nullptr;
    if(si == ei) return lists[si];

    int mid = (si + ei) / 2;

    ListNode* l1 = mergeKLists_(lists, si, mid);
    ListNode* l2 = mergeKLists_(lists, mid + 1, ei);

    return mergeTwoLists(l1, l2);
}

ListNode *mergeKLists(vector<ListNode *> &lists){
    if(lists.size() == 0) return nullptr;
    int n = lists.size();

    return mergeKLists_(list, 0, n - 1);
}


// Remove Nth Node From End Of Linkedlist
ListNode *removeNthFromEnd(ListNode *head, int n){
    if(head == nullptr || head->next == nullptr || n == 0) return nullptr;

    ListNode* dummy = new ListNode(-1);
    dummy->next= head;
    ListNode* first = dummy;
    ListNode* sec = dummy;

    while(n-- > 0){
        first = first->next;
    }

    // delete head wali condition
    if(first->next == nullptr){
        dummy->next = head->next;
        head->next = nullptr;
        delete head;
    }
    else{
        while(first->next != nullptr){
            first = first->next;
            sec = sec->next;
        }

        ListNode* temp = sec->next;
        sec->next = temp->next;
        temp->next = nullptr;
        delete temp;
    }
    return dummy->next;
}

// Segregate Even And Odd Nodes In A Link List
ListNode *segregateEvenOdd(ListNode *head){
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* oh = nullptr;
    ListNode* eh = nullptr;
    ListNode* o = nullptr;
    ListNode* e = nullptr;

    ListNode* curr = head;

    while(curr != nullptr){
        if(curr->val % 2 != 0){ // if odd
            if(oh == nullptr) {
                oh = curr;
                o = oh;
            }
            else{
                o->next = curr;
                o = o->next;
            }
        }
        else{                   // if even
            if(eh == nullptr){
                eh = curr;
                e = eh;
            }
            else{
                e->next = curr;
                e = e->next;
            }
        }
        curr = curr->next;
    }

    // if only odd
    if(eh == nullptr) return oh;

    // if only even
    if(oh == nullptr) return eh;

    o->next = nullptr;
    e->next = oh;
    return eh;
}

// Is Cycle Present In Linkedlist
bool isCyclePresentInLL(ListNode *head){
    if(head == nullptr || head->next == nullptr) return false;
    
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) return true;
    }
    return false;
}

// Cycle Node In Linkedlist
ListNode *CycleNode(ListNode *head){
    if(head == nullptr || head->next == nullptr) return nullptr;
    ListNode* slow = head;
    ListNode* fast = head;

    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) break;
    }

    if(slow != fast) return nullptr;

    slow = head;
    while(slow != fast){
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
 
// length of linked list
int lengthOfLL(ListNode* head){
    if(head == nullptr) return 0;
    int len = 0;
    ListNode* curr = head;
    while(curr != nullptr){
        curr = curr->next;
        len++;
    }
    return len;
}

// Intersection Node In Two Linkedlist Using Difference Method
ListNode *IntersectionNodeInTwoLL(ListNode *headA, ListNode *headB){
    if(headA == nullptr || headB == nullptr) 
        return nullptr;

    int lenA = lengthOfLL(headA);
    int lenB = lengthOfLL(headB);

    ListNode *biggerList = lenA > lenB ? headA : headB;
    ListNode *smallerList = lenA > lenB ? headB : headA;

    int diff = max(lenA, lenB) - min(lenA, lenB);
    
    while (diff-- > 0) biggerList = biggerList->next;

    while(biggerList != smallerList){
        biggerList = biggerList->next;
        smallerList = smallerList->next;
    }
    return biggerList;
}

// Intersection Node In Two Linkedlist Using Floyad Cycle Method
ListNode *IntersectionNodeInTwoLL(ListNode *headA, ListNode *headB){
    if(headA == nullptr || headB == nullptr) 
        return nullptr;
    
    ListNode* curr = headA;
    
    while(curr->next != nullptr) curr = curr->next;

    curr->next = headB;

    ListNode* ans = CycleNode(headA);

    curr->next = nullptr;
    return ans;
}

// Intersection of Two Linked Lists - METHOD 3
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if(headA == nullptr || headB == nullptr) 
        return nullptr;
    
    ListNode* a = headA;
    ListNode* b = headB;

    while(a != b){
        if(a->next == nullptr && b->next == nullptr) return nullptr;
        a = (a->next == nullptr) ? headB : a->next;
        b = (b->next == nullptr) ? headA : b->next;
    }
    return a;
}

// Add Two Linkedlist
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2){
    if(l1 == nullptr || l2 == nullptr) 
        return (l1 == nullptr) ? l2 : l1;

    ListNode* dummy = new ListNode(-1);
    ListNode* itr = dummy;

    l1 = reverse(l1);
    l2 = reverse(l2);

    ListNode* c1 = l1;
    ListNode* c2 = l2;
    int carry = 0;

    while(c1 != nullptr || c2 != nullptr || carry != 0){
        int sum = 0;
        if(c1 != nullptr){
            sum += c1->val;
            c1 = c1->next;
        }

        if(c2 != nullptr){
            sum += c2->val;
            c2 = c2->next;
        }
        
        sum += carry;
        int value = sum % 10;
        ListNode* node = new ListNode(value);
        itr->next = node;
        itr = itr->next;
        carry = sum / 10;
    }

    ListNode* nHead = dummy->next;
    nHead = reverse(nHead);
    return nHead;
}

// Subtract Two Linkedlist
ListNode *subtractTwoNumbers(ListNode *l1, ListNode *l2){
    if(l1 == nullptr || l2 == nullptr) 
        return l1 == nullptr ? l2 : l1;

    l1 = reverse(l1);
    l2 = reverse(l2);

    ListNode* dummy = new ListNode(-1);
    ListNode* itr = dummy;
    ListNode* c1 = l1;
    ListNode* c2 = l2;

    int borrow = 0;

    while(c1 != nullptr){
        int diff = borrow + c1->val - ((c2 != nullptr) ? c2->val : 0);
        if(diff < 0){
            borrow = -1;
            diff += 10;
        }
        else borrow = 0;

        itr->next = new ListNode(diff);
        itr = itr->next;

        c1 = c1->next;
        if(c2 != nullptr) c2 = c2->next;
    }

    ListNode* nHead = dummy->next;
    nHead = reverse(nHead);
    return nHead;
}

// addLast
ListNode* th = nullptr;
ListNode* tt = nullptr;

void addLast(ListNode* node){
    if(tt == nullptr){
        th = node;
        tt = node;
    }
    else{
        tt->next = node;
        tt = node;
    }
}

// Remove Duplicate From Sorted Linkedlist
ListNode *removeDuplicates(ListNode *head){
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* curr = head;

    while(curr != nullptr){
        ListNode* forw = curr->next;
        curr->next = nullptr;
        if(tt == nullptr || curr->val != tt->val){
            
            addLast(curr);
        }
        curr = forw;
    }
    return th;
}

// Remove All Duplicates From Sorted Linkedlist - II
ListNode *removeDuplicates(ListNode *head){
    if(head == nullptr || head->next == nullptr) return head;

    ListNode* dummy = new ListNode(-1);
    ListNode* itr = dummy;
    itr->next = head;
    ListNode* curr = head->next;

    while(curr != nullptr){
        bool isDuplicate = false;

        while(curr != nullptr && curr->val == itr->next->val){
            isDuplicate = true;
            curr = curr->next;
        }

        if(isDuplicate) itr->next = curr;
        else itr = itr->next;

        if(curr != nullptr) curr = curr->next;
    }
    return dummy->next;
}

// addFirst
ListNode* th = nullptr;
ListNode* tt = nullptr;

void addFirst(ListNode* node){
    if(th == nullptr){
        th = node;
        tt = node;
    }
    else{
        node->next = th;
        th = node;
    }
}

// Reverse Node Of Linkedlist In K Group
ListNode *reverseInKGroup(ListNode *head, int k){
    if(head == nullptr || head->next == nullptr || k == 0) // handle edge cases

    ListNode* oh = nullptr;
    ListNode* ot = nullptr;
    ListNode* curr = head;

    int len = lengthOfLL(head);

    while(len >= k){
        int tempK = k;
        while(temp-- > 0){
            ListNode* forw = curr->next;
            curr->next = nullptr;
            addFirst(curr);
            curr = forw;
        }

        if(oh == nullptr && ot == nullptr){
            oh = oh;
            ot = tt;
        }
        else{
            ot->next = th;
            ot = tt;
        }

        th = nullptr;
        tt = nullptr;
        len -= k;
    }
    ot->next = curr;
    return oh;
}


int main(){
    return 0;
}
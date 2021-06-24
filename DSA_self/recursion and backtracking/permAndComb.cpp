#include<iostream>
#include<vector>

using namespace std;

int coinChangePermutationInfi(vector<int> &arr, int target, string ans){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;

    for(int coin : arr){
        if(target - coin >= 0)
            count += coinChangePermutationInfi(arr, target - coin, ans + to_string(coin));
    }
    return count;
}

int coinChangePermutation(vector<int> &arr, int target, string ans){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;

    for(int i = 0; i < arr.size(); i++){
        int coin = arr[i];
    
        if(target - coin >= 0 && arr[i] > 0){
            arr[i] = -arr[i];
            count += coinChangePermutation(arr, target - coin, ans + to_string(coin));
            arr[i] = -arr[i];
        }   
    }
    return count;
}   

int coinChangeCombinationInfi(vector<int> &arr, int target, string ans, int idx){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;

    for(int i = idx; i < arr.size(); i++){
        if(target - arr[i] >= 0)
            count += coinChangeCombinationInfi(arr, target - arr[i], ans + to_string(arr[i]), i);
    }

    return count;
}

int coinChangeCombination(vector<int> &arr, int target, string ans, int idx){
    if(target == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;

    for(int i = idx; i < arr.size(); i++){
        if(target - arr[i] >= 0)
            count += coinChangeCombinationInfi(arr, target - arr[i], ans + to_string(arr[i]), i + 1);
    }

    return count;
}

// subseq method -> 2^n
int coinChangeCombinationInfiSubSeq(vector<int> &arr, int idx, int tar, string ans){
    if(idx == arr.size() || tar == 0){
        if(tar == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    
    if(tar - arr[idx] >= 0)
        count += coinChangeCombinationInfiSubSeq(arr, idx, tar - arr[idx], ans + to_string(arr[idx]));
    
    count += coinChangeCombinationInfiSubSeq(arr, idx + 1, tar, ans);

    return count;
}

int coinChangeCombinationSubSeq(vector<int> &arr, int idx, int tar, string ans){
    if(idx == arr.size() || tar == 0){
        if(tar == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    
    if(tar - arr[idx] >= 0)
        count += coinChangeCombinationInfiSubSeq(arr, idx + 1, tar - arr[idx], ans + to_string(arr[idx]));
    
    count += coinChangeCombinationInfiSubSeq(arr, idx + 1, tar, ans);

    return count;
}

int coinChangePermutationInfiSubSeq(vector<int> &arr, int idx, int tar, string ans){
    if(idx == arr.size() || tar == 0){
        if(tar == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    
    if(tar - arr[idx] >= 0)
        count += coinChangeCombinationInfiSubSeq(arr, 0, tar - arr[idx], ans + to_string(arr[idx]));
    
    count += coinChangeCombinationInfiSubSeq(arr, idx + 1, tar, ans);

    return count;
}

int coinChangePermutationSubSeq(vector<int> &arr, int idx, int tar, string ans){
    if(idx == arr.size() || tar == 0){
        if(tar == 0){
            cout << ans << endl;
            return 1;
        }
        return 0;
    }
    int count = 0;
    int ele = arr[idx];
    if(tar - arr[idx] >= 0 && arr[idx] > 0){
        arr[idx] = -arr[idx];
        count += coinChangeCombinationInfiSubSeq(arr, 0, tar - ele, ans + to_string(ele));
        arr[idx] = -arr[idx];
    }
    
    count += coinChangeCombinationInfiSubSeq(arr, idx + 1, tar, ans);

    return count;
}

int main(){
    vector<int> arr{2,3,5,7};
    int target = 10;

    // cout << coinChangePermutationInfi(arr, target, "");
    // cout << coinChangePermutation(arr, target, "");
    // cout << coinChangeCombinationInfi(arr, target, "", 0);
    cout << coinChangeCombination(arr, target, "", 0);
}
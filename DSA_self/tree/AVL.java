public class AVL{

    public static class TreeNode{
        int val = 0;
        TreeNode left = null;
        TreeNode right = null;

        int height = 0;
        int bal = 0;

        TreeNode(int val){
            this.val = val;
        }

        TreeNode(){}
    }

    public static TreeNode rightRotation(TreeNode A){   // O(1)
        TreeNode B = A.left;
        TreeNode BkaRight = B.right;

        B.right = A;
        A.left = BkaRight;

        updateHeightAndBalance(A);
        updateHeightAndBalance(B);

        return B;
    }

    public static TreeNode leftRotation(TreeNode A){ // O(1)

        TreeNode B = A.right;
        TreeNode BkaLeft = B.left;

        B.left = A;
        A.right = BkaLeft;

        updateHeightAndBalance(A);
        updateHeightAndBalance(B);

        return B;
    }

    public static void updateHeightAndBalance(TreeNode node){   // O(1)
        if(node == null) return;
        int lh = -1;
        int rh = -1;

        if(node.left != null) lh = node.left.height;
        if(node.right != null) rh = node.right.height;

        int bal = lh - rh;
        int height = Math.max(lh, rh) + 1;

        node.height = height;
        node.bal = bal;
    }

    // this balances the tree
    public static TreeNode getRotation(TreeNode node){ // O(1)00
        updateHeightAndBalance(node);

        if(node.bal == 2){  // ll, lr
            if(node.left.bal == 1){ // ll
                return rightRotation(node);
            }
            else{   // lr
                node.left = leftRotation(node.left);
                return rightRotation(node);
            }
        }
        else if(node.bal == -2){    // rr, rl
            if(node.right.bal == -1){    // rr
                return leftRotation(node);
            }
            else{   // rl
                node.right = rightRotation(node.right);
                return leftRotation(node);
            }
        }
         
        return node;
    }

    // basic bst operations =======================================

    public static int maximumEle(TreeNode root){
        TreeNode curr = root;
        while(curr.right != null)
            curr = curr.right;
        
        return curr.val;
    }

    // insertion in bst
    public static TreeNode insertIntoBST(TreeNode root, int val) {
        if(root == null){
            return new TreeNode(val);
        }

        if(root.val > val)
            root.left = insertIntoBST(root.left, val);
        else
            root.right = insertIntoBST(root.right, val);

        return getRotation(root);
        // return root;
    }

    // deletion in bst
    public static TreeNode deleteNode(TreeNode root, int key) {
        if(root == null) return null;

        if(root.val > key)
            root.left = deleteNode(root.left, key);
        else if(root.val < key)
            root.right = deleteNode(root.right, key);
        else{   // found it
            if(root.left == null || root.right == null) // 1 child or 0 child
                return root.left != null ? root.left : root.right; 
               // two child 
            int leftMax = maximumEle(root.left);
            root.val = leftMax;

            root.left = deleteNode(root.left, leftMax);
            
        }
        return getRotation(root);
    }

    public static void display(TreeNode node){
        if(node == null) return;

        String str = ""; 
        str += node.left != null ? node.left.val + "" : ".";
        str += " <- " + node.val + " -> ";
        str += node.right != null ? node.right.val + "" : ".";
        
        System.out.println(str);

        display(node.left);
        display(node.right);
    }

    public static void main(String[] args){
        int[] arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

        TreeNode root = null;

        for(int ele : arr){
            root = insertIntoBST(root, ele);
        }

        display(root);
        System.out.println("================================");

        for(int i = arr.length - 1; i >= 0; i--){
            root = deleteNode(root, arr[i]);
            display(root);
            System.out.println("========");
        }

    }
}
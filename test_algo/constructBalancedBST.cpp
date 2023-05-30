#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* constructBalancedBST(vector<int>& nums, int start, int end) {
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    Node* root = new Node(nums[mid]);

    root->left = constructBalancedBST(nums, start, mid - 1);
    root->right = constructBalancedBST(nums, mid + 1, end);

    return root;
}

void inorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

int main() {
    vector<int> nums = {15, 50, 6, 7, 4, 5};
    
    // Сортируем числа в порядке возрастания
    sort(nums.begin(), nums.end());

    // Построение сбалансированного дерева
    Node* root = constructBalancedBST(nums, 0, nums.size() - 1);

    cout << "(a) Inorder (Left, Root, Right): ";
    inorderTraversal(root);
    cout << endl;

    cout << "(b) Preorder (Root, Left, Right): ";
    preorderTraversal(root);
    cout << endl;

    cout << "(c) Postorder (Left, Right, Root): ";
    postorderTraversal(root);
    cout << endl;

    return 0;
}

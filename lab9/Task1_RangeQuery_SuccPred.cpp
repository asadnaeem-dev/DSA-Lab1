// Lab 9 - Task 1: Range Query and Successor/Predecessor Finder using BST
// Asad Naeem - 541495 - BSDS 3A
//
// Builds a BST from the given sequence, then:
//   * prints the inorder traversal
//   * finds the inorder predecessor and successor of a key
//   * prints all keys in a range [low, high], recursively and iteratively,
//     counting the key comparisons each version makes

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        // duplicates are ignored
        return node;
    }

    void inorder(Node* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    // Recursive range query. Only descends into a subtree if it can hold
    // keys inside [low, high]. Every "<" / ">" / "<=" test on a key is counted.
    void rangeRecursive(Node* node, int low, int high, vector<int>& out, int& comparisons) const {
        if (node == nullptr) return;

        comparisons++;                       // low < node->key ?
        if (low < node->key)
            rangeRecursive(node->left, low, high, out, comparisons);

        comparisons++;                       // low <= key <= high ? (counted as one range test)
        if (low <= node->key && node->key <= high)
            out.push_back(node->key);

        comparisons++;                       // high > node->key ?
        if (high > node->key)
            rangeRecursive(node->right, low, high, out, comparisons);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int key) { root = insert(root, key); }

    void displayInorder() const {
        inorder(root);
        cout << endl;
    }

    bool contains(int key) const {
        Node* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) return true;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        return false;
    }

    // Inorder predecessor and successor of `key` in O(h), walking down from
    // the root. Works whether or not the key itself is present in the tree.
    void findPredSucc(int key, Node*& pred, Node*& succ) const {
        pred = succ = nullptr;
        Node* cur = root;
        while (cur != nullptr) {
            if (key < cur->key) {
                succ = cur;             // cur is a candidate successor
                cur = cur->left;
            } else if (key > cur->key) {
                pred = cur;             // cur is a candidate predecessor
                cur = cur->right;
            } else {
                // Key found: predecessor = max of left subtree,
                //            successor   = min of right subtree
                if (cur->left != nullptr) {
                    Node* t = cur->left;
                    while (t->right != nullptr) t = t->right;
                    pred = t;
                }
                if (cur->right != nullptr) {
                    Node* t = cur->right;
                    while (t->left != nullptr) t = t->left;
                    succ = t;
                }
                break;
            }
        }
    }

    vector<int> rangeQueryRecursive(int low, int high, int& comparisons) const {
        vector<int> out;
        comparisons = 0;
        rangeRecursive(root, low, high, out, comparisons);
        return out;
    }

    // Iterative range query: inorder traversal with an explicit stack,
    // pruning left subtrees that are entirely < low and stopping as soon
    // as a key > high is reached (all later keys are larger).
    vector<int> rangeQueryIterative(int low, int high, int& comparisons) const {
        vector<int> out;
        comparisons = 0;
        stack<Node*> st;
        Node* cur = root;

        while (cur != nullptr || !st.empty()) {
            // Go left, but only while the left side can still contain keys >= low
            while (cur != nullptr) {
                st.push(cur);
                comparisons++;               // low < cur->key ?
                if (low < cur->key)
                    cur = cur->left;
                else
                    cur = nullptr;           // left subtree is all < low, skip it
            }

            cur = st.top();
            st.pop();

            comparisons++;                   // cur->key > high ?
            if (cur->key > high) break;      // everything after this is out of range

            comparisons++;                   // cur->key >= low ?
            if (cur->key >= low)
                out.push_back(cur->key);

            cur = cur->right;
        }
        return out;
    }
};

void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    int sequence[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    int n = sizeof(sequence) / sizeof(sequence[0]);

    BST tree;
    cout << "===== Task 1: Range Query & Successor/Predecessor (BST) =====" << endl;
    cout << "Input sequence : ";
    for (int i = 0; i < n; i++) {
        cout << sequence[i] << " ";
        tree.insert(sequence[i]);
    }
    cout << endl << endl;

    // 1. Inorder traversal
    cout << "Inorder traversal : ";
    tree.displayInorder();
    cout << endl;

    // 2. Predecessor / Successor
    int keys[] = {40, 50, 20, 85};
    for (int key : keys) {
        Node *pred, *succ;
        tree.findPredSucc(key, pred, succ);
        cout << "Key = " << key << (tree.contains(key) ? "" : " (not in tree)") << endl;
        cout << "   Inorder Predecessor : " << (pred ? to_string(pred->key) : "None") << endl;
        cout << "   Inorder Successor   : " << (succ ? to_string(succ->key) : "None") << endl;
    }
    cout << endl;

    // 3 & 4. Range query, recursive vs iterative
    int ranges[][2] = {{30, 70}, {42, 62}, {10, 25}};
    for (auto& r : ranges) {
        int low = r[0], high = r[1];
        int recComp = 0, itComp = 0;
        vector<int> recResult = tree.rangeQueryRecursive(low, high, recComp);
        vector<int> itResult = tree.rangeQueryIterative(low, high, itComp);

        cout << "Range Query [" << low << ", " << high << "]" << endl;
        cout << "   Recursive result : ";
        printVector(recResult);
        cout << "   Iterative result : ";
        printVector(itResult);
        cout << "   Keys found       : " << recResult.size() << endl;
        cout << "   Comparisons -> Recursive: " << recComp
             << " | Iterative: " << itComp << endl << endl;
    }

    cout << "Analysis: both versions prune subtrees outside the range and run" << endl;
    cout << "in O(h + k) time (h = height, k = keys reported)." << endl;
    cout << " - Iterative stops as soon as a key > high is popped, so it makes" << endl;
    cout << "   fewer comparisons for narrow ranges ([42,62], [10,25])." << endl;
    cout << " - For a wide range ([30,70]) its extra per-node checks while" << endl;
    cout << "   pushing/popping make it slightly higher than recursive." << endl;
    cout << " - Iterative uses an explicit stack (no recursion overhead)." << endl;

    return 0;
}

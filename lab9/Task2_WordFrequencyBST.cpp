// Lab 9 - Task 2: Word Frequency Indexing using BST
// Asad Naeem - 541495 - BSDS 3A
//
// Every unique word (case-insensitive, punctuation stripped) is a node in a
// BST ordered alphabetically, holding its frequency count.
// displayByFrequency() builds a second BST keyed by (frequency desc, word asc)
// so the words come out sorted by frequency with an inorder traversal.

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

struct WordNode {
    string word;
    int count;
    WordNode* left;
    WordNode* right;
    WordNode(const string& w, int c = 1) : word(w), count(c), left(nullptr), right(nullptr) {}
};

class WordBST {
private:
    WordNode* root;       // alphabetical index
    int totalWords;
    int uniqueWords;

    // ---------- alphabetical BST ----------
    WordNode* insert(WordNode* node, const string& word) {
        if (node == nullptr) {
            uniqueWords++;
            return new WordNode(word);
        }
        if (word < node->word)
            node->left = insert(node->left, word);
        else if (word > node->word)
            node->right = insert(node->right, word);
        else
            node->count++;                     // already present -> bump frequency
        return node;
    }

    void inorderAlpha(WordNode* node) const {
        if (node == nullptr) return;
        inorderAlpha(node->left);
        cout << "   " << node->word;
        for (size_t i = node->word.size(); i < 10; i++) cout << ' ';
        cout << ": " << node->count << endl;
        inorderAlpha(node->right);
    }

    // ---------- frequency-ordered BST ----------
    // Ordering: higher count first; ties broken alphabetically.
    static bool comesBefore(int c1, const string& w1, int c2, const string& w2) {
        if (c1 != c2) return c1 > c2;
        return w1 < w2;
    }

    WordNode* insertByFreq(WordNode* node, const string& word, int count) {
        if (node == nullptr) return new WordNode(word, count);
        if (comesBefore(count, word, node->count, node->word))
            node->left = insertByFreq(node->left, word, count);
        else
            node->right = insertByFreq(node->right, word, count);
        return node;
    }

    // Copy every node of the alphabetical tree into the frequency tree
    void buildFreqTree(WordNode* node, WordNode*& freqRoot) {
        if (node == nullptr) return;
        freqRoot = insertByFreq(freqRoot, node->word, node->count);
        buildFreqTree(node->left, freqRoot);
        buildFreqTree(node->right, freqRoot);
    }

    void inorderFreq(WordNode* node, int& rank) const {
        if (node == nullptr) return;
        inorderFreq(node->left, rank);
        cout << "   " << (rank < 10 ? " " : "") << rank << ". " << node->word;
        rank++;
        for (size_t i = node->word.size(); i < 10; i++) cout << ' ';
        cout << ": " << node->count << endl;
        inorderFreq(node->right, rank);
    }

    // ---------- helpers ----------
    int maxCount(WordNode* node) const {
        if (node == nullptr) return 0;
        int m = node->count;
        int l = maxCount(node->left);
        int r = maxCount(node->right);
        if (l > m) m = l;
        if (r > m) m = r;
        return m;
    }

    void printWithCount(WordNode* node, int target, int& found) const {
        if (node == nullptr) return;
        printWithCount(node->left, target, found);
        if (node->count == target) {
            cout << (found ? ", " : "   ") << "\"" << node->word << "\"";
            found++;
        }
        printWithCount(node->right, target, found);
    }

    void destroy(WordNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // Lowercase and keep only letters/digits/apostrophes
    static string normalize(const string& token) {
        string w;
        for (char ch : token) {
            if (isalnum(static_cast<unsigned char>(ch)) || ch == '\'')
                w += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
        return w;
    }

public:
    WordBST() : root(nullptr), totalWords(0), uniqueWords(0) {}
    ~WordBST() { destroy(root); }

    void insertWord(const string& rawWord) {
        string w = normalize(rawWord);
        if (w.empty()) return;
        totalWords++;
        root = insert(root, w);
    }

    void insertParagraph(const string& text) {
        stringstream ss(text);
        string token;
        while (ss >> token) insertWord(token);
    }

    void displayAlphabetical() const {
        cout << "Words in alphabetical order (word : frequency)" << endl;
        inorderAlpha(root);
    }

    void displayByFrequency() {
        WordNode* freqRoot = nullptr;
        buildFreqTree(root, freqRoot);
        cout << "Words sorted by frequency (highest -> lowest)" << endl;
        int rank = 1;
        inorderFreq(freqRoot, rank);
        destroy(freqRoot);
    }

    void findMostFrequentWord() const {
        if (root == nullptr) {
            cout << "No words indexed." << endl;
            return;
        }
        int m = maxCount(root);
        int found = 0;
        cout << "Most frequent word(s) (" << m << " occurrences):" << endl;
        printWithCount(root, m, found);
        cout << endl;
    }

    void displaySummary() const {
        cout << "Summary" << endl;
        cout << "   Total words in paragraph : " << totalWords << endl;
        cout << "   Total unique words       : " << uniqueWords << endl;
    }
};

int main() {
    string paragraph = "The quick brown fox jumps over the lazy dog. The fox is quick and smart.";

    cout << "===== Task 2: Word Frequency Indexing using BST =====" << endl;
    cout << "Paragraph:" << endl << "   \"" << paragraph << "\"" << endl << endl;

    WordBST index;
    index.insertParagraph(paragraph);

    index.displayAlphabetical();
    cout << endl;
    index.displayByFrequency();
    cout << endl;
    index.findMostFrequentWord();
    cout << endl;
    index.displaySummary();

    return 0;
}

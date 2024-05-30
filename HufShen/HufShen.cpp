#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <iomanip> 

using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

class Huf_code {
private:
    unordered_map<char, string> codes;
    unordered_map<char, double> prob;

    void gen_codes(Node* root, string code) {
        if (root == nullptr)
            return;

        if (root->data != '$') {
            codes[root->data] = code;
        }

        gen_codes(root->left, code + "0");
        gen_codes(root->right, code + "1");
    }

public:
    Huf_code() {}

    void compress(string word) {
        unordered_map<char, int> freq;
        for (char c : word) {
            freq[c]++;
        }

        int all = word.length();
        for (auto& pair : freq) {
            prob[pair.first] = static_cast<double>(pair.second) / all;
        }

        priority_queue<Node*, vector<Node*>, compare> min_heap;

        for (auto pair : freq) {
            min_heap.push(new Node(pair.first, pair.second));
        }

        while (min_heap.size() != 1) {
            Node* left = min_heap.top();
            min_heap.pop();
            Node* right = min_heap.top();
            min_heap.pop();

            Node* newNode = new Node('$', left->frequency + right->frequency);
            newNode->left = left;
            newNode->right = right;

            min_heap.push(newNode);
        }

        Node* root = min_heap.top();
        gen_codes(root, "");
        delete root;
    }

    void print() {
        cout << setw(8) << left << "Symbol" << setw(15) << left << "Huffman Code" << "Probability\n";
        for (auto pair : codes) {
            cout << setw(8) << left << pair.first << setw(15) << left << pair.second << prob[pair.first] << "\n";
        }
    }
};

int main() {
    string word;
    cout << "Enter the word for coding: ";
    cin >> word;

    Huf_code huff;
    huff.compress(word);
    huff.print();

    return 0;
}

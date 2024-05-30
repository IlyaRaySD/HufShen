#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <iomanip> 

using namespace std;

// Node structure
struct Node {
    char data; // symbol
    int frequency; 
    Node* left;
    Node* right;

    Node(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

// Struct that returns bigger node
struct compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// Class for coding word
class Huf_code {
private:
    unordered_map<char, string> codes;
    unordered_map<char, double> prob;

    // Codes generation method
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
    // Huffman algorithm
    void huff(string word) {
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

    // Method for output codes & probabilites in console
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
    huff.huff(word);
    huff.print();

    return 0;
}

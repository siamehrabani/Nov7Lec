#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Node* buildExpTree(const string& exp) {
    stack<Node*> stack;
    for (char c : exp) {
        if (!isOp(c))
            stack.push(new Node(c));
        else {
            Node* rightOp = stack.top();
            stack.pop();
            Node* leftOp = stack.top();
            stack.pop();
            Node* newNode = new Node(c);
            newNode->left = leftOp;
            newNode->right = rightOp;
            stack.push(newNode);
        }
    }
    return stack.top();
}

int eval(Node* root) {
    if (root->data >= '0' && root->data <= '9') {
        return root->data - '0';
    }
    int lValue = eval(root->left);
    int rValue = eval(root->right);
    switch (root->data) {
        case '+': return lValue + rValue;
        case '-': return lValue - rValue;
        case '*': return lValue * rValue;
        case '/': return lValue / rValue;
        default:cerr << "Wrong op: " << root->data << endl;
        return 0;
    }
}

void printExp(Node* root) {
    if (root) {
        if (isOp(root->data))
            cout << "(";
        printExp(root->left);
        cout << root->data;
        printExp(root->right);
        if (isOp(root->data))
            cout << ")";           
    }
}

void deleteTree(Node* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}    


int main()
{
    // "12+3*" postfix
    string pfExp = "12+3*";
    Node* root = buildExpTree(pfExp);
    cout << "Result: " << eval(root) << endl;
    printExp(root);
    cout << endl;
    deleteTree(root);
    return 0;
}
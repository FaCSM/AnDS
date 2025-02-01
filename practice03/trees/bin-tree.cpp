#include "bin-tree.h"


/// Node constructor
BinTree::Node::Node() {
    key = 0;
    left = nullptr;
    right = nullptr;
}


/// Node constructor
BinTree::Node::Node(int k) {
    key = k;
    left = nullptr;
    right = nullptr;
}


/// Tree constructor
BinTree::BinTree() {
    root = nullptr;
}


/// Split expression string to vector of string-tokens. Supports: ( ), 0-9. WS-friendly
std::vector<std::string> stringToTokens(std::string &str) {
    // Empty expression handler
    if (str.empty()) throw std::invalid_argument("Empty string");

    // Remove whitespaces
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    // Algorithm
    std::vector<std::string> tokens;
    std::string number;  // Any number will be stored here
    for (char c : str) {
        std::string s(1, c);  // Handle multiple char operands (i.e. 123, 456, etc.)

        // Digit found
        if (isdigit(c)) {
            number += c;
        }

        // Single-char operators (look for char operators[8])
        else if (c == '(' || c == ')') {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            tokens.push_back(s);
        }

        // Unknown symbol error
        else throw std::runtime_error("Unknown symbol: " + s);
    }
    if (!number.empty()) tokens.push_back(number);
    return tokens;
}


/// Bracket binary tree representation parser. Get the tokens and return the root ptr
BinTree::Node* BinTree::parse(std::vector<std::string> &tokens) {
    if (tokens.empty()) throw std::invalid_argument("Empty string");

    unsigned openParenthesis = 0; // "Stack" to store open parentheses, close ones ain't actually stored
    std::stack<Node*> nodeStack;  // Stack to store nodes
    Node *curr;

    for (auto &token : tokens) {
        // Open parenthesis. Add to the opStack and continue
        if (token[0] == '(') {
            openParenthesis += 1;
        }

        // Digit. Create new node and push it to the nodeStack
        else if (std::isdigit(token[0])) {
            nodeStack.push(new Node(std::stoi(token)));
        }

        // Close parenthesis. Get the last node and delete the open parenthesis
        else if (token[0] == ')') {
            // Error handlers
            if (openParenthesis == 0) throw std::runtime_error("Unclosed brace");
            if (openParenthesis == 1 && (&token != &tokens.back())) throw std::runtime_error("Unclosed brace");
            if (nodeStack.empty()) throw std::runtime_error("Invalid expression");

            // Last node in stack is the head of the tree
            if (openParenthesis == 1 && &token == &tokens.back()) return nodeStack.top();

            if (openParenthesis == nodeStack.size()) {
                // In case with empty parenthesis stacks size wouldn't be equal
                openParenthesis -= 1;
                curr = nodeStack.top();
                nodeStack.pop();

                if (nodeStack.top()) {
                    // Default case
                    if (nodeStack.top()->left) nodeStack.top()->right = curr;
                    else nodeStack.top()->left = curr;
                } else {
                    // Empty parenthesis case, insert to the right
                    openParenthesis -= 1;
                    nodeStack.pop();
                    nodeStack.top()->right = curr;
                }
            } else {
                if (!(nodeStack.top()) || nodeStack.top()->left)
                    openParenthesis -= 1;    // Right empty parenthesis
                else
                    nodeStack.push(nullptr); // Left empty parenthesis
            }
        }
    }

    throw std::runtime_error("Unclosed brace");
}

/// Tree constructor based on bracket notation
BinTree::BinTree(std::string str) {
    std::vector tokens = stringToTokens(str); // String converted to vector of tokens
    root = parse(tokens);
}


/// Tree destructor
BinTree::~BinTree() {
    deleteTree(root);
}

/// Deep copy util for = operator
BinTree::Node* BinTree::copyTree(const Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->key);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}


/// Assignment operator
BinTree& BinTree::operator=(const BinTree& rhs) {
    if (this != &rhs) {
        deleteTree(root);
        root = copyTree(rhs.root);
    }
    return *this;
}

/// Delete the tree recursively
void BinTree::deleteTree(Node *head) {
    if (!head) return;

    deleteTree(head->left);
    deleteTree(head->right);

    delete head;
}


/// Print the tree from left to right
void BinTree::osVert(std::ostream &os, const Node *head, std::string prefix, bool isLeft) const {
    if (!head) return;

    const std::string vert = "³   ";
    const std::string up = "ÚÄ>";
    const std::string mid = "ÄÄ>";
    const std::string down = "ÀÄ>";

    // Print right path
    std::string rPrefix = prefix + (isLeft ? vert : "    ");
    osVert(os, head->right, rPrefix, false);

    // Print value
    if (head->key == root->key) os << mid << head->key << std::endl;
    else os << prefix << (isLeft ? down : up) << head->key << std::endl;

    // Print left path
    if (prefix.empty()) prefix += "    ";
    else prefix += (isLeft ? "    " : vert);
    osVert(os, head->left, prefix, true);
}


/// Print the tree to the output stream
std::ostream&operator<< (std::ostream &os, const BinTree &tree) {
    tree.osVert(os, tree.root);
    os << std::endl;
    return os;
}


/// Depth-first search util
void BinTree::depthFirstUtil(Node *head, std::vector<int> &values) {
    if (!head) return;
    values.push_back(head->key);
    depthFirstUtil(head->left, values);
    depthFirstUtil(head->right, values);
}


/// Depth-first search
std::vector<int> BinTree::depthFirstTraversal() {
    std::vector<int> values;
    depthFirstUtil(root, values);
    return values;
}
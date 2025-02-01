#include "avl-tree.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>


AVLTree::Node::Node(int k) {
    key = k;
    height = 1;
    left = nullptr;
    right = nullptr;
}


AVLTree::AVLTree() {
    root = nullptr;
}


AVLTree::AVLTree(const std::vector<int> &values) {
    root = nullptr;
    for (const auto &el : values) insert(el);
}

AVLTree::~AVLTree() {
    deleteTree(root);
}


void AVLTree::clear() {
    deleteTree(root);
    root = nullptr;
}


void AVLTree::deleteTree(Node *head) {
    if (!head) return;

    deleteTree(head->left);
    deleteTree(head->right);

    delete head;
}


unsigned char AVLTree::getHeight(Node *node) {
    return node ? node->height : 0;
}


unsigned char AVLTree::height() const {
    return root->height;
}

int AVLTree::getBalanceFactor(Node *head) {
    if (!head) return 0;
    return getHeight(head->left) - getHeight(head->right);
}


void AVLTree::Node::fixHeight() {
    unsigned char hLeft = getHeight(left);
    unsigned char hRight = getHeight(right);
    height = (hLeft > hRight ? hLeft : hRight) + 1;
}


AVLTree::Node* AVLTree::rotateRight(Node *head) {
    Node *newHead = head->left;
    head->left = newHead->right;
    newHead->right = head;
    head->fixHeight();
    newHead->fixHeight();
    return newHead;
}


AVLTree::Node* AVLTree::rotateLeft(Node *head) {
    Node *newHead = head->right;
    head->right = newHead->left;
    newHead->left = head;
    head->fixHeight();
    newHead->fixHeight();
    return newHead;
}


AVLTree::Node* AVLTree::insertUtil(Node *head, int k) {
    if (!head) {
        return new Node(k);
    }

    if (k < head->key) head->left = insertUtil(head->left, k);
    else if (k > head->key) head->right = insertUtil(head->right, k);

    head->fixHeight();
    int balanceFactor = getBalanceFactor(head);
    if (balanceFactor > 1) {
        if (k >= head->left->key) head->left = rotateLeft(head->left);
        return rotateRight(head);
    } else if (balanceFactor < -1) {
        if (k <= head->right->key) head->right = rotateRight(head->right);
        return rotateLeft(head);
    }

    return head;
}


void AVLTree::insert(int k) {
    root = insertUtil(root, k);
}


AVLTree::Node* AVLTree::searchUtil(Node *head, int k) {
    if (!head || k == head->key) return head;

    if (k > head->key) return searchUtil(head->right, k);
    else return searchUtil(head->left, k);
}


bool AVLTree::find(int k) {
    return searchUtil(root, k) != nullptr;
}


AVLTree::Node *AVLTree::removeUtil(Node *head, int k) {
    if (!head) return nullptr;

    if (k < head->key) head->left = removeUtil(head->left, k);
    else if (k > head->key) head->right = removeUtil(head->right, k);
    else {
        if (!head->left || !head->right) {
            Node *temp = head->left ? head->left : head->right;
            if (!temp) {
                temp = head;
                head = nullptr;
            } else {
                *head = *temp;
            }
            delete temp;
        } else {

            Node *temp = head->right;
            while (temp->left) temp = temp->left;
            head->key = temp->key;
            head->right = removeUtil(head->right, temp->key);
        }
    }

    if (!head) return nullptr;

    head->height = 1 + std::max(getHeight(head->left), getHeight(head->right));

    int balance = getBalanceFactor(head);
    if (balance > 1 && getBalanceFactor(head->left) >= 0) {
        return rotateRight(head);
    }
    if (balance > 1 && getBalanceFactor(head->left) < 0) {
        head->left = rotateLeft(head->left);
        return rotateRight(head);
    }
    if (balance < -1 && getBalanceFactor(head->right) <= 0) {
        return rotateLeft(head);
    }
    if (balance < -1 && getBalanceFactor(head->right) > 0) {
        head->right = rotateRight(head->right);
        return rotateLeft(head);
    }

    return head;
}


void AVLTree::remove(int k) {
    root = removeUtil(root, k);
}


void AVLTree::getVerticalOrder(const Node *head, std::vector<std::vector<int>> &verticalOrder, int depth = 0) const {
    if (!head) {
        verticalOrder[depth].push_back(9999);
        return;
    }

    getVerticalOrder(head->right, verticalOrder, depth + 1);
    verticalOrder[depth].push_back(head->key);
    getVerticalOrder(head->left, verticalOrder, depth + 1);
}


void AVLTree::osHor(std::ostream& os) const {
    if (!root) return;

    const std::string downL = "Ú";
    const std::string downR = "¿";
    const std::string horiz = "Ä";
    const std::string horUp = "Á";

    unsigned char h = root->height;
    unsigned short maxLine = short(pow(2, h - 1)) * 4;
    unsigned short tab, prefix = 10;

    std::vector<std::vector<int>> verticalOrder;
    verticalOrder.resize(h + 1);
    getVerticalOrder(root, verticalOrder);

    for (short i = 1; i <= h; ++i) {
        auto row = verticalOrder[i - 1];
        std::reverse(row.begin(), row.end());

        tab = prefix;
        prefix = short(maxLine / pow(2, i)) - 1;

        if (i != 1) {
            os << std::string(prefix, ' ');
            for (int j = 0; j < row.size() / 2; ++j) {
                std::cout << downL;
                for (int l = 0; l < tab / 2; ++l) std::cout << horiz;
                std::cout << horUp;
                for (int l = 0; l < tab / 2; ++l) std::cout << horiz;
                std::cout << downR << std::string(tab, ' ');
            }
            os << std::endl;
        }


        if (prefix) os << std::string(prefix - 1, ' ');
        for (auto &key: row) {
            unsigned char keyLength = std::to_string(key).length();
            if (keyLength < 3) {
                os << " ";
                keyLength++;
            }
            if (key == 9999) {
                os << "   ";
                keyLength = 3;
            } else {
                os << key;
            }
            os << std::string(tab + 1 - keyLength, ' ');
        }
        os << std::endl;
    }
}


void AVLTree::osVert(std::ostream &os, const Node *head, std::string prefix, bool isLeft) const {
    if (!head) return;

    const std::string vert = "³   ";
    const std::string up = "ÚÄ>";
    const std::string mid = "ÄÄ>";
    const std::string down = "ÀÄ>";

    std::string rPrefix = prefix + (isLeft ? vert : "    ");
    osVert(os, head->right, rPrefix, false);

    if (head->key == root->key) os << mid << head->key << std::endl;
    else os << prefix << (isLeft ? down : up) << head->key << std::endl;

    if (prefix.empty()) prefix += "    ";
    else prefix += (isLeft ? "    " : vert);
    osVert(os, head->left, prefix, true);
}


std::ostream&operator<< (std::ostream &os, const AVLTree &tree) {
    if (tree.height() > 4) tree.osVert(os, tree.root);
    else tree.osHor(os);
    os << std::endl;
    return os;
}


void AVLTree::breadthFirstUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::queue<Node*> q;
    q.push(head);
    while (!q.empty()) {
        Node *curr = q.front();
        q.pop();

        std::cout << curr->key << ' ';

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

void AVLTree::breadthFirstTraversal() const {
    breadthFirstUtil(root);
}


void AVLTree::inOrderUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::stack<Node*> s;
    Node *curr = head;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        std::cout << curr->key << ' ';

        curr = curr->right;
    }
}


void AVLTree::inOrderTraversal() const {
    inOrderUtil(root);
}


void AVLTree::preOrderUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::stack<Node*> s;
    Node *curr = head;

    while (curr || !s.empty()) {
        while (curr) {
            std::cout << curr->key << ' ';

            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        curr = curr->right;
    }
}


void AVLTree::preOrderTraversal() const {
    preOrderUtil(root);
}


void AVLTree::postOrderUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::stack<Node*> s;
    Node *curr = head;
    Node *last = nullptr;

    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }

        Node *top = s.top();
        if (!top->right || top->right == last) {
            std::cout << top->key << ' ';

            s.pop();
            last = top;
        } else {
            curr = top->right;
        }
    }
}


void AVLTree::postOrderTraversal() const {
    postOrderUtil(root);
}
// intbst.cpp
// Implements class IntBST
// Ashvik Vivekan 10/23/2026

#include "intbst.h"

#include <iostream>
using std::cout;

IntBST::IntBST() {
    root = nullptr;
}

IntBST::~IntBST() {
    clear(root);
}

void IntBST::clear(Node *n) {
    if (n==nullptr){
        return;
    }

    clear(n->left);
    clear(n->right);
    delete n;
}

bool IntBST::insert(int value) {
    if (root==nullptr){
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

bool IntBST::insert(int value, Node *n) {
    if (value < n->info){
        if (n->left==nullptr){
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        else{
            return insert(value, n->left);
        }
    }
    else if (value > n->info){
        if (n->right==nullptr){
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        else{
            return insert(value, n->right);
        }
    }
    else{
        return false;
    }
}

void IntBST::printPreOrder() const {
    printPreOrder(root);
}

void IntBST::printPreOrder(Node *n) const {
    if (n==nullptr){
        return;
    }

    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

void IntBST::printInOrder() const {
    printInOrder(root);
}

void IntBST::printInOrder(Node *n) const {
    if (n==nullptr){
        return;
    }

    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n==nullptr){
        return;
    }

    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

int IntBST::sum() const {
    return sum(root);
}

int IntBST::sum(Node *n) const {
    if (n==nullptr){
        return 0;
    }

    int val = 0;
    val += sum(n->left);
    val += n->info;
    val += sum(n->right);

    return val;
}

int IntBST::count() const {
    return count(root);
}

int IntBST::count(Node *n) const {
    if (n==nullptr){
        return 0;
    }

    int ctr = 1;
    ctr += count(n->left);
    ctr += count(n->right);

    return ctr;
}

IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (n==nullptr){
        return nullptr;
    }

    if (value < n->info){
        return getNodeFor(value, n->left);
    }
    else if (value > n->info){
        return getNodeFor(value, n->right);
    }
    else{
        return n;
    }
}

bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

IntBST::Node* IntBST::getPredecessorNode(int value) const {
    Node* n = getNodeFor(value, root);
    if (n==nullptr){
        return nullptr;
    }

    if (n->left != nullptr){
        n = n->left;
        while (n->right != nullptr){
            n = n->right;
        }
        return n;
    }

    Node* p = n->parent;
    while (p != nullptr && n==p->left){
        n = p;
        p = p->parent;
    }

    return p;
}

int IntBST::getPredecessor(int value) const {
    Node* n = getPredecessorNode(value);
    if (n==nullptr){
        return 0;
    }

    return n->info;
}

IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* n = getNodeFor(value, root);
    if (n==nullptr){
        return nullptr;
    }

    if (n->right != nullptr){
        n = n->right;
        while (n->left != nullptr){
            n = n->left;
        }
        return n;
    }

    Node* p = n->parent;
    while (p != nullptr && n==p->right){
        n = p;
        p = p->parent;
    }

    return p;
}

int IntBST::getSuccessor(int value) const {
    Node* n = getSuccessorNode(value);
    if (n==nullptr){
        return 0;
    }

    return n->info;
}

bool IntBST::remove(int value) {
    Node* n = getNodeFor(value, root);
    if (n==nullptr){
        return false;
    }

    if (n->left != nullptr && n->right != nullptr){
        Node* successor = getSuccessorNode(value);
        n->info = successor->info;
        n = successor;
    }

    Node* child = nullptr;
    if (n->left != nullptr){
        child = n->left;
    }
    else{
        child = n->right;
    }

    if (child != nullptr){
        child->parent = n->parent;
    }

    if (n->parent==nullptr){
        root = child;
    }
    else if (n==n->parent->left){
        n->parent->left = child;
    }
    else{
        n->parent->right = child;
    }

    delete n;
    return true;
}

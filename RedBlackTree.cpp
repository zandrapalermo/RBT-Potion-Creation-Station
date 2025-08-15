#include "RedBlackTree.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

RedBlackTree::RedBlackTree(function<int(const Potion&)> keyFunc)
    : root(nullptr), sortKey(std::move(keyFunc)) {}

RedBlackTree::~RedBlackTree() {
    clear();
}

RedBlackTree::RedBlackTree(RedBlackTree&& other) noexcept
    : root(other.root), sortKey(std::move(other.sortKey)) {
    other.root = nullptr;
}

RedBlackTree& RedBlackTree::operator=(RedBlackTree&& other) noexcept {
    if (this != &other) {
        clear();
        root = other.root;
        sortKey = std::move(other.sortKey);
        other.root = nullptr;
    }
    return *this;
}

void RedBlackTree::rotateLeft(Node*& x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node*& x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node*& k) {
    while (k->parent && k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right;
            if (u && u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->left;
            if (u && u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(k->parent->parent);
            }
        }
    }
    if (root) root->color = BLACK;
}

void RedBlackTree::insert(const Potion& p) {
    Node* node = new Node(p);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (sortKey(node->data) < sortKey(x->data))
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (!y)
        root = node;
    else if (sortKey(node->data) < sortKey(y->data))
        y->left = node;
    else
        y->right = node;

    if (!node->parent) {
        node->color = BLACK;
        return;
    }
    if (!node->parent->parent)
        return;

    fixInsert(node);
}

// ---- helpers that don't rely on BST order by name ----
Node* RedBlackTree::findByNameDFS(Node* node, const string& name) const {
    if (!node) return nullptr;
    if (node->data.name == name) return node;
    if (auto* left = findByNameDFS(node->left, name)) return left;
    return findByNameDFS(node->right, name);
}

void RedBlackTree::collectAll(Node* node, vector<Potion>& out) const {
    if (!node) return;
    collectAll(node->left, out);
    out.push_back(node->data);
    collectAll(node->right, out);
}

Potion* RedBlackTree::search(const string& name) {
    Node* n = findByNameDFS(root, name);
    return n ? &n->data : nullptr;
}

// Simpler, safe removal by rebuilding the tree without the target name.
// This keeps behavior correct for any sort key without implementing full RBT delete.
void RedBlackTree::remove(const string& name) {
    if (!root) return;
    vector<Potion> items;
    items.reserve(64);
    collectAll(root, items);

    // filter out the one to remove (by name)
    bool removed = false;
    vector<Potion> keep;
    keep.reserve(items.size());
    for (const auto& p : items) {
        if (!removed && p.name == name) { removed = true; continue; }
        keep.push_back(p);
    }
    if (!removed) return; // nothing to remove

    clear();
    for (const auto& p : keep) insert(p);
}

void RedBlackTree::inorderHelper(Node* node, vector<Potion>& vec) const {
    if (!node) return;
    inorderHelper(node->left, vec);
    vec.push_back(node->data);
    inorderHelper(node->right, vec);
}

void RedBlackTree::inorder(bool descending) const {
    vector<Potion> potions;
    inorderHelper(root, potions);

    if (descending) {
        for (auto it = potions.rbegin(); it != potions.rend(); ++it)
            it->print();
    } else {
        for (auto& p : potions)
            p.print();
    }
}

void RedBlackTree::clearHelper(Node* node) {
    if (!node) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

void RedBlackTree::clear() {
    clearHelper(root);
    root = nullptr;
}

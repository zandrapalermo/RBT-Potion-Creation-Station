#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Potion.h"
#include <functional>
#include <string>
#include <vector>
#include <utility>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    Potion data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;

    Node(const Potion& p) : data(p), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    Node* root;
    function<int(const Potion&)> sortKey;

    
    void rotateLeft(Node*&);
    void rotateRight(Node*&);
    void fixInsert(Node*&);

    
    void inorderHelper(Node* node, vector<Potion>& vec) const;
    void clearHelper(Node* node);
    void collectAll(Node* node, vector<Potion>& out) const;
    Node* findByNameDFS(Node* node, const string& name) const;

public:
    explicit RedBlackTree(function<int(const Potion&)> keyFunc);
    ~RedBlackTree();

    
    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;
    RedBlackTree(RedBlackTree&& other) noexcept;
    RedBlackTree& operator=(RedBlackTree&& other) noexcept;

    
    void insert(const Potion& p);
    void remove(const string& name);      
    Potion* search(const string& name);   
    void inorder(bool descending = false) const;
    void clear();
};

#endif

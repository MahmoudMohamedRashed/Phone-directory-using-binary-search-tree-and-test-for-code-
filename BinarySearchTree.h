#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "Exception.h"
#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;
struct Node
{
    string data;
    Node* parent;
    Node* left;
    Node* right;
    Node* associated_node;
    Node() : parent(NULL), left(NULL),right(NULL)
        , associated_node(NULL) {}
};

class BinarySearchTree
{
public:
    class Position
    {
    public:
        Node* v;
    public:
        Position(Node* v = NULL);
        string& operator*();
        Position left() const;
        Position right() const;
        Position parent() const;
        Position associated_node() const;
        bool isRoot() const;
        bool isExternal() const;
        bool hasLeftChild() const;
        bool hasRightChild() const;
        friend class BinarySearchTree;
    };
    typedef std::list<Position> PositionList;
public:
    BinarySearchTree();
    bool is_vaild_num (string num) throw() ;
    bool is_vaild_nam (string nam) throw() ;
    bool empty() const;
    Position root() const;
    PositionList positions() const;
    Node* add(string data)
    {
        if (empty())
        {
            addRoot() ;
            root().v ->data = data ;
            expandExternal(root()) ;
            return (root().v);
        }
        Position r (_root) ;
        while( !r.isExternal() )
        {
            if ( data == r.v->data ) throw NameExist("Name is already existed in the directory") ;
            if ( data < (r.v->data) )
                r = r.left() ;
            else
                r = r.right() ;
        }
        if ( r.isExternal() )
        {
            r.v->data = data ;
            expandExternal(r);
        }
        return (r.v) ;
    }
    void remove(Position & p);
    void inorder(Position p, PositionList& pl) const;

protected:
    void addRoot();
    void expandExternal(const Position& p);
private:
    Node* _root;
};

typedef BinarySearchTree::Position Position;
typedef BinarySearchTree::PositionList PositionList;
#endif

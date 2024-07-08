#include "BinarySearchTree.h"
Position::Position(Node* v) : v(v) {}

string& BinarySearchTree::Position::operator*()
{
    return v->data ;
}

Position Position::left() const
{
    return Position(v->left);
}

Position Position::right() const
{
    return Position(v->right);
}

Position Position::parent() const
{
    return Position(v->parent);
}
Position Position ::associated_node() const
{
    return Position( v->associated_node ) ;
}

bool Position::isRoot() const
{
    return v->parent == NULL;
}

bool Position::isExternal() const
{
    return (v->left == NULL && v->right == NULL);
}

bool Position::hasLeftChild() const
{
    return v->left != NULL;
}

bool Position::hasRightChild() const
{
    return v->right != NULL;
}

BinarySearchTree::BinarySearchTree()
    : _root(NULL) { }

bool BinarySearchTree::empty() const
{
    return _root == NULL ;
}

bool BinarySearchTree ::is_vaild_nam(string nam) throw()
{
    for ( int i = 0 ; i < nam.size() ; i++ )
    {
        if ( (( nam[i] < 'a' ) || (nam[i] > 'z')) && (nam[i] != ' ') )
        {
            throw vaildName("Invalid Name Format") ;
            return false ;
        }
    }
    return true ;
}

bool BinarySearchTree ::is_vaild_num( string num ) throw()
{
    for ( int i = 0 ; i < num.size() ; i++ )
    {
        if ( ( num[i] < '0' ) || (num[i] > '9') )
        {
            throw vaildNumber("Invalid Phone Number Format") ;
            return false ;
        }
    }
    return true ;
}

Position BinarySearchTree::root() const
{
    return Position( _root ) ;
}

void BinarySearchTree::addRoot()
{
    _root = new Node;
}

void BinarySearchTree::expandExternal(const Position& p)
{
    Node* v = p.v;
    v->left = new Node;
    v->left->parent = v;
    v->right = new Node;
    v->right->parent = v;
}
PositionList BinarySearchTree::positions() const
{
    PositionList pl;
    inorder(_root, pl);
    return PositionList(pl);
}


void BinarySearchTree::inorder(Position p, PositionList& pl) const
{
    if(p.isExternal()) return ;
    if(p.hasLeftChild())
        inorder(p.left(), pl);
    pl.push_back(p);
    if(p.hasRightChild())
        inorder(p.right(), pl);
}

void BinarySearchTree::remove(Position & p)
{
    Position left = p.left() ;
    Position right= p.right();
    Node* cur ;
    Node* ptr ;
    if ( left.isExternal() && right.isExternal() )
    {
        cur = left.v ;
        delete cur ;
        left = p.parent() ;
        cur = left.v ;
        if ( cur ->left == p.v ) cur ->left = right.v ;
        else cur ->right = right.v ;
        ptr = p.v ;
        delete ptr ;
    }
    else
    {
        if ( left.isExternal() ) //has only right
        {
            cur = left.v ;
            delete cur ;
            ptr = right.v ;
            left = p.parent() ;
            cur = left.v ;
            if ( cur -> left == p.v ) cur ->left = ptr ;
            else cur ->right = ptr ;
            ptr = p.v ;
            delete ptr ;
        }
        else if ( right.isExternal() )  //has only left
        {
            cur = right.v ;
            delete cur ;
            ptr = left.v ;
            right = p.parent() ;
            cur = right.v ;
            if ( cur -> left == p.v ) cur ->left = ptr ;
            else cur ->right = ptr ;
            ptr = p.v ;
            delete ptr ;
        }
        else  //has left and right
        {
            while ( !right.isExternal() ) right = right.left() ;
            cur = right.v ;
            right = right.parent() ;
            delete cur ;
            p.v->data = right.v->data ;
            this->remove(right) ;
        }
    }
}

/*if not found*/


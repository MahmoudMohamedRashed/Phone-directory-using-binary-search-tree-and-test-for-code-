#include "phonedirectory.h"
void PhoneDirectory ::insert(string name, string phone_num)
{
    if (( name_bst.is_vaild_nam(name) && (phone_bst.is_vaild_num(phone_num))) )
    {
        Node* na = name_bst.add( name ) ;
        Node* ph = phone_bst.add( phone_num ) ;
        na ->associated_node = ph ;
        ph ->associated_node = na ;
        counter++ ;
    }
}

void PhoneDirectory ::remove(string name)
{
    Position p = name_bst.root() ;
    while ( !p.isExternal() )
    {
        if ( name == p.v->data )
        {
            Node* ptr = p.v->associated_node ;
            Position ph(ptr) ;
            name_bst.remove(p) ;
            phone_bst.remove(ph) ;
            counter-- ;
            return ;
        }
        else if ( name > p.v->data )
        {
            p = p.right() ;
        }
        else
        {
            p = p.left() ;
        }
    }
}
void PhoneDirectory ::helper (PositionList &p, Position q, string name)
{
    if ( q.v == NULL ) return ;
    if ( q.isExternal() ) return ;
    if ( equal_str(name, q.v->data) || name == q.v->data )
    {
        p.push_back (q) ;
        helper( p, q.left(), name ) ;
        helper( p, q.right(), name ) ;
    }
    else if ( name < q.v->data )
        helper( p, q.left(), name ) ;
    else
        helper( p, q.right(), name ) ;
}

PositionList PhoneDirectory ::search_by_name(string name)
{
    PositionList out ;
    if ( name_bst.empty() ) return out ;
    Position start = name_bst.root() ;
    helper( out, start, name ) ;
    return out ;
}

PositionList PhoneDirectory ::search_by_phone_num(string phone_num)
{
    PositionList out ;
    if ( phone_bst.empty() ) return out ;
    Position start = phone_bst.root() ;
    helper( out, start, phone_num ) ;
    return out ;
}
PositionList PhoneDirectory ::get_contact_list()
{
    Position p = name_bst.root() ;
    PositionList out ;
    name_bst.inorder( p, out) ;
    return out ;
}
void PhoneDirectory ::travel ( Position& p )
{
    Position pa ;
    if ( p.hasLeftChild() )
    {
        Position left = p.left() ;
        travel(left) ;
    }
    if ( p.hasRightChild() )
    {
        Position right = p.right() ;
        travel(right) ;
    }
    pa = p.parent() ;
    Node* ptr = p.v ;
    if ( pa.v->left == p.v ) pa.v->left = NULL ;
    else pa.v->right = NULL ;
    delete ptr ;
    ptr = NULL ;
}
/*
in reomve all funcation if we go by the root of tree the program will be crach you shoud
    go by the left and right sub tree
    I dont no why...!! but it work good
*/
void PhoneDirectory ::delete_all()
{
    Position p = name_bst.root() ;
    Position ph= phone_bst.root() ;
    Position l = p.left() ;
    Position r = p.right();
    travel( l ) ;
    travel( r ) ;
    Node* pt = p.v ;
    delete pt ;
    pt = NULL ;
    l = ph.left() ;
    r = ph.right() ;
    travel( l ) ;
    travel( r ) ;
    pt = ph.v ;
    delete pt ;
    pt = NULL ;
}


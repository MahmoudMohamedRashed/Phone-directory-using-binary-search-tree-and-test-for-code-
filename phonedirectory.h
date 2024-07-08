#ifndef PHONEDIRECTORY_H
#define PHONEDIRECTORY_H
#include <string>
#include "BinarySearchTree.h"

using namespace std;

class PhoneDirectory{
protected:
    bool equal_str ( string name1 , string name2 )
    {
        int size1 = name1.size() ;
        int size2 = name2.size() ;
        if ( size2 < size1 ) return false ;
        for ( int i = 0 ; i < size1 ; i++ )
        {
            if ( name1[i] != name2[i] ) return false ;
        }
        return true ;
    }
    void travel ( Position &p) ;
    void helper ( PositionList &p , Position q , string name ) ;
public:
	// void or bool
	void insert(string name, string phone_num);

	void remove(string name) ;
	// List of Positions to Name nodes starting with or matching string name.
	PositionList search_by_name(string name);
	// List of Positions to Phone number nodes starting with or matching string phone_num.
	PositionList search_by_phone_num(string phone_num);

	PositionList get_contact_list();
	void print_all ( Node* ptr = NULL ) ;

	void delete_all();

	unsigned int get_count();
private:
	// Copy Constructor / Destructor / Copy Assignment (Not Implemented)
	BinarySearchTree name_bst;
	BinarySearchTree phone_bst;
	int counter = 0 ;
};

/*
Name // lower case letters w/ spaces
PhoneNumber // only numeric digits
*/
#endif // PHONEDIRECTORY_H

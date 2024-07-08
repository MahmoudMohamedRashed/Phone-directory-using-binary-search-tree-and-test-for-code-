#ifndef BINARY.H
#define BINARY.H
#include <string>
struct phones
{
    string val ;
    phones* left ;
    phones* right;
    phones* parent;
    phones* nother;
    phones() : left(NULL) , right(NULL) , parent(NULL) , nother(NULL) {}
};

class binary_s
{
private:
    phones* head ;
    int counter  ;
public:
    binary_s() ;
    bool isempty () ;
    bool is_external() ;
    void insert ( string nam , string num ) ;
    void remove
};
#endif // BINARY

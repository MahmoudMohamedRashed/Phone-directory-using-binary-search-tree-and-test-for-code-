#include "positionlistutils.h"

void PositionListUtils::display_list(PositionList& pl, bool is_name_list)
{
    if(!pl.size())
    {
        cout << "not found" << endl;
        return;
    }

    printf("found %d matches\n", (int)pl.size());
    for (PositionList::iterator i = pl.begin(); i!=pl.end(); i++)
    {
        Position x = *i ;
        Node* ptr = x.v->associated_node ;
        // Name list
        if (is_name_list)
            cout << x.v->data <<": " << ptr->data << endl;
        // Phone list: print name first
        else
            cout << ptr->data << ": " << x.v->data << endl;
    }
}

void PositionListUtils::sort_list(PositionList& pl, bool is_name_list)
{
    for (PositionList::iterator i = pl.begin(); i!=pl.end(); i++)
    {
        Position x = *i ;
        Node* ptrx = x.v->associated_node ;
        PositionList::iterator j = i;
        while(++j!=pl.end())
        {
            Position y = *j ;
            Node* ptry = y.v->associated_node ;
            // Always sort by name
            if((is_name_list && ( x.v->data ) > (y.v->data) ||
                    (!is_name_list && (ptrx->data) > (ptry ->data))))
            {
                Position temp_p = *i;
                *i = *j;
                *j = temp_p;
            }
        }
    }
}

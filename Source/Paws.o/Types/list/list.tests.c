#include "list.c"
#include "Cest.h"


CEST(List, allocate) {
  list    a_list    = List->allocate();
  ASSERT( a_list->content->first  == NULL );
  ASSERT( a_list->content->last   == NULL );
  ASSERT( a_list->content->length == 0    );
  
  SUCCEED;
}

CEST(list, naughtify) {
  list    rv, a_naughty, a_list    = List->allocate();
  
  rv    = List->naughtify(a_list);
  ASSERT(              a_list->   content->length                 == 1         );
  ASSERT(       LL->at(a_list->   content, 0)->thing.isa          == LIST      );
  
  a_naughty   = LL->at(a_list->   content, 0)->thing.pointer.list;
  ASSERT(       LL->at(a_naughty->content, 0)->thing.isa          == LIST      );
  ASSERT(       LL->at(a_naughty->content, 0)->thing.pointer.list == a_naughty );
  
  ASSERT(                                                      rv == a_naughty );
  
  SUCCEED;
}

CEST(list, thing) {
  list    a_list    = List->allocate();
  
  ASSERT( List->thing(a_list).isa          == LIST   );
  ASSERT( List->thing(a_list).pointer.list == a_list );
  
  SUCCEED;
}

CEST(list, insert) {
  list  a_list = List->allocate();
  thing thing1 = List->thing(List->allocate()),
        thing2 = List->thing(List->allocate()),
        thing3 = List->thing(List->allocate()),
        thing4 = List->thing(List->allocate());
  
  /* Insert into empty list */
  List->insert    (a_list, thing2, 0);
  ASSERT( List->at(a_list, 0).pointer.list == thing2.pointer.list );
  ASSERT(          a_list->content->length == 1                   );
  
  /* Insert onto the front of list */
  List->insert    (a_list, thing1, 0);
  ASSERT( List->at(a_list, 0).pointer.list == thing1.pointer.list );
  ASSERT(          a_list->content->length == 2                   );
  
  /* Insert onto the end of list */
  List->insert    (a_list, thing4, 2);
  ASSERT( List->at(a_list, 2).pointer.list == thing4.pointer.list );
  ASSERT(          a_list->content->length == 3                   );
  
  /* Insert into list */
  List->insert    (a_list, thing3, 2);
  ASSERT( List->at(a_list, 2).pointer.list == thing3.pointer.list );
  ASSERT(          a_list->content->length == 4                   );
  
  SUCCEED;
}

CEST(list, prefix) {
  list  a_list = List->allocate();
  thing thing1 = List->thing(List->allocate()),
        thing2 = List->thing(List->allocate()),
        thing3 = List->thing(List->allocate());
  
  List->prefix    (a_list, thing3);
  ASSERT( List->at(a_list, 0).pointer.list == thing3.pointer.list );
  ASSERT(          a_list->content->length == 1                   );
  
  List->prefix    (a_list, thing2);
  ASSERT( List->at(a_list, 0).pointer.list == thing2.pointer.list );
  ASSERT(          a_list->content->length == 2                   );
  
  List->prefix    (a_list, thing1);
  ASSERT( List->at(a_list, 0).pointer.list == thing1.pointer.list );
  ASSERT(          a_list->content->length == 3                   );
  
  SUCCEED;
}

CEST(list, affix) {
  list  a_list = List->allocate();
  thing thing1 = List->thing(List->allocate()),
        thing2 = List->thing(List->allocate()),
        thing3 = List->thing(List->allocate());
  
  List->affix     (a_list, thing1);
  ASSERT( List->at(a_list, 0).pointer.list == thing1.pointer.list );
  ASSERT(          a_list->content->length == 1                   );
  
  List->affix     (a_list, thing2);
  ASSERT( List->at(a_list, 1).pointer.list == thing2.pointer.list );
  ASSERT(          a_list->content->length == 2                   );
  
  List->affix     (a_list, thing3);
  ASSERT( List->at(a_list, 2).pointer.list == thing3.pointer.list );
  ASSERT(          a_list->content->length == 3                   );
  
  SUCCEED;
}

CEST(list, at) {
  list  a_list = List->allocate();
  
  /* Empty `list`s */
  ASSERT( List->at(a_list, 5).pointer.unknown == NULL    );
  ASSERT( List->at(a_list, 4).pointer.unknown == NULL    );
  ASSERT( List->at(a_list, 1).pointer.unknown == NULL    );
  ASSERT( List->at(a_list, 0).pointer.unknown == NULL    );
  
  thing thing1 = List->thing(List->allocate()); List->affix(a_list, thing1);
  thing thing2 = List->thing(List->allocate()); List->affix(a_list, thing2);
  thing thing3 = List->thing(List->allocate()); List->affix(a_list, thing3);
  
  /* Positive indicies */
  ASSERT( List->at(a_list, 0).pointer.list == thing1.pointer.list );
  ASSERT( List->at(a_list, 1).pointer.list == thing2.pointer.list );
  ASSERT( List->at(a_list, 2).pointer.list == thing3.pointer.list );
  
  /* OOB indicies */
  ASSERT( List->at(a_list, 5).pointer.unknown == NULL    );
  ASSERT( List->at(a_list, 4).pointer.unknown == NULL    );
  
  SUCCEED;
}

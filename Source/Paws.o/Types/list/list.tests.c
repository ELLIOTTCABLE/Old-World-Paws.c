#include "list.c"
#include "Cest.h"


CEST(List, create) {
  list    a_list, a_naughty;
  
  a_list      = List->create();
  ASSERT(              a_list->   content->length                 == 1         );
  ASSERT(       LL->at(a_list->   content, 0)->thing.isa          == LIST      );
  
  a_naughty   = LL->at(a_list->   content, 0)->thing.pointer.list;
  ASSERT(       LL->at(a_naughty->content, 0)->thing.isa          == LIST      );
  ASSERT(       LL->at(a_naughty->content, 0)->thing.pointer.list == a_naughty );
  
  SUCCEED;
}

CEST(List, create_naughty) {
  list    a_naughty;
  
  a_naughty   = List->create_naughty();
  ASSERT(        a_naughty->content->length                 == 1         );
                                                            
  ASSERT( LL->at(a_naughty->content, 0)->thing.isa          == LIST      );
  ASSERT( LL->at(a_naughty->content, 0)->thing.pointer.list == a_naughty );
  
  SUCCEED;
}

CEST(list, thing) {
  list    a_list    = List->create();
  
  ASSERT( List->thing(a_list).isa          == LIST   );
  ASSERT( List->thing(a_list).pointer.list == a_list );
  
  SUCCEED;
}

CEST(list, insert) {
  list  a_list = List->create();
  thing thing1 = List->thing(List->create()),
        thing2 = List->thing(List->create()),
        thing3 = List->thing(List->create()),
        thing4 = List->thing(List->create());
  
  /* This is a somewhat unusual situation… it shouldn’t often show up in practice, but we’re going to remove the
   * naughty, and reset the list to a blank state, before proceeding. */
  a_list->content->first    = NULL;
  a_list->content->last     = NULL;
  a_list->content->length   = 0;
  
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
  list  a_list = List->create();
  thing thing1 = List->thing(List->create()),
        thing2 = List->thing(List->create()),
        thing3 = List->thing(List->create());
  
  a_list->content->first  = NULL;
  a_list->content->last   = NULL;
  a_list->content->length = 0;
  
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
  list  a_list = List->create();
  thing thing1 = List->thing(List->create()),
        thing2 = List->thing(List->create()),
        thing3 = List->thing(List->create());
  
  a_list->content->first  = NULL;
  a_list->content->last   = NULL;
  a_list->content->length = 0;
  
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
  list  a_list = List->create();
  
  a_list->content->first  = NULL;
  a_list->content->last   = NULL;
  a_list->content->length = 0;
  
  /* Empty `list`s */
  ASSERT( List->at(a_list, 5).pointer.nothing == NULL    );
  ASSERT( List->at(a_list, 5).isa             == NOTHING );
  ASSERT( List->at(a_list, 4).pointer.nothing == NULL    );
  ASSERT( List->at(a_list, 4).isa             == NOTHING );
  ASSERT( List->at(a_list, 1).pointer.nothing == NULL    );
  ASSERT( List->at(a_list, 1).isa             == NOTHING );
  ASSERT( List->at(a_list, 0).pointer.nothing == NULL    );
  ASSERT( List->at(a_list, 0).isa             == NOTHING );
  
  thing thing1 = List->thing(List->create()); List->affix(a_list, thing1);
  thing thing2 = List->thing(List->create()); List->affix(a_list, thing2);
  thing thing3 = List->thing(List->create()); List->affix(a_list, thing3);
  
  /* Positive indicies */
  ASSERT( List->at(a_list, 0).pointer.list == thing1.pointer.list );
  ASSERT( List->at(a_list, 1).pointer.list == thing2.pointer.list );
  ASSERT( List->at(a_list, 2).pointer.list == thing3.pointer.list );
  
  /* OOB indicies */
  ASSERT( List->at(a_list, 5).pointer.nothing == NULL    );
  ASSERT( List->at(a_list, 5).isa             == NOTHING );
  ASSERT( List->at(a_list, 4).pointer.nothing == NULL    );
  ASSERT( List->at(a_list, 4).isa             == NOTHING );
  
  SUCCEED;
}

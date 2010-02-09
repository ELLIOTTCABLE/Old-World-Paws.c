#include "list.c"

#if !defined(CEST_H)
# include "Cest.h"
#endif

CEST(List, create) {
  list a_list, a_naughty;
  
  a_list = List.create();
  ASSERT( a_list->content->length == 1 );
  
  /* We use the `LL` interface here, so as not to depend upon `List.at()`.
   * FIXME: This really evidences how horrid this `thing` API is.
  a_naughty = List.at(a_list, 0)->pointer.list;
  ASSERT( List.at(a_naughty, 0)->isa == LIST );
  ASSERT( List.at(a_naughty, 0)->pointer.list == a_naughty );
   */
  
  a_naughty = LL.at(a_list->content, 0)->thing->pointer.list;
  ASSERT( LL.at(a_naughty->content, 0)->thing->isa == LIST );
  ASSERT( LL.at(a_naughty->content, 0)->thing->pointer.list == a_naughty );
  
  return true;
}

CEST(list, to_thing) {
  list  a_list = List.create();
  thing a_thing;
  
  a_thing = List.to_thing(a_list);
  ASSERT( a_thing->isa          == LIST   );
  ASSERT( a_thing->pointer.list == a_list );
  
  return true;
}

CEST(list, insert) {
  list  a_list = List.create();
  thing thing1, thing2, thing3, thing4;
  
  thing1 = List.to_thing(List.create());
  thing2 = List.to_thing(List.create());
  thing3 = List.to_thing(List.create());
  thing4 = List.to_thing(List.create());
  
  /* This is a somewhat unusual situation… it shouldn’t often show up in
   * practice, but we’re going to remove the naughty, and reset the list to a
   * blank state, before proceeding. */
  a_list->content->first = NULL;
  a_list->content->last = NULL;
  a_list->content->length = 0;
  
  /* Insert into empty list */
  List.insert(a_list, thing2, 0);
  ASSERT( List.at(a_list, 0) == thing2 );
  ASSERT( a_list->content->length == 1 );
  
  /* Insert onto the front of list */
  List.insert(a_list, thing1, 0);
  ASSERT( List.at(a_list, 0) == thing1 );
  ASSERT( a_list->content->length == 2 );
  
  /* Insert onto the end of list */
  List.insert(a_list, thing4, 2);
  ASSERT( List.at(a_list, 2) == thing4 );
  ASSERT( a_list->content->length == 3 );
  
  /* Insert into list */
  List.insert(a_list, thing3, 2);
  ASSERT( List.at(a_list, 2) == thing3 );
  ASSERT( a_list->content->length == 4 );
  
  return true;
}

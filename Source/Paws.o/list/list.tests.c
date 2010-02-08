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

CEST(List, to_thing) {
  list  a_list;
  thing a_thing;
  
  a_list = List.create();
  a_thing = List.to_thing(a_list);
  ASSERT( a_thing->isa          == LIST   );
  ASSERT( a_thing->pointer.list == a_list );
  
  return true;
}

#include "ll.c"

/* FIXME: These shouldn’t depend on `list.c` */
#if !defined(LIST_H)
# include "Paws.o/list/list.h"
#endif

#if !defined(CEST_H)
# include "Cest.h"
#endif

#define A_LIST \
  List.to_thing(List.create())//;


CEST(LL, create) {
  ll  a_ll;
  
  a_ll = LL.create();
  ASSERT( a_ll->first  == NULL );
  ASSERT( a_ll->last   == NULL );
  ASSERT( a_ll->length == 0    );
  
  return true;
}

CEST(ll, anterior_insert) {
  ll        a_ll = LL.create();
  element   element1 = Element.create(A_LIST); LL.affix(a_ll, element1);
  element   element2 = Element.create(A_LIST); LL.affix(a_ll, element2);
  element   element3 = Element.create(A_LIST); LL.affix(a_ll, element3);
  
  element elementA = Element.create(A_LIST);
  
  /* TODO: Error condition */
  LL.anterior_insert(a_ll, elementA, 0);
  ASSERT( LL.at(a_ll, 0) == element1 );
  
  LL.anterior_insert(a_ll, elementA, 1);
  ASSERT( LL.at(a_ll, 0) == element1 );
  ASSERT( LL.at(a_ll, 1) == elementA );
  ASSERT( LL.at(a_ll, 2) == element2 );
  
  return true;
}

CEST(ll, posterior_insert) {
  ll        a_ll = LL.create();
  element   element1 = Element.create(A_LIST); LL.affix(a_ll, element1);
  element   element2 = Element.create(A_LIST); LL.affix(a_ll, element2);
  element   element3 = Element.create(A_LIST); LL.affix(a_ll, element3);
  
  element elementA = Element.create(A_LIST);
  
  /* TODO: Error condition */
  LL.posterior_insert(a_ll, elementA, a_ll->length);
  ASSERT( LL.at(a_ll, 0) == element1 );
  
  LL.posterior_insert(a_ll, elementA, 1);
  ASSERT( LL.at(a_ll, 0) == element1 );
  ASSERT( LL.at(a_ll, 1) == elementA );
  ASSERT( LL.at(a_ll, 2) == element2 );
  
  return true;
}

CEST(ll, prefix) {
  ll    a_ll = LL.create();
  element   element1 = Element.create(A_LIST),
            element2 = Element.create(A_LIST),
            element3 = Element.create(A_LIST);
  
  LL.prefix(a_ll, element3);
  ASSERT( a_ll->length == 1        );
  ASSERT( a_ll->first  == element3 );
  ASSERT( a_ll->last   == element3 );
  
  LL.prefix(a_ll, element2);
  ASSERT( a_ll->length == 2        );
  ASSERT( a_ll->first  == element2 );
  ASSERT( a_ll->last   == element3 );
  
  LL.prefix(a_ll, element1);
  ASSERT( a_ll->length == 3        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element3 );
  
  return true;
}

CEST(ll, affix) {
  ll    a_ll = LL.create();
  element   element1 = Element.create(A_LIST),
            element2 = Element.create(A_LIST),
            element3 = Element.create(A_LIST);
  
  LL.affix(a_ll, element1);
  ASSERT( a_ll->length == 1        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element1 );
  
  LL.affix(a_ll, element2);
  ASSERT( a_ll->length == 2        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element2 );
  
  LL.affix(a_ll, element3);
  ASSERT( a_ll->length == 3        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element3 );
  
  return true;
}

CEST(ll, at) {
  ll    a_ll = LL.create();
  
  /* Empty `ll`s */
  ASSERT( LL.at(a_ll,  5) == NULL );
  ASSERT( LL.at(a_ll,  1) == NULL );
  ASSERT( LL.at(a_ll,  0) == NULL );
  
  element   element1, element2, element3;
  element1 = Element.create(A_LIST); LL.affix(a_ll, element1);
  element2 = Element.create(A_LIST); LL.affix(a_ll, element2);
  element3 = Element.create(A_LIST); LL.affix(a_ll, element3);
  
  /* Positive indicies */
  ASSERT( LL.at(a_ll,  0) == element1 );
  ASSERT( LL.at(a_ll,  1) == element2 );
  ASSERT( LL.at(a_ll,  2) == element3 );
  
  /* OOB indicies */
  ASSERT( LL.at(a_ll,  5) == NULL );
  ASSERT( LL.at(a_ll,  4) == NULL );
  
  return true;
}


CEST(Element, create) {
  element  a_element;
  
  a_element = Element.create( A_LIST );
  ASSERT( a_element->next     == NULL );
  ASSERT( a_element->previous == NULL );
  
  return true;
}

CEST(element, prefix) {
  element   element1 = Element.create(A_LIST),
            element2 = Element.create(A_LIST),
            element3 = Element.create(A_LIST),
            elementA = Element.create(A_LIST),
            elementB = Element.create(A_LIST),
            elementC = Element.create(A_LIST);
  
  
  /* A basic single prefix */
  /* > [***] node3
   * 
   *         node1
   * > [***]    └→ node3
   * 
   * > [***] node1 node3
   */
  Element.prefix(element3, element1);
  ASSERT( element1->previous == NULL     && element1->next == element3 );
  ASSERT( element3->previous == element1 && element3->next == NULL     );
  
  
  /* A single prefix that pushes old nodes */
  /* > [***] node1 node3
   * 
   *               node2
   * > [***] node1    └→ node3
   * 
   * > [***] node1 node2 node3
   */
  Element.prefix(element3, element2);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  
  Element.affix(elementA, elementB);
  Element.affix(elementB, elementC);
  
  /* A splicing-prefix that pushes old nodes */
  /* > [***] node1 node2 node3
   * 
   * > [***] nodeA nodeB nodeC
   * > [***] node1    └→ node2 node3
   * 
   * > [***] nodeA nodeB node2 node3
   *   [***] node1   …   [***] nodeC
   */
  Element.prefix(element2, elementB);
  ASSERT( elementA->previous == NULL     && elementA->next == elementB );
  ASSERT( elementB->previous == elementA && elementB->next == element2 );
  ASSERT( element2->previous == elementB && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  ASSERT( elementC->previous != elementB );
  ASSERT( element1->next     != element2 );
  
  
  return true;
}

CEST(element, affix) {
  element   element1 = Element.create(A_LIST),
            element2 = Element.create(A_LIST),
            element3 = Element.create(A_LIST),
            elementA = Element.create(A_LIST),
            elementB = Element.create(A_LIST),
            elementC = Element.create(A_LIST);
  
  
  /* A basic single affix */
  /* > node1 [***]
   * 
   *         node3
   * > node1 ←┘    [***]
   * 
   * > node1 node3 [***]
   */
  Element.affix(element1, element3);
  ASSERT( element1->previous == NULL     && element1->next == element3 );
  ASSERT( element3->previous == element1 && element3->next == NULL     );
  
  
  /* A single affix that pushes old nodes */
  /* > node1 node3 [***]
   * 
   *         node2
   * > node1 ←┘    node3 [***]
   * 
   * > node1 node2 node3 [***]
   */
  Element.affix(element1, element2);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  
  Element.affix(elementA, elementB);
  Element.affix(elementB, elementC);
  
  /* A splicing-affix that pushes old nodes */
  /* > node1 node2 node3 [***]
   * 
   *       > nodeA nodeB nodeC [***]
   * > node1 node2 ←┘          node3 [***]
   * 
   * > node1 node2 nodeB nodeC [***]
   *   nodeA [***]   …   node3 [***]
   */
  Element.affix(element2, elementB);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == elementB );
  ASSERT( elementB->previous == element2 && elementB->next == elementC );
  ASSERT( elementC->previous == elementB && elementC->next == NULL     );
  
  ASSERT( element3->previous != element2 );
  ASSERT( elementA->next     != elementB );
  
  
  return true;
}

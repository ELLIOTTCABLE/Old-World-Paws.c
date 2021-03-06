#include "ll.c"

#define DECLARATIONS
# include "Cest.c"

# include <string.h>
#undef  DECLARATIONS


#define SOMETHING \
  _make_something()//;

thing _make_something(void) {
  struct thing something = { .isa = LIST, .pointer = { .list = NULL } };
  
  return something;
}

CEST(LL, allocate) {
  ll    a_ll;
  
  a_ll = LL->allocate();
  ASSERT( a_ll->first  == NULL );
  ASSERT( a_ll->last   == NULL );
  ASSERT( a_ll->length == 0    );
  
  SUCCEED;
}

CEST(ll, anterior_insert) {
  ll        a_ll = LL->allocate();
  element   element1 = Element->allocate(SOMETHING); LL->affix(a_ll, element1);
  element   element2 = Element->allocate(SOMETHING); LL->affix(a_ll, element2);
  element   element3 = Element->allocate(SOMETHING); LL->affix(a_ll, element3);
  element   elementA = Element->allocate(SOMETHING);
  
  /* TODO: Error condition */
  LL->anterior_insert(a_ll, elementA, 0);
  ASSERT( LL->at(a_ll, 0) == element1 );
  
  LL->anterior_insert(a_ll, elementA, 1);
  ASSERT( LL->at(a_ll, 0) == element1 );
  ASSERT( LL->at(a_ll, 1) == elementA );
  ASSERT( LL->at(a_ll, 2) == element2 );
  
  SUCCEED;
}

CEST(ll, posterior_insert) {
  ll        a_ll = LL->allocate();
  element   element1 = Element->allocate(SOMETHING); LL->affix(a_ll, element1);
  element   element2 = Element->allocate(SOMETHING); LL->affix(a_ll, element2);
  element   element3 = Element->allocate(SOMETHING); LL->affix(a_ll, element3);
  
  element   elementA = Element->allocate(SOMETHING);
  
  /* TODO: Error condition */
  LL->posterior_insert(a_ll, elementA, a_ll->length);
  ASSERT( LL->at(a_ll, 0) == element1 );
  
  LL->posterior_insert(a_ll, elementA, 1);
  ASSERT( LL->at(a_ll, 0) == element1 );
  ASSERT( LL->at(a_ll, 1) == elementA );
  ASSERT( LL->at(a_ll, 2) == element2 );
  
  SUCCEED;
}

CEST(ll, prefix) {
  ll        a_ll = LL->allocate();
  element   element1 = Element->allocate(SOMETHING),
            element2 = Element->allocate(SOMETHING),
            element3 = Element->allocate(SOMETHING);
  
  LL->prefix(a_ll, element3);
  ASSERT( a_ll->length == 1        );
  ASSERT( a_ll->first  == element3 );
  ASSERT( a_ll->last   == element3 );
  
  LL->prefix(a_ll, element2);
  ASSERT( a_ll->length == 2        );
  ASSERT( a_ll->first  == element2 );
  ASSERT( a_ll->last   == element3 );
  
  LL->prefix(a_ll, element1);
  ASSERT( a_ll->length == 3        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element3 );
  
  SUCCEED;
}

CEST(ll, affix) {
  ll        a_ll = LL->allocate();
  element   element1 = Element->allocate(SOMETHING),
            element2 = Element->allocate(SOMETHING),
            element3 = Element->allocate(SOMETHING);
  
  LL->affix(a_ll, element1);
  ASSERT( a_ll->length == 1        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element1 );
  
  LL->affix(a_ll, element2);
  ASSERT( a_ll->length == 2        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element2 );
  
  LL->affix(a_ll, element3);
  ASSERT( a_ll->length == 3        );
  ASSERT( a_ll->first  == element1 );
  ASSERT( a_ll->last   == element3 );
  
  SUCCEED;
}

CEST(ll, at) {
  ll    a_ll = LL->allocate();
  
  /* Empty `ll`s */
  ASSERT( LL->at(a_ll,  5) == NULL );
  ASSERT( LL->at(a_ll,  1) == NULL );
  ASSERT( LL->at(a_ll,  0) == NULL );
  
  element   element1 = Element->allocate(SOMETHING); LL->affix(a_ll, element1);
  element   element2 = Element->allocate(SOMETHING); LL->affix(a_ll, element2);
  element   element3 = Element->allocate(SOMETHING); LL->affix(a_ll, element3);
  
  /* Positive indicies */
  ASSERT( LL->at(a_ll,  0) == element1 );
  ASSERT( LL->at(a_ll,  1) == element2 );
  ASSERT( LL->at(a_ll,  2) == element3 );
  
  /* OOB indicies */
  ASSERT( LL->at(a_ll,  5) == NULL );
  ASSERT( LL->at(a_ll,  4) == NULL );
  
  SUCCEED;
}


CEST(Element, allocate) {
  element   a_element;
  
  a_element = Element->allocate( SOMETHING );
  ASSERT( a_element->next     == NULL );
  ASSERT( a_element->previous == NULL );
  
  SUCCEED;
}

CEST(element, prefix) {
  element   element1 = Element->allocate(SOMETHING),
            element2 = Element->allocate(SOMETHING),
            element3 = Element->allocate(SOMETHING),
            elementA = Element->allocate(SOMETHING),
            elementB = Element->allocate(SOMETHING),
            elementC = Element->allocate(SOMETHING);
  
  
  /* A basic single prefix */
  /* > [***] node3
   * 
   *         node1
   * > [***]    └→ node3
   * 
   * > [***] node1 node3
   */
  Element->prefix(element3, element1);
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
  Element->prefix(element3, element2);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  
  Element->affix(elementA, elementB);
  Element->affix(elementB, elementC);
  
  /* A splicing-prefix that pushes old nodes */
  /* > [***] node1 node2 node3
   * 
   * > [***] nodeA nodeB nodeC
   * > [***] node1    └→ node2 node3
   * 
   * > [***] nodeA nodeB node2 node3
   *   [***] node1   …   [***] nodeC
   */
  Element->prefix(element2, elementB);
  ASSERT( elementA->previous == NULL     && elementA->next == elementB );
  ASSERT( elementB->previous == elementA && elementB->next == element2 );
  ASSERT( element2->previous == elementB && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  ASSERT( elementC->previous != elementB );
  ASSERT( element1->next     != element2 );
  
  
  SUCCEED;
}

CEST(element, affix) {
  element   element1 = Element->allocate(SOMETHING),
            element2 = Element->allocate(SOMETHING),
            element3 = Element->allocate(SOMETHING),
            elementA = Element->allocate(SOMETHING),
            elementB = Element->allocate(SOMETHING),
            elementC = Element->allocate(SOMETHING);
  
  
  /* A basic single affix */
  /* > node1 [***]
   * 
   *         node3
   * > node1 ←┘    [***]
   * 
   * > node1 node3 [***]
   */
  Element->affix(element1, element3);
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
  Element->affix(element1, element2);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == element3 );
  ASSERT( element3->previous == element2 && element3->next == NULL     );
  
  
  Element->affix(elementA, elementB);
  Element->affix(elementB, elementC);
  
  /* A splicing-affix that pushes old nodes */
  /* > node1 node2 node3 [***]
   * 
   *       > nodeA nodeB nodeC [***]
   * > node1 node2 ←┘          node3 [***]
   * 
   * > node1 node2 nodeB nodeC [***]
   *   nodeA [***]   …   node3 [***]
   */
  Element->affix(element2, elementB);
  ASSERT( element1->previous == NULL     && element1->next == element2 );
  ASSERT( element2->previous == element1 && element2->next == elementB );
  ASSERT( elementB->previous == element2 && elementB->next == elementC );
  ASSERT( elementC->previous == elementB && elementC->next == NULL     );
  
  ASSERT( element3->previous != element2 );
  ASSERT( elementA->next     != elementB );
  
  
  SUCCEED;
}

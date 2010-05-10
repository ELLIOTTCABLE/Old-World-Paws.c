#include "ast.c"
#include "Cest.h"


CEST(Node, create) {
  node    a_node;
  
  a_node = Node->create(SCOPE);
  ASSERT( a_node->start     == 0 );
  ASSERT( a_node->end       == 0 );
  ASSERT( a_node->archetype == NULL );
  ASSERT( a_node->size      == 0 );
  ASSERT( a_node->content   == NULL );
  
  ASSERT( a_node->type == SCOPE );
  a_node = Node->create(EXPRESSION);
  ASSERT( a_node->type == EXPRESSION );
  a_node = Node->create(WORD);
  ASSERT( a_node->type == WORD );
  
  SUCCEED;
}

CEST(Node, create_scope) {
  node    a_scope;
  
  a_scope = Node->create_scope();
  ASSERT( a_scope->type == SCOPE );
  
  SUCCEED;
}

CEST(Node, create_expression) {
  node    a_expression;
  
  a_expression = Node->create_expression();
  ASSERT( a_expression->type == EXPRESSION );
  
  SUCCEED;
}

CEST(Node, create_word) {
  node    a_word;
  
  a_word = Node->create_word("foo", 4);
  ASSERT( a_word->type == WORD );
  ASSERT( a_word->size == 4 );
  
  ASSERT( strcmp(a_word->content, "foo") == 0 );
  
  SUCCEED;
}

CEST(node, insert) {
  node    parent = Node->create_expression(),
          child1 = Node->create_word("foo", 4),
          child2 = Node->create_word("bar", 4),
          child3 = Node->create_word("baz", 4);
  
  
  Node->insert(parent, child1, 0);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( parent->size == 1 );
  
  Node->insert(parent, child3, 1);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( *((node *)parent->content + 1) == child3 );
  ASSERT( parent->size == 2 );
  
  Node->insert(parent, child2, 1);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( *((node *)parent->content + 1) == child2 );
  ASSERT( *((node *)parent->content + 2) == child3 );
  ASSERT( parent->size == 3 );
  
  SUCCEED;
}

CEST(node, prefix) {
  node    parent = Node->create_expression(),
          child1 = Node->create_word("foo", 4),
          child2 = Node->create_word("bar", 4),
          child3 = Node->create_word("baz", 4);
  
  Node->prefix(parent, child3);
  ASSERT( *((node *)parent->content + 0) == child3 );
  ASSERT( parent->size == 1 );
  
  Node->prefix(parent, child2);
  ASSERT( *((node *)parent->content + 0) == child2 );
  ASSERT( *((node *)parent->content + 1) == child3 );
  ASSERT( parent->size == 2 );
  
  Node->prefix(parent, child1);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( *((node *)parent->content + 1) == child2 );
  ASSERT( *((node *)parent->content + 2) == child3 );
  ASSERT( parent->size == 3 );
  
  SUCCEED;
}

CEST(node, affix) {
  node    parent = Node->create_expression(),
          child1 = Node->create_word("foo", 4),
          child2 = Node->create_word("bar", 4),
          child3 = Node->create_word("baz", 4);
  
  Node->affix(parent, child1);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( parent->size == 1 );
  
  Node->affix(parent, child2);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( *((node *)parent->content + 1) == child2 );
  ASSERT( parent->size == 2 );
  
  Node->affix(parent, child3);
  ASSERT( *((node *)parent->content + 0) == child1 );
  ASSERT( *((node *)parent->content + 1) == child2 );
  ASSERT( *((node *)parent->content + 2) == child3 );
  ASSERT( parent->size == 3 );
  
  SUCCEED;
}

CEST(node, at) {
  node    parent = Node->create_expression(),
          child1 = Node->create_word("foo", 4),
          child2 = Node->create_word("bar", 4),
          child3 = Node->create_word("baz", 4);
  
  Node->affix(parent, child1);
  Node->affix(parent, child2);
  Node->affix(parent, child3);
  
  ASSERT( Node->at(parent, 0) == child1 );
  ASSERT( Node->at(parent, 1) == child2 );
  ASSERT( Node->at(parent, 2) == child3 );
  
  SUCCEED;
}

CEST(node, native) {
  node    a_word;
  
  a_word = Node->create_word("foo", 4);
  ASSERT( strcmp(Node->native(a_word), "foo") == 0 );
  
  SUCCEED;
}

CEST(node, duplicate) {
  node    a_word = Node->create_word("foo", 4), another_word;
  
  another_word = Node->duplicate(a_word);
  ASSERT( another_word            != a_word );
  ASSERT( another_word->archetype == NULL );
  
  ASSERT( another_word->type == WORD );
  ASSERT( another_word->size == 4 );
  
  ASSERT( strcmp(another_word->content, "foo") == 0 );
  
  
  node    an_expression = Node->create_expression(), another_expression,
          child1 = Node->create_word("foo", 4),
          child2 = Node->create_word("bar", 4),
          child3 = Node->create_word("baz", 4);
  
  Node->affix(an_expression, child1);
  Node->affix(an_expression, child2);
  Node->affix(an_expression, child3);
  
  another_expression = Node->duplicate(an_expression);
  ASSERT( another_expression            != an_expression );
  ASSERT( another_expression->archetype == NULL );
  
  ASSERT( another_expression->type == EXPRESSION );
  ASSERT( another_expression->size == 3 );
  
  ASSERT( Node->at(another_expression, 0)            != child1 );
  ASSERT( Node->at(another_expression, 0)->archetype == NULL );
  ASSERT( Node->at(another_expression, 1)            != child2 );
  ASSERT( Node->at(another_expression, 1)->archetype == NULL );
  ASSERT( Node->at(another_expression, 2)            != child3 );
  ASSERT( Node->at(another_expression, 2)->archetype == NULL );
  
  ASSERT( strcmp(Node->at(another_expression, 0)->content, "foo") == 0 );
  ASSERT( strcmp(Node->at(another_expression, 1)->content, "bar") == 0 );
  ASSERT( strcmp(Node->at(another_expression, 2)->content, "baz") == 0 );
  
  SUCCEED;
}

CEST(node, instantiate) {
  node    a_word = Node->create_word("foo", 4), another_word;
  
  another_word = Node->instantiate(a_word);
  ASSERT( another_word            != a_word );
  ASSERT( another_word->archetype == a_word );
  
  ASSERT( another_word->type == WORD );
  ASSERT( another_word->size == 4 );
  
  ASSERT( strcmp(another_word->content, "foo") == 0 );
  
  
  node    an_expression = Node->create_expression(), another_expression,
          child1 = Node->create_word("foo", 4),
          child2 = Node->create_word("bar", 4),
          child3 = Node->create_word("baz", 4);
  
  Node->affix(an_expression, child1);
  Node->affix(an_expression, child2);
  Node->affix(an_expression, child3);
  
  another_expression = Node->instantiate(an_expression);
  ASSERT( another_expression            != an_expression );
  ASSERT( another_expression->archetype == an_expression );
  
  ASSERT( another_expression->type == EXPRESSION );
  ASSERT( another_expression->size == 3 );
  
  ASSERT( Node->at(another_expression, 0)            != child1 );
  ASSERT( Node->at(another_expression, 0)->archetype == child1 );
  ASSERT( Node->at(another_expression, 1)            != child2 );
  ASSERT( Node->at(another_expression, 1)->archetype == child2 );
  ASSERT( Node->at(another_expression, 2)            != child3 );
  ASSERT( Node->at(another_expression, 2)->archetype == child3 );
  
  ASSERT( strcmp(Node->at(another_expression, 0)->content, "foo") == 0 );
  ASSERT( strcmp(Node->at(another_expression, 1)->content, "bar") == 0 );
  ASSERT( strcmp(Node->at(another_expression, 2)->content, "baz") == 0 );
  
  SUCCEED;
}

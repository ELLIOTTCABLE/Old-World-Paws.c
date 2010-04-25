#include "ast.c"

#if !defined(CEST_H)
# include "Cest.h"
#endif


CEST(Node, create) {
  node    a_node;
  
  a_node = Node.create(SCOPE);
  ASSERT( a_node->start     == 0 );
  ASSERT( a_node->end       == 0 );
  ASSERT( a_node->archetype == NULL );
  ASSERT( a_node->size      == 0 );
  ASSERT( a_node->content   == NULL );
  
  ASSERT( a_node->type == SCOPE );
  a_node = Node.create(EXPRESSION);
  ASSERT( a_node->type == EXPRESSION );
  a_node = Node.create(WORD);
  ASSERT( a_node->type == WORD );
  
  return true;
}

CEST(Node, create_scope) {
  node    a_scope;
  
  a_scope = Node.create_scope();
  ASSERT( a_scope->type == SCOPE );
  
  return true;
}

CEST(Node, create_expression) {
  node    a_expression;
  
  a_expression = Node.create_expression();
  ASSERT( a_expression->type == EXPRESSION );
  
  return true;
}

CEST(Node, create_word) {
  node    a_word;
  
  a_word = Node.create_word("foo", 4);
  ASSERT( a_word->type == WORD );
  ASSERT( a_word->size == 4 );
  
  ASSERT( strcmp(a_word->content, "foo") == 0 );
  
  return true;
}

CEST(node, insert) {
  return false;
}

CEST(node, prefix) {
  return false;
}

CEST(node, affix) {
  return false;
}

CEST(node, at) {
  return false;
}

CEST(node, native) {
  node    a_word;
  
  a_word = Node.create_word("foo", 4);
  ASSERT( strcmp(Node.native(a_word), "foo") == 0 );
  
  return true;
}

CEST(node, instantiate) {
  return false;
}

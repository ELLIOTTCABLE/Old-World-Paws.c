#include "ast.h"

#include <stdlib.h>
#include <string.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM, BYTES) \
  strncpy(TO, FROM, BYTES); TO[BYTES - 1] = '\0'


/* ======
= `ast` =
====== */

/* ### Method Declarations ### */

node    Node__create              (enum node_type type);
node    Node__create_scope        (void);
node    Node__create_expression   (void);
node    Node__create_word         (char *content, node_size bytes);

void    node__insert              (node this, node child, node_size index);
void    node__prefix              (node this, node child);
void    node__affix               (node this, node child);
node    node__at                  (node this,             node_size index);
char*   node__native              (node this);
node    node__instantiate         (node this);

struct Node const Node = {
  .create               = Node__create,
  .create_scope         = Node__create_scope,
  .create_expression    = Node__create_expression,
  .create_word          = Node__create_word,
  
  .prefix               = node__prefix,
  .affix                = node__affix,
  .at                   = node__at,
  .native               = node__native,
  .instantiate          = node__instantiate
};


/* ### Method Implementations ### */

/* This method initializes a new `node`, with no children. All values are
 * initialized to either `NULL` or zero.
 * 
 * You really should not be using this method; the respective `create_*`
 * method for the type of node you actually need is far more appropriate.
 */
node Node__create(enum node_type type) {
  node this = malloc(sizeof(struct node));
  
  this->type = type;
  
  this->start = 0;
  this->end   = 0;
  
  this->archetype = NULL;
  
  this->size    = 0;
  this->content = NULL;
  
  return this;
}

/* This method initializes a new `node` with `.type` set to `SCOPE`. */
node Node__create_scope(void) {
  node this = Node.create(SCOPE);
  
  return this;
}

/* This method initializes a new `node` with `.type` set to `EXPRESSION`. */
node Node__create_expression(void) {
  node this = Node.create(EXPRESSION);
  
  return this;
}

/* This method initializes a new `node` with `.type` set to `WORD`, and then
 * initializes the `.content` to an empty cstring. */
node Node__create_word(char *content, node_size bytes) {
  node this = Node.create(WORD);
  
  char *copy = malloc(bytes);
  STRCPY(copy, content, bytes);
  this->content = copy;
  
  this->size = bytes;
  
  return this;
}

void node__insert(node this, node child, node_size index) {
  
}

void node__prefix(node this, node child) {
  
}

void node__affix(node this, node child) {
  
}

node node__at(node this, node_size index) {
  return this; /* lol */
}

char* node__native(node this) {
  return this->content;
}

node node__instantiate(node this) {
  return this; /* lol */
}

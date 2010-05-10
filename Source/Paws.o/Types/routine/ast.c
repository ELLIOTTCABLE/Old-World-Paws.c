#include "ast.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM, BYTES) \
  strncpy(TO, FROM, BYTES); TO[BYTES - 1] = '\0'


/* ======
= `ast` =
====== */

/* ### Method Declarations ### */

                         struct AST // »
                               *AST   = NULL;
void Paws__register_AST(void) { AST   = malloc(sizeof(struct AST));
  
  struct AST // »
  data = { .nothing = NULL };
  
  memcpy(AST, &data, sizeof(struct AST));
}

node    Node__create              (enum node_type type);
node    Node__create_scope        (void);
node    Node__create_expression   (void);
node    Node__create_word         (char *content, node_size bytes);

void    node__insert              (node this, node child, node_size index);
void    node__prefix              (node this, node child);
void    node__affix               (node this, node child);
node    node__at                  (node this,             node_size index);
char*   node__native              (node this);
node    node__duplicate           (node this);
node    node__instantiate         (node this);

                          struct Node // »
                                *Node   = NULL;
void Paws__register_Node(void) { Node   = malloc(sizeof(struct Node));
  
  struct Node // »
  data = {
    .create               = Node__create,
    .create_scope         = Node__create_scope,
    .create_expression    = Node__create_expression,
    .create_word          = Node__create_word,
    
    .insert               = node__insert,
    .prefix               = node__prefix,
    .affix                = node__affix,
    .at                   = node__at,
    .native               = node__native,
    .duplicate            = node__duplicate,
    .instantiate          = node__instantiate
  };
  
  memcpy(Node, &data, sizeof(struct Node));
}


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
  node this = Node->create(SCOPE);
  
  return this;
}

/* This method initializes a new `node` with `.type` set to `EXPRESSION`. */
node Node__create_expression(void) {
  node this = Node->create(EXPRESSION);
  
  return this;
}

/* This method initializes a new `node` with `.type` set to `WORD`, and then
 * initializes the `.content` to an empty cstring. */
node Node__create_word(char *content, node_size bytes) {
  node this = Node->create(WORD);
  
  char *copy = malloc(bytes);
  STRCPY(copy, content, bytes);
  this->content = copy;
  
  this->size = bytes;
  
  return this;
}

void node__insert(node this, node child, node_size index) {
  /* TODO: Flip a nut if `this` isn’t an `SCOPE` or `EXPRESSION`.
     TODO: Flip a nut if `this` is a `SCOPE` and `child` is a `WORD`.
     TODO: Flip a nut if `size` is smaller than `index`.
     TODO: Merge `Node->prefix()` and `Node->affix()` into this. */
  
  node *children = malloc(sizeof(node) * this->size + 1);
  
  memcpy(children + 0,         (node *)this->content,         sizeof(node) * index);
       *(children + index) =           child;
  memcpy(children + index + 1, (node *)this->content + index, sizeof(node) * (this->size - index));
  
  this->content = children;
  this->size++;
}

void node__prefix(node this, node child) {
  /* TODO: Flip a nut if `this` isn’t an `SCOPE` or `EXPRESSION`.
     TODO: Flip a nut if `this` is a `SCOPE` and `child` is a `WORD`. */
  
  node *children = malloc(sizeof(node) * this->size + 1);
  memcpy(children + 1, this->content, sizeof(node) * this->size);
  children[0] = child;
  
  this->content = children;
  this->size++;
}

void node__affix(node this, node child) {
  /* TODO: Flip a nut if `this` isn’t an `SCOPE` or `EXPRESSION`.
     TODO: Flip a nut if `this` is a `SCOPE` and `child` is a `WORD`. */
  
  node *children = malloc(sizeof(node) * this->size + 1);
  memcpy(children, this->content, sizeof(node) * this->size);
  children[this->size] = child;
  
  this->content = children;
  this->size++;
}

node node__at(node this, node_size index) {
  /* TODO: Flip a nut if `this` isn’t an `SCOPE` or `EXPRESSION`.
     TODO: Flip a nut if `size` is smaller than `index`. */
  
  return *((node *)this->content + index);
}

char* node__native(node this) {
  /* TODO: Flip a nut if `this` isn’t a `WORD`. */
  
  return this->content;
}

node _node__duplicate  (node this, bool set_archetype);
node  node__duplicate  (node this) { return _node__duplicate(this, false); }
node  node__instantiate(node this) { return _node__duplicate(this, true);  }

node _node__duplicate(node this, bool set_archetype) {
  node new;
  
  if (this->type == WORD)
    new = Node->create_word(this->content, this->size);
  else {
    /* FIXME: If we use `Node->create_word()` here, we should use
              `Node->create_scope()` and `Node->create_expression()` as well. */
    new = Node->create(this->type);
    node *children = malloc(sizeof(node) * this->size);
    for (node_size i = 0; i < this->size; ++i)
      children[i] = _node__duplicate(((node *)this->content)[i], set_archetype);
    new->content = children; new->size = this->size;
  }
  
  if(set_archetype)
    new->archetype = this;
  
  return new;
}

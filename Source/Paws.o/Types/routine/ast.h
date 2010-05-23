#define AST_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif


/* ======
= `ast` =
====== */

/* ### Data Types & Structures ### */

        struct E(ast); /* Our code storage system (an abstract syntax tree) */
        struct E(node); /* A single node of an `ast` */
typedef struct E(ast)* E(ast);
typedef struct E(node)* E(node);

typedef   unsigned long long int     E(ast_size); /* The maximum storable character index into a Paws document */
typedef   unsigned           int    E(node_size); /* The maximum storable character index into a `WORD` node, as well as the maximum descendants to a node */

/* This name is reserved, but unused */
struct E(ast) { void *nothing; };

struct E(node) {
  enum E(node_type) { E(SCOPE), E(EXPRESSION), E(WORD) } //»
                  type; /* The node’s ‘type’ */
  
  E(ast_size)     start; /* The character index of the start of this node */
  E(ast_size)     end; /* The character index of the end of this node */
  
  E(node)         archetype; /* The prototype of this node. */ 
  
  E(node_size)    size; /* The number of child nodes, or the bytes in this `WORD` */
  void           *content; /* A meta-pointer to the first child node, or to the cstring */
};

/* ### Method Declarations ### */

/* This name is reserved, but unused */
struct E(AST) { void (*nothing)(void); };
#if !defined(EXTERNALIZE)
  struct E(AST) extern *AST;
#endif

struct E(Node) {
  /* `Node` functions */
  E(node)   (*allocate)       ( enum E(node_type) type );
  E(node)   (*scope)          ( void );
  E(node)   (*expression)     ( void );
  E(node)   (*word)           ( char *content, E(node_size) bytes );
  
  /* `struct node` methods */
  void      (*insert)         ( E(node) this, E(node) child, E(node_size) index );
  void      (*prefix)         ( E(node) this, E(node) child );
  void      (*affix)          ( E(node) this, E(node) child );
  E(node)   (*at)             ( E(node) this,                E(node_size) index );
  char*     (*native)         ( E(node) this );
  E(node)   (*duplicate)      ( E(node) this );
  E(node)   (*instantiate)    ( E(node) this );
};
#if !defined(EXTERNALIZE)
  struct E(Node) extern *Node;
#endif

void    Paws__register_AST    ( void );
void    Paws__register_Node   ( void );

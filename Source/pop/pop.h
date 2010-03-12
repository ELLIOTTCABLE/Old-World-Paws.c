typedef  unsigned long long int  pop_size; /* The maximum length of a processing unit */
typedef  unsigned long long int  ast_size; /* The maximum children of a single node of a processing unit, or the maxiumum characters in a node’s textual content */

/* A `pop` handling-unit; generally, a single file. */
typedef struct pop {
  enum { PROCESSING_SCOPES, CONSTRUCTING_AST, PROCESSING_COMPLETE } state;
  
  pop_size seen; /* The character index into the processing unit as seen so far */
  pop_size size; /* The character index representing the end of the processing unit */
  
  struct pop_scope_node {
    unsigned char marker_length; /* The number of delimiting whitespace characters (zero represents a literal ‘{…}’) */
    pop_size start; /* The processing unit character index of the scope’s starting character */
    pop_size end; /* The processing unit character index of the scope’s ending character */
    
    ast_size size; /* The number of nested scopes */
    struct pop_scope_node *children; /* An array of nested scopes */
  } *scope;
  
  struct pop_ast_node {
    enum {
      DOCUMENT_NODE,
      SCOPE_NODE,
      EXPRESSION_NODE,
      WORD_NODE
    } type; /* The ‘type’ of the node */
    
    ast_size size; /* Either the number of characters in the textual content, or the number of child nodes */
    void *content; /* A pointer to either the textual content of the node, or an array of children nodes */
  } *ast;
  
} *pop;

struct POP {
  /* `POP` functions */
  pop   (*create)   ( void );
  
  /* `struct pop` methods */
  void      (*process)      ( pop this, char *data, pop_size bytes );
  void      (*process_file) ( pop this, char const filename[] );
  void      (*close)        ( pop this );
} extern const POP;

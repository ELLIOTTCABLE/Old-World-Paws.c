#include "pop.h"

#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


pop     POP__create         (void);

void    pop__process        (pop this, char *data, pop_size bytes);
void    pop__process_file   (pop this, char const filename[]);
void    pop__close          (pop this);

struct POP const POP = {
  .create         = POP__create,
  
  .process        = pop__process,
  .process_file   = pop__process_file,
  .close          = pop__close
};

/* This method creates a new `pop` struct, and initializes all the members to their basic values. The members
 * will be further initialized and manipulated, based on input, by `POP.process()`. */
pop POP__create(void) {
  /* LEAK: Duh. */
  pop this = malloc(sizeof(struct pop));
  
  /* TODO: Can we use an initializer literal here? */
  this->state = PROCESSING_SCOPES;
  
  this->seen = 0;
  this->size = 0;
  
  
  this->scope = malloc(sizeof(struct pop_scope_node));
  
  /* This *would* represent a `{}` literal, anywhere but at the root. */
  this->scope->marker_length = 0;
  this->scope->start = 0;
  this->scope->end = 0;
  
  this->scope->size = 0;
  this->scope->children = NULL;
  
  
  this->ast = malloc(sizeof(struct pop_ast_node));
  
  this->ast->type = DOCUMENT_NODE;
  
  this->ast->size = 0;
  this->ast->content = NULL;
  
  return this;
}

/* This method accepts some `char` data, and iterates over the involved characters, modifying a `pop`
 * accordingly.
 * 
 * Every piece of data must eventually be passed to this function *twice*, because it has to iterate the
 * character data twice to determine routine literals’ nesting and start/end points. */
void pop__process(pop this, char *data, pop_size bytes) {
  if (this->state == PROCESSING_SCOPES) {
    /* First, we get the current scope… */
    struct {
      ast_size size;
      struct pop_scope_node **content;
    } stack;
    stack.size = 1;
    stack.content = malloc(sizeof(struct pop_scope_node*));
    stack.content[0] = this->scope;
    
    struct pop_scope_node *s;
    while (s = stack.content[stack.size - 1], s->size != 0 && s->children[s->size - 1].end == 0) {
      stack.content = realloc(stack.content, sizeof(struct pop_scope_node*) * ++stack.size);
      stack.content[stack.size - 1] = s->children + (s->size - 1);
    }
    
    /* Now we iterate over the character data given us, building upon our existing scope tree. */
    for (pop_size i = 0; i < bytes; ++i, ++this->seen, ++this->size, ++this->scope->end) {
      if (data[i] == '{') {
        /* If we see an opening bracket, we’re going to create a new scope, store it on the currently ‘open’
         * scope (off the top of the stack), and then put a pointer to *it* on the stack. */
        struct pop_scope_node *current_scope;
        
        /* `current_scope` is set to the pointer on top of the stack, and we then screw with the scope-node
         * pointed at by that, to add a new child. */
        current_scope = stack.content[stack.size - 1];
        current_scope->size++;
        current_scope->children = realloc(current_scope->children,
          sizeof(struct pop_scope_node) * current_scope->size);
        /* Now we realloc the stack to put a pointer to this new scope on top of it, while incrementing the
         * stack’s size */
        stack.content = realloc(stack.content, sizeof(struct pop_scope_node*) * ++stack.size);
        /* FIXME: Is this safe? `current_scope` hasn’t been re-defined by the time we reference it, correct? */
        current_scope = stack.content[stack.size - 1] = current_scope->children + (current_scope->size - 1);
        
        /* Finally, we initialize the *data* for the new scope’s memory */
        current_scope->marker_length = 0;
        current_scope->start = this->seen;
        current_scope->end = 0;
        
        current_scope->size = 0;
        current_scope->children = NULL;
      } else if (data[i] == '}') {
        /* When we see a *closing* bracket, we close the last/top ‘open’ scope from the nesting tree. We don’t
         * realloc here, because we don’t care if a little extra memory with old stack entries is left hanging
         * around. Next time a *new* stack element is added, it will be forcibly realloc’d to the necessary size
         * anyway, thus destroying these useless old references. */
        stack.content[--stack.size]->end = this->seen;
      }
    }
    
    free(stack.content);
    return;
  } else if (this->state == CONSTRUCTING_AST) {
    /* TODO: This. */
    
    return;
  } else {
    /* TODO: This. */
    
    return;
  }
}

/* This function reads the contents of a file into a `pop`. It is identical to reading portions of the file, and
 * passing them to `POP.process()` sequentially. It is merely provided as a convenience. */
void pop__process_file(pop this, char const filename[]) {
  char buffer[64];
  int fd = open(filename, O_RDONLY);
  
  int bytes;
  while (bytes = read(fd, buffer, 64))
    POP.process(this, buffer, bytes);
  
  POP.close(this);
  
  return;
}

/* Private method that deallocates the memory used in a `pop_scope_node` */
void pop__dealloc_scope(struct pop_scope_node *this) {
  for (int i = 0; i < this->size; ++i)
    pop__dealloc_scope(this->children + i);
  free(this->children);
}

/* This function preforms three disparate actions, depending on the state of the `pop`. The first time you call
 * this function on a `pop`, you’re indicating that you have reached the end of the data you intend to process.
 * This will modify the `pop`, such that subsequent `POP.process()` calls will instead begin to build an AST.
 * 
 * The second time, you are indicating that you have passed in all of the data you intend to process for the
 * *second* time, thus having completed the construction of the AST. The scope nesting structures will be
 * deallocated, leaving a constructed `pop->ast` for you to do with as you please.
 * 
 * The final time you call this function, you indicate that you are entirely done with the `pop`, and the entire
 * thing (including the AST) will be deallocated and destroyed. Only do this when you no longer require access to
 * the constructed AST. */
void pop__close(pop this) {
  switch (this->state) {
    case PROCESSING_SCOPES:
      break;
    case CONSTRUCTING_AST:
      pop__dealloc_scope(this->scope);
      free(this->scope);
      this->scope = NULL;
      
      break;
    case PROCESSING_COMPLETE:
      /* TODO: This. */
      
      break;
  }
  
  this->state++;
  return;
}


int main(int count, char const **arguments) {
  if (count < 2) {
    printf("You failed to provide a filename!\n", stdout);
    exit(EXIT_FAILURE);
  }
  
  pop this = POP.create();
  POP.process_file(this, arguments[1]);
  POP.process_file(this, arguments[1]);
  
  /* breakpoint */
  
  POP.close(this);
  
  return 0;
}

#if !defined(CEST_DECLARATIONS)
# define     CEST_DECLARATIONS

#define constructor __attribute__((constructor))
#define CEST(NAMESPACE, NAME) \
  static cest_state NAMESPACE ## __test__ ## NAME(); \
  static /* inline */ constructor void Cest_registrar_for__ ## NAMESPACE ## __test__ ## NAME() { \
    Cest.enroll(Cest.create(#NAMESPACE, #NAME, NAMESPACE ## __test__ ## NAME)); } \
  cest_state NAMESPACE ## __test__ ## NAME() //{ … }

#define ASSERT(FACT) \
  if (!(FACT)) \
    FAIL//;

#define FAIL    return failure//;
#define SUCCEED return success//;
#define PEND    return pending//;

        struct cest;
typedef struct cest* cest;
        struct cest_node;
typedef struct cest_node* cest_node;

typedef enum cest_state { failure, success, pending } cest_state;

struct cest {
  cest_state    (*function)(void);
  char          namespace[32];
  char          name[216]; /* `256 - 32 - "__test__".length == 216` */
};

/* For now, we implement a shitty global linked-list of tests to run. Not my
 * favourite implementation, but it will serve for the moment.
 */
struct cest_node {
  cest        cest;
  cest_node   next;
};

struct Cest {
  /* `Cest` functions */
  void          (*enroll)     ( cest );
  int           (*run_all)    ( void );
  cest          (*create)     ( char[], char[], cest_state (*)(void) );
  
  /* `struct cest` methods */
  cest_state    (*execute)    ( cest );
  
  /* Data elements */
  cest_node       first;
} extern Cest;



#endif
#if !defined(DECLARATIONS) && !defined(CEST_IMPLEMENTATION) /* ========================================== BODY */
# define                               CEST_IMPLEMENTATION
# define DECLARATIONS
#   include <stdlib.h>
#   include <stdio.h>
#   include <string.h>
# undef  DECLARATIONS

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM) \
  strncpy(TO, FROM, sizeof(TO)); TO[sizeof(TO) - 1] = '\0'

#define CSI "\033["
#define SGR "m"
static const struct { char red[6]; char green[6]; char yellow[6]; char reset[6]; }
ANSIEscapes = {
  .red    = CSI "31" SGR,
  .green  = CSI "32" SGR,
  .yellow = CSI "33" SGR,
  .reset  = CSI "0"  SGR
};


void          Cest__enroll    (cest);
int           Cest__run_all   (void);
cest          Cest__create    (char[], char[], cest_state (*)(void));

cest_state    cest__execute   (cest);

struct Cest Cest = {
  .enroll     = Cest__enroll,
  .run_all    = Cest__run_all,
  .create     = Cest__create,
  
  .execute    = cest__execute,
  
  .first      = NULL
};

void Cest__enroll(cest a_cest) {
  struct cest_node   *current = NULL;
  struct cest_node    this_node = { .cest = a_cest, .next = NULL };
  struct cest_node   *this = malloc(sizeof(struct cest_node));        // LEAK: Moar!
  memcpy(this, &this_node, sizeof(struct cest_node));
  
  if (Cest.first == NULL)
    Cest.first = this;
  else {
    current = Cest.first;
    while (current->next != NULL)
      current = current->next;
    
    current->next = this;
  }
}

int Cest__run_all(void) {
  cest_state return_value; int total, successes, pends;
  
  cest                current;
  struct cest_node   *current_node = Cest.first;
  
  for (total = 0, successes = 0, pends = 0; current_node != NULL; total++, current_node = current_node->next) {
    current = current_node->cest;
    return_value = Cest.execute(current);
    if (return_value) { successes++; }
    if (return_value - 1) { pends++; }
    
    printf("%s->%s%s%s()\n", current->namespace,
      return_value ? (return_value - 1 ? ANSIEscapes.yellow : ANSIEscapes.green) : ANSIEscapes.red,
      current->name, ANSIEscapes.reset);
  }
  
  printf("%s%d successes%s (of %d)\n",
    successes < total ? ANSIEscapes.red : (pends ? ANSIEscapes.yellow : ANSIEscapes.green),
    successes, ANSIEscapes.reset, total);
  
  return total - successes;
}

cest Cest__create(char namespace[], char name[], cest_state (*function)(void)) {
  /* LEAK: All up in yo’ beeswax, leakin’ like a sieve! \m/ ^.^ \m/ */
  cest this = malloc(sizeof(struct cest));
  
         this->function     = function;
  STRCPY(this->namespace    , namespace);
  STRCPY(this->name         , name);
  
  return this;
}

cest_state cest__execute(cest this) { return this->function(); }

int main() { return Cest.run_all(); }

#endif

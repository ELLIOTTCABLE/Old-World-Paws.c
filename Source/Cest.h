#define CEST_H

#define constructor __attribute__((constructor))
#define CEST(NAMESPACE, NAME) \
  static cest_state NAMESPACE ## __test__ ## NAME(); \
  static /* inline */ constructor void Cest_registerer_for__ \
          ## NAMESPACE ## __test__ ## NAME() { \
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

typedef enum cest_state {
  failure,
  success,
  pending
} cest_state;

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
  cest_state    (*run_all)    ( void );
  cest          (*create)     ( char[], char[], cest_state (*)(void) );
  
  /* `struct cest` methods */
  cest_state    (*execute)    ( cest );
  
  /* Data elements */
  cest_node   first;
} extern Cest;

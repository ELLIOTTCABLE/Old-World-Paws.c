#define CEST_H

#include <stdbool.h>

#define constructor __attribute__((constructor))
#define CEST(NAMESPACE, NAME) \
  static bool NAMESPACE ## __test__ ## NAME(); \
  static /* inline */ constructor void Cest_registerer_for__ \
          ## NAMESPACE ## __test__ ## NAME() { \
    Cest.enroll(Cest.create(#NAMESPACE, #NAME, NAMESPACE ## __test__ ## NAME)); } \
  bool NAMESPACE ## __test__ ## NAME()

#define ASSERT(FACT) \
  if (!(FACT)) \
    return false

        struct cest;
typedef struct cest* cest;

struct cest {
  bool  (*function)(void);
  char  namespace[32];
  char  name[216]; /* `256 - 32 - "__test__".length == 216` */
};

/* For now, we implement a shitty global linked-list of tests to run. Not my
 * favourite implementation, but it will serve for the moment.
 */
struct cest_node {
  cest                cest;
  struct cest_node*   next;
};

struct Cest {
  /* General functions */
  void  (*enroll)   (cest);
  bool  (*run_all)  (void);
  
  /* `struct cest` methods */
  cest  (*create)   (char[], char[], bool (*)(void));
  bool  (*execute)  (cest);
  
  /* Data storage */
  struct cest_node* first;
} extern Cest;

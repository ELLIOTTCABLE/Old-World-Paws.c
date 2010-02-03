#define CEST_H_INCLUDED

#include <stdbool.h>

#define constructor __attribute__((constructor))
#define CEST(NAMESPACE, FUNCTION) \
  static bool NAMESPACE ## __test__ ## FUNCTION(); \
  static /* inline */ constructor void Cest_registerer_for__ \
          ## NAMESPACE ## __test__ ## FUNCTION() { \
    Cest.enroll(Cest.create(#NAMESPACE, #FUNCTION, NAMESPACE ## __test__ ## FUNCTION)); } \
  bool NAMESPACE ## __test__ ## FUNCTION()

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
        struct cest_node;
typedef struct cest_node* cest_node;

struct cest_node {
  cest      cest;
  cest_node next;
};

struct Cest {
  void  (*enroll) (cest);
  
  cest  (*create) (char[], char[], bool (*)(void));
  
  cest_node first;
} extern Cest;

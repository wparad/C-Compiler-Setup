// the initial capacity (number of buckets)
#define CAPACITY 100

typedef struct Node node;
struct Node {
  char* value;
  node* next; // next node in the list
};

typedef struct Hashtable hashtable;
struct Hashtable {
  node* list[CAPACITY]; // "buckets" of linked lists
};

/* Function prototypes */
int hash(char *, unsigned long *);
int put(char *, hashtable *);
int get(char *, hashtable *);

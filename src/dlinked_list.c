#include "dlinked_list.h"
#include <stdio.h>
#include <stdlib.h>
struct node {
  dlinked_list_data_t data;
  struct node *next;
};
typedef struct node Node;

struct dlinked_list {
  Node *start;
  Node *end;
  int size;
};

dlinked_list_t *dlinked_list_create() {
  dlinked_list_t *li = (dlinked_list_t *)malloc(sizeof(dlinked_list_t));
  if (li != NULL) {
    li->start = NULL;
    li->end = NULL;
    li->size = 0;
  }
  return li;
}

void dlinked_list_free(dlinked_list_t *li) {
  if (li != NULL) {
    Node *no;
    while ((li->start) != NULL) {
      no = li->start;
      li->start = li->start->next;
      free(no);
    }
    free(li);
  }
}

int dlinked_list_size(dlinked_list_t *li) {
  if (li == NULL)
    return 0;
  return li->size;
}

dlinked_list_data_t *dlinked_list_to_vector(dlinked_list_t *li) {
  dlinked_list_data_t *v = NULL;
  if (li != NULL) {
    Node *node = li->start;
    v = malloc(dlinked_list_size(li) * sizeof(dlinked_list_data_t));
    int i = 0;
    while (node != NULL) {
      v[i] = node->data;
      node = node->next;
      i++;
    }
    free(li);
  }
  return v;
}

int dlinked_list_insert_end(dlinked_list_t *li, dlinked_list_data_t al) {
  if (li == NULL)
    return 0;
  Node *no;
  no = (Node *)malloc(sizeof(Node));
  if (no == NULL)
    return 0;
  no->data = al;
  no->next = NULL;
  if (li->start == NULL)
    li->start = no;
  else
    li->end->next = no;

  li->end = no;
  li->size++;
  return 1;
}

#ifndef DLINKED_LIST_H
#define DLINKED_LIST_H
typedef struct dlinked_list dlinked_list_t;
typedef int dlinked_list_data_t;

dlinked_list_t *dlinked_list_create();

void dlinked_list_free(dlinked_list_t *li);

int dlinked_list_size(dlinked_list_t *li);

dlinked_list_data_t *dlinked_list_to_vector(dlinked_list_t *li);

int dlinked_list_insert_end(dlinked_list_t *li, dlinked_list_data_t al);
#endif

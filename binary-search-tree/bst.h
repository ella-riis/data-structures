#ifndef __BST_H
#define __BST_H

/*
 * Structure used to represent a binary search tree.
 */
struct bst;
struct bst_node;

/*
 * Basic binary search tree interface function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
struct bst* bst_create();
void bst_free(struct bst* bst);
void bst_free_from_root(struct bst_node* root);
int bst_size(struct bst* bst);
int bst_size_from_root(struct bst_node* root);
void bst_insert(struct bst* bst, int key, void* value);
void bst_remove(struct bst* bst, int key);
void print_tree(struct bst* bst);
struct bst_node* get_node(struct bst* bst, int key);
void* bst_get(struct bst* bst, int key);

/*
 * Binary search tree "puzzle" function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
int bst_height(struct bst* bst);
int bst_height_from_root(struct bst_node* root);
int bst_path_sum(struct bst* bst, int sum);
int path_sum_from_root(struct bst_node* root, int sum);
int bst_range_sum(struct bst* bst, int lower, int upper);
int range_sum_from_root(struct bst_node* root, int lower, int upper);

#endif

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "stack.h"

struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};

struct bst {
  struct bst_node* root;
};

//Allocate space for a new binary search tree
struct bst* bst_create() {
  struct bst* bst = malloc(sizeof(struct bst));
  return bst;
}

//Frees the memory allocated by a BST
 void bst_free(struct bst* bst) {
  bst_free_from_root(bst -> root);
  free(bst);
}

void bst_free_from_root(struct bst_node* root) {
  if (root == NULL) return;

  bst_free_from_root(root -> left);
  bst_free_from_root(root -> right);

  free(root);
}

// Returns the total number of elements stored in a given BST.
int bst_size(struct bst* bst) {
  return bst_size_from_root(bst -> root);
}

int bst_size_from_root(struct bst_node* root) {
  if (root == NULL) return 0;
  else return 1 + bst_size_from_root(root -> left) + bst_size_from_root(root -> right);
}

// Inserts a new key/value pair into the BST.

void bst_insert(struct bst* bst, int key, void* value) {
  struct bst_node* parent = NULL;
  struct bst_node* cur = bst -> root;
  struct bst_node* to_add = malloc(sizeof(struct bst_node));
  to_add -> key = key;
  to_add -> value = value;
  to_add -> right = NULL;
  to_add -> left = NULL;

  if (cur == NULL)
    bst -> root = to_add;

  else {

    while (cur != NULL) {
      parent = cur;

      if (key < cur -> key)
        cur = cur -> left;

      else cur = cur -> right;
    }

    if (key < parent -> key)
      parent -> left = to_add;
    else parent -> right = to_add;

  }

}


//Removes a key/value pair with a specified key from a given BST.

void bst_remove(struct bst* bst, int key) {
  struct bst_node* to_remove = bst -> root;
  struct bst_node* parent = bst -> root;
  struct bst_node* successor = NULL;
  struct bst_node* successor_parent = NULL;

  while (to_remove != NULL && to_remove -> key != key) {
    parent = to_remove;

    if (key < to_remove -> key)
      to_remove = to_remove -> left;
    else to_remove = to_remove -> right;
  }

  //Case of no children or one child
  if (to_remove -> left == NULL || to_remove -> right == NULL) {

    if (to_remove -> left != NULL) { //One child to the left
      if (key < parent -> key)
        parent -> left = to_remove -> left;
      else parent -> right = to_remove -> left;
    }

    else if (to_remove -> right != NULL) { //One child to the right
      if (key < parent -> key)
        parent -> left = to_remove -> right;
      else parent -> right = to_remove -> right;
    }
    else {  //No children
      if (key < parent -> key)
        parent -> left = NULL;
      else parent -> right = NULL;
    }
  }

  else if (to_remove -> left != NULL && to_remove -> right != NULL) { //Case of two children
    //Find successor and successor parent
    successor = to_remove -> right;
    successor_parent = to_remove;
    while (successor -> left != NULL) {
      successor_parent = successor;
      successor = successor -> left;
    }
    //Adjust nodes
    successor -> left = to_remove -> left;
    successor_parent -> left = successor -> right;
    if (successor != to_remove -> right)
      successor -> right = to_remove -> right;
    else successor -> right = NULL;

    if (to_remove == bst -> root)
      bst -> root = successor;
    else {
      if (successor -> key < parent -> key)
        parent -> left = successor;
      else if (successor -> key >= parent -> key)
        parent -> right = successor;
    }
  }
  free(to_remove);
}

struct bst_node* get_node(struct bst* bst, int key) {
  struct bst_node* temp = bst -> root;
  while (temp != NULL && temp -> key != key) {
    if (key < temp -> key)
      temp = temp -> left;
    else temp = temp -> right;
  }
  if (temp != NULL)
    return temp;
  return NULL;
}

// Returns the value associated with a specified key in a given BST.

void* bst_get(struct bst* bst, int key) {
  struct bst_node* temp = bst -> root;
  while (temp != NULL && temp -> key != key) {
    if (key < temp -> key)
      temp = temp -> left;
    else temp = temp -> right;
  }
  if (temp != NULL)
    return temp -> value;
  return NULL;
}

//Returns the height of a given BST

 int bst_height(struct bst* bst) {
   return bst_height_from_root(bst -> root);
 }
 int bst_height_from_root(struct bst_node* root) {
   if (root == NULL)
    return -1;
   else {
     int left_height = bst_height_from_root(root -> left);
     int right_height = bst_height_from_root(root -> right);

     if (left_height > right_height)
      return left_height + 1;
     else return right_height + 1;
   }
 }

// Determines whether a specified value is a valid path
// sum within a given BST.
//Shoutout to geeksforgeeks for help with this one:
//https://www.geeksforgeeks.org/root-to-leaf-path-sum-equal-to-a-given-number/

int bst_path_sum(struct bst* bst, int sum) {
  int sum_counter = 0;
  struct bst_node* temp = bst -> root;
  return path_sum_from_root(bst -> root, sum);
}

int path_sum_from_root(struct bst_node* root, int sum) {
  int sum_found = 0;
  int sub_sum = sum - root -> key;

  if (sub_sum == 0 && root -> left == NULL && root -> right == NULL)
    return 1;

  if (root -> left != NULL)
    sum_found = sum_found || path_sum_from_root(root -> left, sub_sum);
  if (root -> right != NULL)
    sum_found = sum_found || path_sum_from_root(root -> right, sub_sum);

  return sum_found;
}

//Computes the sum of all keys in the BST between a given lower bound
// and a given upper bound.

int bst_range_sum(struct bst* bst, int lower, int upper) {
  return range_sum_from_root(bst -> root, lower, upper);
}

int range_sum_from_root(struct bst_node* root, int lower, int upper) {
  if (root == NULL)
    return 0;
  if (root -> key <= upper && root -> key >= lower)
    return root -> key + range_sum_from_root(root -> left, lower, upper)
      + range_sum_from_root(root -> right, lower, upper);
  else if (root -> key < lower)
    return range_sum_from_root(root -> right, lower, upper);
  else return range_sum_from_root(root -> left, lower, upper);
}

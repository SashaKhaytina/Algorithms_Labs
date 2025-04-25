#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


const int MAX_REQUESTS_NUM = 100000;
const int MAX_STR_SIZE     = 600;



typedef struct Node Node;
struct Node
{
    Node* prev;
    Node* left;
    Node* right;

    char* first_value;
    char* second_value;
};

typedef struct{
    Node* min_tree;
    Node* max_tree;
}PairTrees;



void left_turn(Node* head);
void right_turn(Node *head);

void zig    (Node* needed_node);
void zig_zig(Node* needed_node);
void zig_zag(Node* needed_node);

Node* splay(Node* needed_node);

Node*     splay_tree_find  (Node* current_node, char *elem);
PairTrees splay_tree_split (Node* tree, char* elem);
Node*     splay_tree_insert(Node *tree, Node* new_elem);
Node*     splay_tree_merge (Node* min_tree, Node* max_tree);
Node*     splay_tree_remove(Node *head, char *elem);

int compare_elements(Node* node, char* str);


int main()
{
  Node* splay_tree_first = NULL;
  Node* splay_tree_second = NULL;

  int n = 0;
  int m = 0;
  scanf("%d", &n);
  if (n > MAX_REQUESTS_NUM) return 1;

  Node* arr_first_second = (Node*) calloc(n, sizeof(Node));
  Node* arr_second_first = (Node*) calloc(n, sizeof(Node));

  if (arr_first_second == NULL || arr_second_first == NULL) return 0;




  for(int i = 0; i < n; i++) 
  {
    char* first_strs  = (char*) calloc(1, sizeof(char) * MAX_STR_SIZE);
    char* second_strs = (char*) calloc(1, sizeof(char) * MAX_STR_SIZE);

    if (first_strs == NULL || second_strs == NULL) return 0;

    scanf("%s %s", first_strs, second_strs);

    arr_first_second[i].prev  = NULL; 
    arr_first_second[i].left  = NULL; 
    arr_first_second[i].right = NULL;
    arr_first_second[i].first_value  = first_strs;
    arr_first_second[i].second_value = second_strs;

    arr_second_first[i].prev  = NULL; 
    arr_second_first[i].left  = NULL; 
    arr_second_first[i].right = NULL;
    arr_second_first[i].first_value  = second_strs;
    arr_second_first[i].second_value = first_strs;

    splay_tree_second = splay_tree_insert(splay_tree_second, &arr_second_first[i]);
    splay_tree_first = splay_tree_insert(splay_tree_first, &arr_first_second[i]);
  }


  scanf("%d", &m);

  for(int i = 0; i < m; i++) 
  {
    char request[MAX_STR_SIZE] = {};
    scanf("%s", request);

    splay_tree_first =  splay_tree_find(splay_tree_first, request);
    if (splay_tree_first && compare_elements(splay_tree_first, request) == 0) printf("%s\n", splay_tree_first->second_value);
    else
    {
      splay_tree_second =  splay_tree_find(splay_tree_second, request);
      if (splay_tree_second && compare_elements(splay_tree_second, request) == 0) printf("%s\n", splay_tree_second->second_value);
      else printf("No same name in definition\n");
    }

  }

  for (int i = 0; i < n; i++)
  {
    free(arr_first_second[i].first_value);
    free(arr_first_second[i].second_value);
  }
  free(arr_first_second);
  free(arr_second_first);


}





void left_turn(Node* head)
{
  // change child of subtree`s parent
  if (head->prev != NULL)
  {
    if (head->prev->left == head) head->prev->left  = head->right;
    else                          head->prev->right = head->right;
  }

  Node* middle_child = NULL;
  if (head->right != NULL) 
  {
    middle_child = head->right->left;

    head->right->prev = head->prev;
    head->right->left = head;
    head->prev = head->right;
  }


  if (middle_child != NULL)   middle_child->prev = head;
  head->right = middle_child;

}

void right_turn(Node *head)
{
  // change child of subtree`s parent
  if (head->prev != NULL)
  {
    if (head->prev->left == head) head->prev->left  = head->left;
    else                          head->prev->right = head->left;  
  }

  Node* middle_child = NULL;
  if (head->left != NULL ) 
  {
    middle_child = head->left->right;

    head->left->prev = head->prev;
    head->left->right  = head;
    head->prev = head->left;
  }


  if (middle_child != NULL)   middle_child->prev = head;
  head->left = middle_child;
}


Node* splay(Node* node) 
{
    while (node != NULL && node->prev != NULL) 
    {
        Node* parent = node->prev;
        Node* grandparent = parent->prev;
        
        if (grandparent == NULL) 
        {
          // Zig
          if (parent->left == node) right_turn(parent);
          else left_turn(parent);
        } 
        else 
        {
          if (grandparent->left == parent && parent->left == node) 
          {
            // Zig-zig
            right_turn(grandparent);
            right_turn(parent);
          } 
          else if (grandparent->right == parent && parent->right == node) 
          {
            // Zig-zig
            left_turn(grandparent);
            left_turn(parent);
          }
          else 
          {
            // Zig-zag
            if (parent->left == node) 
            {
              right_turn(parent);
              left_turn(grandparent);
            } 
            else 
            {
              left_turn(parent);
              right_turn(grandparent);
            }
          }
        }
    }
    return node;
}


// void zig(Node* needed_node)
// {
//   if (needed_node->prev->left == needed_node) right_turn(needed_node->prev);
//   else left_turn(needed_node->prev);
// }



// void zig_zig(Node* needed_node)
// {
//   if (needed_node->prev->prev->left == needed_node->prev && needed_node->prev->left == needed_node) 
//   {
//     right_turn(needed_node->prev->prev);
//     right_turn(needed_node->prev);
//   } 
//   else if (needed_node->prev->prev->right == needed_node->prev && needed_node->prev->right == needed_node) 
//   {
//     left_turn(needed_node->prev->prev);
//     left_turn(needed_node->prev);
//   }
// }



// void zig_zag(Node* needed_node)
// {
//   if (needed_node->prev->left == needed_node) 
//   {
//       right_turn(needed_node->prev);
//       left_turn(needed_node->prev->prev);
//   } else 
//   {
//       left_turn(needed_node->prev);
//       right_turn(needed_node->prev->prev);
//   }
// }



Node* splay_tree_find(Node* current_node, char *elem) {
    Node* last_valid = NULL;
    while (current_node != NULL) {
        last_valid = current_node;
        int cmp = strcmp(current_node->first_value, elem);
        if (cmp == 0) break;
        current_node = (cmp < 0) ? current_node->right : current_node->left;
    }
    if (last_valid) splay(last_valid);
    return last_valid;
}


PairTrees splay_tree_split(Node* tree, char* elem) 
{
    PairTrees pair = {NULL, NULL};
    if (tree == NULL) return pair;

    tree = splay_tree_find(tree, elem);
    int cmp = compare_elements(tree, elem);

    if (cmp > 0) 
    { 
      pair.min_tree = tree->left;

      if (tree->left != NULL) tree->left->prev = NULL;
      
      tree->left = NULL;
      
      pair.max_tree = tree;
    }
    else if (cmp < 0) 
    {
      pair.max_tree = tree->right;
      
      if (tree->right != NULL) tree->right->prev = NULL;
      
      tree->right = NULL;
      
      pair.min_tree = tree;
    }
    else 
    {
      pair.min_tree = tree;
      pair.max_tree = tree->right;

      if (tree->right != NULL) tree->right->prev = NULL;
      tree->right = NULL;
    }

    return pair;
}


Node* splay_tree_insert(Node* tree, Node* new_elem)
{
  PairTrees pair = splay_tree_split(tree, new_elem->first_value);

  new_elem->left = pair.min_tree;
  new_elem->right = pair.max_tree;

  if (pair.min_tree != NULL) pair.min_tree->prev = new_elem;
  if (pair.max_tree != NULL) pair.max_tree->prev = new_elem;

  return new_elem;
}



int compare_elements(Node* node, char* str)
{
  if (node == NULL) return -1;
  if (node != NULL) return strcmp(node->first_value, str);
}


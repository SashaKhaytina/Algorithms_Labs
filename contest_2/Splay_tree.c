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



// int main()
// {
//   char str_f[100000][600] = {};
//   char str_s[100000][600] = {};
//   char quest[100000][600] = {};
//   int AmountCom = 0, val = 0, may = 0;
//   scanf("%d", &AmountCom);


//   Node *arr_f = (Node *)calloc(AmountCom, sizeof(Node));
//   Node *arr_s = (Node *)calloc(AmountCom, sizeof(Node));
//   Node *head_f = NULL;

//   for(int i = 0; i < AmountCom; i++) {
//     scanf("%s %s", str_f[i], str_s[i]);

//     arr_f[i].first_value = str_f[i];
//     arr_f[i].second_value = str_s[i];
//     arr_s[i].first_value = str_s[i];
//     arr_s[i].second_value = str_f[i];

//     head_f = splay_tree_insert(head_f, arr_s + i);
//     head_f = splay_tree_insert(head_f, arr_f + i);
//     // assert(head_f == arr_f + i);
//   }

//   scanf("%d", &AmountCom);

//   for(int i = 0; i < AmountCom; i++) {
//     scanf("%s", quest[i]);

//     head_f =  splay_tree_find(head_f, quest[i]);

//     if(compare_elements(head_f, quest[i]) == 0) printf("%s\n", head_f->second_value);

//   }

// }

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

  if (arr_first_second == NULL || arr_second_first == NULL)
  {
    printf("AAAAAAAAAAAA\n");
    return 0;
  }


  // char first_strings[MAX_REQUESTS_NUM][MAX_STR_SIZE]  = {};
  // char second_strings[MAX_REQUESTS_NUM][MAX_STR_SIZE] = {};


  for(int i = 0; i < n; i++) 
  {
    char* first_strs  = (char*) calloc(1, sizeof(char) * MAX_STR_SIZE);
    char* second_strs = (char*) calloc(1, sizeof(char) * MAX_STR_SIZE);

    if (first_strs == NULL || second_strs == NULL)
    {
      printf("AAAAAAAAAAAA\n");
      return 0;
    }

    // char* first_strs;
    // char* second_strs;

    // char* first_strs;
    // char* second_strs;

    // char* first_strs  = first_strings[i];
    // char* second_strs = second_strings[i];

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
    // char* request;
    scanf("%s", request);

    splay_tree_first =  splay_tree_find(splay_tree_first, request);
    // if (splay_tree_first == NULL) printf("NULL tree f\n");
    /*else*/ if (splay_tree_first && compare_elements(splay_tree_first, request) == 0) printf("%s\n", splay_tree_first->second_value);
    else
    {
      splay_tree_second =  splay_tree_find(splay_tree_second, request);
      // if (splay_tree_second == NULL) printf("NULL tree s\n");
      /*else*/ if (splay_tree_second && compare_elements(splay_tree_second, request) == 0) printf("%s\n", splay_tree_second->second_value);
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



// Node* splay(Node* needed_node)
// {
//   while (needed_node->prev != NULL)
//   {
//     if (needed_node->prev->prev == NULL) 
//       zig(needed_node);

//     else if ((needed_node->prev->prev->left  == needed_node->prev && needed_node->prev->left  == needed_node) ||
//              (needed_node->prev->prev->right == needed_node->prev && needed_node->prev->right == needed_node))
//       zig_zig(needed_node);
//     else if ((needed_node->prev->prev->left  == needed_node->prev && needed_node->prev->right == needed_node) ||
//              (needed_node->prev->prev->right == needed_node->prev && needed_node->prev->left  == needed_node))
//       zig_zag(needed_node);
//   }

//   return needed_node;
// }

Node* splay(Node* node) {
    while (node != NULL && node->prev != NULL) {
        Node* parent = node->prev;
        Node* grandparent = parent->prev;
        
        if (grandparent == NULL) {
            // Zig
            if (parent->left == node) right_turn(parent);
            else left_turn(parent);
        } else {
            if (grandparent->left == parent && parent->left == node) {
                // Zig-zig
                right_turn(grandparent);
                right_turn(parent);
            } else if (grandparent->right == parent && parent->right == node) {
                // Zig-zig
                left_turn(grandparent);
                left_turn(parent);
            } else {
                // Zig-zag
                if (parent->left == node) {
                    right_turn(parent);
                    left_turn(grandparent);
                } else {
                    left_turn(parent);
                    right_turn(grandparent);
                }
            }
        }
    }
    return node;
}


void zig(Node* needed_node)
{
  if (needed_node == NULL) return;
  if (needed_node->prev == NULL) return;

  if (needed_node->prev->left == needed_node)
  {
    right_turn(needed_node->prev);
  }
  else if (needed_node->prev->right == needed_node)
  {
    left_turn(needed_node->prev);
  }
  else
  {
    printf("ERROR ZIG\n");
  }
}



void zig_zig(Node* needed_node)
{
  if (needed_node == NULL) return;
  if (needed_node->prev == NULL) return;
  if (needed_node->prev->prev == NULL) return ;
  
  if (needed_node->prev->prev->left == needed_node->prev && needed_node->prev->left == needed_node)
  {
    right_turn(needed_node->prev->prev);
    right_turn(needed_node->prev);
  } 
  else if ((needed_node->prev->prev->right == needed_node->prev) && (needed_node->prev->right == needed_node))
  {
    left_turn(needed_node->prev->prev);
    left_turn(needed_node->prev);
  }
  else
  {
    printf("ERROR ZIG-ZIG\n");
  }
}



void zig_zag(Node* needed_node)
{
  if (needed_node == NULL) return;
  if (needed_node->prev == NULL) return;
  if (needed_node->prev->prev == NULL) return ;

  if (needed_node->prev->prev->left == needed_node->prev && needed_node->prev->right == needed_node)
  {
    left_turn(needed_node->prev);
    right_turn(needed_node->prev->prev);
  }
  else if (needed_node->prev->prev->right == needed_node->prev && needed_node->prev->left == needed_node)
  {
    right_turn(needed_node->prev);
    left_turn(needed_node->prev->prev);
  }
  else
  {
    printf("ERROR ZIG-ZAG\n");
  }
}



// Node* splay_tree_find(Node* current_node, char *elem)
// {
//   if (current_node == NULL) return current_node;


//   while (compare_elements(current_node, elem) != 0)
//   {
//     if ((compare_elements(current_node, elem) < 0) && (current_node->right != NULL))  current_node = current_node->right; //return splay_tree_find(current_node->right, elem);
//     else if ((compare_elements(current_node, elem) > 0) && (current_node->left  != NULL))  current_node = current_node->left; // return splay_tree_find(current_node->left,  elem);

//     else 
//     {
//       splay(current_node); // no elem in tree
//       return current_node;
//     }
//   }

//   splay(current_node);
//   return current_node;

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



// PairTrees splay_tree_split(Node* tree, char* elem)
// {
//   PairTrees pair = {};
//   if (tree == NULL)  return pair;

//   tree = splay_tree_find(tree, elem);

//   if (compare_elements(tree, elem) < 0)
//   {
//     if (tree->right != NULL) tree->right->prev = NULL;

//     pair.max_tree = tree->right;
//     pair.min_tree = tree;

//     tree->right = NULL;

//     return pair;
//   }
//   else if (compare_elements(tree, elem) > 0)
//   {
//     if (tree->left != NULL) tree->left->prev = NULL;

//     pair.min_tree = tree->left;
//     pair.max_tree = tree;

//     tree->left = NULL;

//     return pair;
//   }

//   pair.min_tree = tree;
//   pair.max_tree = NULL;
//   return pair;
// }
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

// Node* splay_tree_merge(Node* min_tree, Node* max_tree)
// {
//   if (min_tree == NULL) return max_tree;
//   if (max_tree == NULL) return min_tree;


//   // спускаемся вправо до упора
//   Node* max_in_max_tree = max_tree;
//   while (max_in_max_tree->right != NULL)
//   {
//     max_in_max_tree = max_in_max_tree->right;
//   }

//   max_tree = splay(max_in_max_tree);

//   if (max_tree->left != NULL)
//   {
//     printf("ERROR MERGE\n");
//     return min_tree; //? это норм?
//   }

//   max_tree->left = min_tree;
//   min_tree->prev = max_tree;

//   return max_tree;
// }



// Node* splay_tree_remove(Node* tree, char* elem)
// {
//   tree = splay_tree_find(tree, elem);
//   if (compare_elements(tree, elem) != 0)  return tree; // no elem in tree

//   if (tree->left != NULL)  tree->left->prev  = NULL;
//   if (tree->right != NULL) tree->right->prev = NULL; 

//   // free(head->first_value);
//   // free(head->second_value);
//   return splay_tree_merge(tree->left, tree->right);
// }




int compare_elements(Node* node, char* str)
{
  if (node == NULL) return -1;
  if (node != NULL) return strcmp(node->first_value, str);
}


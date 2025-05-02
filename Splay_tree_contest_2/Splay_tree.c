#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


const int MAX_REQUESTS_NUM = 100000;
const int MAX_STR_SIZE     = 600;



typedef struct Node Node;
/*!
 * Struct for node splay tree.
 */
struct Node
{
    Node* prev;              /*!< pointer to parent node */
    Node* left;              /*!< pointer to left child */
    Node* right;             /*!< pointer to right child */

    char* first_value;       /*!< first value node */
    char* second_value;      /*!< second value node */
};


/*!
 * Struct for pair splay trees.
 */
typedef struct
{
    Node* min_tree;          /*!< root tree with smaller nodes */
    Node* max_tree;          /*!< root tree with bigger nodes */
} PairTrees;


/*! \brief A function do left turn.
 *
 * \param[in] head node that the turn is relative to.
*/
void left_turn(Node* head);


/*! \brief A function do right turn.
 *
 * \param[in] head node that the turn is relative to.
*/
void right_turn(Node* head);


/*! \brief A function that lifts the requested node.
 *
 * \param[in] needed_node requested node.
 *
 * \return new tree root (return splay tree).
 * 
 * \see left_turn(Node* head)
 * \see right_turn(Node* head)
*/
Node* splay(Node* needed_node);


/*! \brief A function that find the requested element in splay tree and lifts this element.
 *
 * \param[in] current_node root subtree, where finding element.
 * \param[in] elem requested element.
 *
 * \return new tree root (return splay tree).
 * 
 * \see splay(Node* needed_node)
*/
Node*     splay_tree_find  (Node* current_node, char* elem);


/*! \brief A function that split splay tree by value (elem) into two trees.
 *
 * \param[in] tree root tree.
 * \param[in] elem value (elem) by which split takes place.
 *
 * \return value type PairTrees, struct wich have two trees.
 * 
 * \see splay_tree_find(Node* current_node, char* elem)
 * \see compare_elements(Node* node, char* str)
*/
PairTrees splay_tree_split (Node* tree, char* elem);


/*! \brief A function that insert element in splay tree.
 *
 * \param[in] tree root tree.
 * \param[in] new_elem value (elem) which will insert.
 *
 * \return new tree root (return splay tree).
 * 
 * \see splay_tree_split(Node* tree, char* elem)
*/
Node*     splay_tree_insert(Node* tree, Node* new_elem);


/*! \brief A function that compare node first_value and another value.
 *
 * \param[in] node node, which first_value compared.
 * \param[in] str value compared.
 *
 * \return int number. If (node first_value) < (value) return (< 0); If (node first_value) == (value) return (0); If (node first_value) > (value) return (> 0).
*/
int compare_elements(Node* node, char* str);


/*! \brief A function get data and build splay tree.
 *
 * \param[in] n number of pairs.
 * \param[in] arr_first_second array of node with correct order of values.
 * \param[in] arr_second_first array of node with incorrect order of values.
 * \param[in] splay_tree_first splay tree with node with incorrect order of values.
 * \param[in] splay_tree_second splay tree with node with incorrect order of values.
 *
 * \return error - (1) or OK - (0).
 * 
 * \see splay_tree_insert(Node* tree, Node* new_elem)
*/
int  get_data          (int n, Node* arr_first_second, Node* arr_second_first, Node** splay_tree_first, Node** splay_tree_second);


/*! \brief A function that processing all requests.
 *
 * \param[in] splay_tree_first splay tree with node with incorrect order of values.
 * \param[in] splay_tree_second splay tree with node with incorrect order of values.
 * 
 * \see splay_tree_find(Node* current_node, char* elem)
 * \see compare_elements(Node* node, char* str)
*/
void request_processing(Node* splay_tree_first, Node* splay_tree_second);


/*! \brief A function that free all memory.
 *
 * \param[in] n number of pairs.
 * \param[in] arr_first_second array of node with correct order of values.
 * \param[in] arr_second_first array of node with incorrect order of values.
*/
void free_memory       (int n, Node* arr_first_second, Node* arr_second_first);



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

  if (arr_first_second == NULL || arr_second_first == NULL) return 1;


  if (get_data(n, arr_first_second, arr_second_first, &splay_tree_first, &splay_tree_second) == 1) return 1;


  request_processing(splay_tree_first, splay_tree_second);


  free_memory(n, arr_first_second, arr_second_first);

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
  if (head->left != NULL) 
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


Node* splay_tree_find(Node* current_node, char *elem) 
{
    Node* last_valid = NULL;

    while (current_node != NULL) 
    {
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



int get_data(int n, Node* arr_first_second, Node* arr_second_first, Node** splay_tree_first, Node** splay_tree_second)
{

  for(int i = 0; i < n; i++) 
  {
    char* first_strs  = (char*) calloc(1, sizeof(char) * MAX_STR_SIZE);
    char* second_strs = (char*) calloc(1, sizeof(char) * MAX_STR_SIZE);

    if (first_strs == NULL || second_strs == NULL) return 1;

    scanf("%599s %599s", first_strs, second_strs);

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

    *splay_tree_second = splay_tree_insert(*splay_tree_second, &arr_second_first[i]);
    *splay_tree_first = splay_tree_insert(*splay_tree_first, &arr_first_second[i]);
  }

  return 0;
}


void request_processing(Node* splay_tree_first, Node* splay_tree_second)
{
  int m = 0;
  scanf("%d", &m);

  for(int i = 0; i < m; i++) 
  {
    char request[MAX_STR_SIZE] = {};
    scanf("%599s", request);

    splay_tree_first =  splay_tree_find(splay_tree_first, request);
    if (splay_tree_first && compare_elements(splay_tree_first, request) == 0) printf("%s\n", splay_tree_first->second_value);
    else
    {
      splay_tree_second =  splay_tree_find(splay_tree_second, request);
      if (splay_tree_second && compare_elements(splay_tree_second, request) == 0) printf("%s\n", splay_tree_second->second_value);
      else printf("No same name in definition\n");
    }
  }
}


void free_memory(int n, Node* arr_first_second, Node* arr_second_first)
{
  for (int i = 0; i < n; i++)
  {
    free(arr_first_second[i].first_value);
    free(arr_first_second[i].second_value);
  }
  free(arr_first_second);
  free(arr_second_first);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <malloc.h>


const int MAX_RAND_PRIORITY = 1000000;

typedef int Elem_t;


typedef struct Node Node;
struct Node
{
    Node* left;
    Node* right;

    Elem_t value;
    int priority;
    int size_subtree;
};


typedef struct Decart_Tree Decart_Tree;
struct Decart_Tree
{
    Node* root;
};


void change_size(Node* node)
{
    if (node == NULL) return ;


    node->size_subtree = 1;

    if (node->left  != NULL) node->size_subtree += node->left->size_subtree;
    if (node->right != NULL) node->size_subtree += node->right->size_subtree;
}


// bool  decart_tree_find  (Node* current_node, Elem_t value);
Node* decart_tree_find    (Node* current_node, Elem_t value);
void  decart_tree_insert  (Decart_Tree* tree, Elem_t value);
void  decart_tree_delete  (Decart_Tree* tree, Elem_t value);
void  decart_tree_split   (Node* current_root, Node** left_tree_return, Node** right_tree_return, Elem_t value);
Node* decart_tree_merge   (Node* left_subtree, Node* right_subtree);

Node* create_new_node     (Elem_t value);

Node* k_ordinal_statistics(Node* current_node, int k);
Node* find_minimum_bigger (Decart_Tree* tree, Elem_t value); 
Node* find_maximum_smaller(Decart_Tree* tree, Elem_t value);

void free_decart_tree     (Node* current_node);



int main()
{
    char operation[20] = {};
    Elem_t element = 0;

    Decart_Tree tree = {.root = NULL};

    while (scanf("%s", operation) != EOF)
    {
        scanf("%d", &element);

        if (strcmp(operation, "insert") == 0)
        {
            decart_tree_insert(&tree, element);
        }
        else if (strcmp(operation, "delete") == 0)
        {
            decart_tree_delete(&tree, element);
        }
        else if (strcmp(operation, "exists") == 0)
        {
            bool ans = decart_tree_find(tree.root, element);
            if (ans == true) printf("true\n");
            else             printf("false\n");
        }
        else if (strcmp(operation, "next") == 0)
        {
            Node* answer = find_minimum_bigger(&tree, element);
            if (answer == NULL) printf("none\n");
            else printf("%d\n", answer->value);
        }
        else if (strcmp(operation, "prev") == 0)
        {
            Node* answer = find_maximum_smaller(&tree, element);
            if (answer == NULL) printf("none\n");
            else printf("%d\n", answer->value);
        }
        else if (strcmp(operation, "kth") == 0)
        {
            Node* answer = k_ordinal_statistics(tree.root, element);
            if (answer == NULL) printf("none\n");
            else printf("%d\n", answer->value);
        }
        else
        {
            printf("ERROR command\n");
            return 0;
        }
    }

    free_decart_tree(tree.root);
}

// bool decart_tree_find(Node* current_node, Elem_t value)
Node* decart_tree_find(Node* current_node, Elem_t value)

{
    if (current_node == NULL) return NULL; // return false;
    if (current_node->value == value) return current_node; // return true;

    if (value < current_node->value) return decart_tree_find(current_node->left, value);

    return decart_tree_find(current_node->right, value);
}


void decart_tree_insert(Decart_Tree* tree, Elem_t value)
{
    if (tree == NULL) return ;


    if (decart_tree_find(tree->root, value) != NULL) return ;

    Node* left_tree_return = NULL;
    Node* right_tree_return = NULL;

    decart_tree_split(tree->root, &left_tree_return, &right_tree_return, value);

    tree->root = decart_tree_merge(decart_tree_merge(left_tree_return, create_new_node(value)), right_tree_return);
}



void decart_tree_split(Node* current_root, Node** left_tree_return, Node** right_tree_return, Elem_t value)
{
    if (left_tree_return == NULL || right_tree_return == NULL)
    {
        printf("ERROR args in split\n");
        return ;
    } 


    if (current_root == NULL)
    {
        *left_tree_return = NULL;
        *right_tree_return = NULL;
        return;
    }

    if (current_root->value <= value)
    {
        decart_tree_split(current_root->right, &(current_root->right), right_tree_return, value);
        *left_tree_return = current_root;
    }
    else
    {
        decart_tree_split(current_root->left, left_tree_return, &(current_root->left), value);
        *right_tree_return = current_root;
    }

    change_size(current_root);
}




Node* decart_tree_merge(Node* left_subtree, Node* right_subtree)
{
    if (right_subtree == NULL) return left_subtree;
    if (left_subtree  == NULL) return right_subtree;


    if (left_subtree->priority <= right_subtree->priority)
    {
        right_subtree->left = decart_tree_merge(left_subtree, right_subtree->left);
        change_size(right_subtree);
        return right_subtree;
    }
    else // left_subtree->priority > right_subtree->priority
    {
        left_subtree->right = decart_tree_merge(left_subtree->right, right_subtree);
        change_size(left_subtree);
        return left_subtree;
    }
}



Node* create_new_node(Elem_t value)
{
    Node* new_node = (Node*) calloc(1, sizeof(Node));

    new_node->left     = NULL;
    new_node->right    = NULL;
    new_node->value    = value;
    new_node->priority = rand() % MAX_RAND_PRIORITY;
    new_node->size_subtree     = 1;

    return new_node;
}




// void decart_tree_delete(Decart_Tree* tree, Elem_t value)
// {
//     if (tree == NULL) return ;

//     Node* deleted_node = decart_tree_find(tree->root, value);
//     if (deleted_node == NULL) return;

//     Node* new_subtree = decart_tree_merge(deleted_node->left, deleted_node->right);

//     if (new_subtree == NULL)
//     {
//         free(deleted_node);
//         return ;
//     }

//     deleted_node->left     = new_subtree->left;
//     deleted_node->right    = new_subtree->right;
//     deleted_node->value    = new_subtree->value;
//     deleted_node->priority = new_subtree->priority;
//     deleted_node->size_subtree     = new_subtree->size_subtree;

//     free(new_subtree);
// }


void decart_tree_delete(Decart_Tree* tree, Elem_t value) 
{
    if (tree == NULL) return;
    
    Node* parent = NULL;
    Node* current = tree->root;
    

    while (current != NULL && current->value != value) 
    {
        parent = current;
        if (current->value > value) current = current->left;
        else                        current = current->right;
    }
    
    if (current == NULL) return; 
    
    Node* new_subtree = decart_tree_merge(current->left, current->right);
    
    if (parent == NULL) tree->root = new_subtree;
    else if (parent->left == current) parent->left = new_subtree;
    else parent->right = new_subtree;
    
    free(current);
}


Node* find_maximum_smaller(Decart_Tree* tree, Elem_t value) 
{
    if (tree == NULL || tree->root == NULL) return NULL;

    Node* current_node = tree->root;
    Node* candidate = NULL;

    while (current_node != NULL) 
    {
        if (current_node->value < value) 
        {
            candidate = current_node; 
            current_node = current_node->right;
        } 
        else 
        {
            current_node = current_node->left;
        }
    }

    return candidate;
}


Node* find_minimum_bigger(Decart_Tree* tree, Elem_t value) 
{
    if (tree == NULL || tree->root == NULL) return NULL;

    Node* current_node = tree->root;
    Node* candidate = NULL;

    while (current_node != NULL) 
    {
        if (current_node->value > value) 
        {
            candidate = current_node; 
            current_node = current_node->left;
        } 
        else 
        {
            current_node = current_node->right;
        }
    }

    return candidate;
}


Node* k_ordinal_statistics(Node* current_node, int k)
{
    if (current_node == NULL || k < 0 || k >= current_node->size_subtree) return NULL;

    int left_subtree_size = 0;
    if (current_node->left != NULL) left_subtree_size = current_node->left->size_subtree;

    if (k < left_subtree_size) return k_ordinal_statistics(current_node->left, k);
    if (k > left_subtree_size) return k_ordinal_statistics(current_node->right, k - left_subtree_size - 1);
    return current_node;
}




void free_decart_tree(Node* current_node)
{
    if (current_node == NULL) return;

    free(current_node->left);
    free(current_node->right);
    free(current_node);
}


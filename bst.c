#include <stdio.h>
#include <stdlib.h>

typedef struct _bst {
    int         val;
    struct _bst *left;
    struct _bst *right;
} bst_t;


bst_t *newNode(int val)
{
    bst_t *new = malloc(sizeof(bst_t));
    if(new == NULL)
        goto fail;

    new->left = new->right = NULL;
    new->val = val;

fail:
    return new;
}

/* 
 * As root is getting modified in the
 * function, double pointer is needed.
 */
void insert (bst_t **root, int val)
{
    bst_t *temp = *root;
    bst_t *new = newNode(val);
    if (!new) {
        printf("Unable to insert\n");
        return;
    }

    if (*root == NULL) {
        *root = new;
    } else {
        
        bst_t *parent;
        while (temp) {
            parent = temp;
            if (temp->val > val) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        if (parent->val > val) {
            parent->left = new;
        } else {
            parent->right = new;
        }
    }
}

void preOrderTraversal(bst_t *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->val);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void inOrderTraversal(bst_t *root)
{
    if (root == NULL)
        return;

    inOrderTraversal(root->left);
    printf("%d ", root->val);
    inOrderTraversal(root->right);
}

void postOrderTraversal(bst_t *root)
{
    if (root == NULL)
        return;

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->val);
}

/* 
 * https://www.geeksforgeeks.org/level-order-tree-traversal/
 *
 * BFS traversal
 * Breadth-first search_traversal
 *
 * Treating this as an array(so max size is needed)...
 * we can do this with double linked list
 *
 */

#define Q_SZ  500  


bst_t **creatQ(void)
{
    bst_t **q = (bst_t**)malloc (sizeof(bst_t) * Q_SZ);
    return q;
}

void enQ(bst_t **q, bst_t *node, int *rear)
{
    if (*rear == Q_SZ) {
        printf("Unable to insert\n");
        return;
    }

    q[(*rear)++] = node;
    //(*rear)++;

}

bst_t *deQ(bst_t **q, int *front, int *rear)
{
/*    if (*front == *rear) {
        printf("Queue is empty\n");
        return NULL;
    }
*/
    //(*front)++;
    //return q[(*front) - 1];
    return q[(*front)++];
}

void levelOrderTraversal(bst_t *root)
{
    int front, rear;
    bst_t *temp = root;
    bst_t **q;

    front = rear = 0;

    q = creatQ();
    if (!q) {
        printf("Unable to level traverse\n");
        return;
    }
    
    while (temp) {
        
        printf("%d ", temp->val);

        if (temp->left) {
            enQ(q, temp->left, &rear);
        }


        if (temp->right) {
            enQ(q, temp->right, &rear);
        }

        temp = deQ(q, &front, &rear);
    }
}

void search(bst_t **root, int val)
{
    bst_t *node = *root;

    while(node) {
        if(node->val == val) {
            printf("Found value: %d\n", node->val);
            return;
        }

        if (val < node->val) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    printf("%d NOT FOUND\n", val);
}


/*
 * https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 * https://www.geeksforgeeks.org/binary-search-tree-set-3-iterative-delete/
 *
 * case 1: node had 2 children node, search for the __rt_sub_tree's__ smallest value and replace it with the value.
 * case 2: No 2 children
 *          (i) No parent node (root node)
 *          (ii) Only one child
 */
void delete(bst_t **root, int val)
{

}


int main(void)
{
    int i = 0;
    bst_t *root = NULL;
    int arr[] = {10,4,15,2,5,13,22,1,14};

    for (i = 0; i < (sizeof(arr)/sizeof(int)); i++) {
        insert(&root, arr[i]);
    }
    
    insert(&root, 12);

    preOrderTraversal(root);
    printf("\n");
    
    inOrderTraversal(root);
    printf("\n");

    postOrderTraversal(root);
    printf("\n");

    levelOrderTraversal(root);
    printf("\n");

    search(&root,10);
    search(&root,4);
    search(&root,52);
    search(&root,14);
    search(&root,16);
    search(&root,12);

    delete(&root, 12);
    search(&root,12);

    return 0;
}

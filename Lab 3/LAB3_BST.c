// LAB3_BST.c - Lab 03 - Abdellah, Ghassel

#include <stdlib.h>
#include <stdio.h>
#include "LAB3_BST.h"

Node *initNode(Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
    Node *n = malloc(sizeof(Node));
    // initialize node if memory obtained
    if (n != NULL) {
        n->key = k;
        n->value = v;
        n->leftChild = NULL;
        n->rightChild = NULL;
    }
    return n;
}//initNode()

Tree *initTree(Key k, void *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
    Tree *t = malloc(sizeof(Tree));
    if (t != NULL)
        t->root = initNode(k, v);
    return t;
}//initTree()

void printTreeExplanation(void)
// Prints hint to reader what to expect on screen
{
    static int done = 0;
    if (!done) {
        printf("First time explanation of tree display:\n");
        printf("Every node is displayed as a comma-separated pair within brackets:");
        printf(" (kk,vv)\n");
        printf("where kk is the key and vv is the value\n");
        printf("A tree starts with a curly bracket { and ends with a curly bracket }.\n");
        printf("An empty tree will be {}\n");
        printf("A tree with no children will be { (kk,vv),{},{} }\n");
        printf("If either subtree is populated, it will be shown using the same ");
        printf("technique as described above\n");
        printf("(Hint: Start at p - and then match up all the remaining\n");
        printf("brackets, then interpret what those bracket pairs are telling\n");
        printf("you.)\n============\n\n");
        done = 1;
    }
}//printTreeExplanation()

void printTree(Node *root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
    // assume printTree magically knows the types in the tree node
    printTreeExplanation();
    // start of this tree
    printf("{");
    // values in the p node (assuming value is pointing to an integer)
    printf("(%d,%d),", root->key, *(int *) root->value);

    // Now show leftChild subtree or {} if there is no leftChild subtree
    if (root->leftChild != NULL) printTree(root->leftChild);
    else printf("{}");
    // Marker between leftChild and rightChild subtrees
    printf(",");
    // Now show rightChild subtree or {} if there is no rightChild subtree
    if (root->rightChild != NULL) printTree(root->rightChild);
    else printf("{}");
    // Close display of this tree with closing curly bracket
    printf("}");
}//printTree()

Node *find(Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// p holds pointer to p node of tree. Function returns immediately
// if either p pointer is null, or the node that p points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the leftChild or rightChild
// subtree.
{
    // termination conditions - either true, search is ended
    if ((root == NULL) || (root->key == k)) return root;
    // search continues.  Since this is a search tree, we know that
    // every key in the rightChild subtree is bigger than the key in the tree's
    // p, and every key in the leftChild subtree is smaller than the key in
    // the tree's p.  That allows us to choose the appropriate subtree
    // to search.
    if (k > root->key)
        // Key value sought is larger than current node key, so search rightChild
        // subtree
        return find(k, root->rightChild);
    else
        // Key value sought is smaller than current node key (the equal case
        // was handled as a termination condition in the first line), so
        // search leftChild subtree
        return find(k, root->leftChild);
}//find()

int insert(Key k, void *v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter p points to p node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
    int result = BST_FAIL;
    // this if statement can only be true with first p (p of whole tree)
    if (root == NULL) {
        Node *n = initNode(k, v);
        root = n;
        return BST_SUCCESS;
    }

    // already exists in tree ==> can't insert
    if (root->key == k)
        result = BST_FAIL;
    else if (k < root->key) {
        // key value less than key value in p node - try to insert into leftChild
        // subtree, if it exists.
        if (root->leftChild != NULL)
            // there is a leftChild subtree - insert it
            result = insert(k, v, root->leftChild);
        else {
            // new Node becomes the leftChild subtree
            Node *n = initNode(k, v);
            root->leftChild = n;
            result = BST_SUCCESS;
        }
    } else if (k > root->key) {            // test actually redundant
        // key is greater than this nodes key value, so value goes into rightChild
        // subtree, if it exists
        if (root->rightChild != NULL)
            // there is a rightChild subtree - insert new node
            result = insert(k, v, root->rightChild);
        else {
            // no rightChild subtree - new node becomes rightChild subtree
            Node *n = initNode(k, v);
            root->rightChild = n;
            result = BST_SUCCESS;
        }
    }
    return result;
}//insert()

int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see a conditional expression in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
    return (a >= b) ? a : b;
}//intmax()

int height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than larger height of node's two subtrees.
{
    int leftheight, rightheight;
    int nodeheight = -1;    // default returned for empty tree
    if (root != NULL) {
        leftheight = height(root->leftChild); //find height recursively of leftChild subtree
        rightheight = height(root->rightChild); //find height recursively of rightChild subtree
        nodeheight = 1 + intmax(leftheight, rightheight); //use 1 to offset the -1 and add the longer subtree
    }
    return nodeheight;

}//height()

Node *findParentHelper(Key k, Node *root)
// Help find parent of node with key == k. Parameter p is node with
// at least one child (see findParent()).
{
    //check that root's child is not NULL AND it is either equal to the root's left child OR right child
    if ((root->leftChild != NULL && root->leftChild->key == k) ||
        (root->rightChild != NULL && root->rightChild->key == k))
        return root;
    //if the key is greater than the root's key, than find parent recursively in the right child's subtree
    if (k > root->key) return findParentHelper(k, root->rightChild);
    else return findParentHelper(k, root->leftChild); //otherwise, find it recursively in left child's subtree

}//findparenthelper()

Node *findParent(Key k, Node *root)
//
{
    // Deal with special cases which could only happen for p
    // of whole tree
    if (root == NULL) return NULL;
    // real p doesn't have parent so we make it parent of itself
    if (root->key == k) return root;
    // p has no children
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
        return NULL;
    // Deal with cases where p has at least one child
    return findParentHelper(k, root);
}//findParent()

void delete(Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
//Three Cases: Node i.e. n has two children, one child or no children
{
    if (n->leftChild != NULL && n->rightChild != NULL) {    //two children - replace node with min key in right subtree
                                                            //Note: could also use max of left subtree
        Node *parentTemp = n;                               //set parentTemp to node
        Node *childTemp = n->rightChild;                    //set childTemp to node's left child

        while (childTemp->leftChild != NULL) {     //iterate through left subtree until childTemp is a leaf node
            parentTemp = childTemp;
            childTemp = childTemp->leftChild;
        }
        delete(parentTemp, childTemp);              //recursive call to delete parent Temp and childTemp

    } else if (n->rightChild == NULL) {             //one left child exists
        if (p->leftChild == n) p->leftChild = n->leftChild; //if n is p's left child, replace n with n's left child
        else p->rightChild = n->leftChild;          //if the node is right child, replace node with its left child
        free(n);                                    //remove node from memory

    } else if (n->leftChild == NULL) {              //one right child exists
        if (p->leftChild == n) p->leftChild = n->rightChild; //if n is p's left child, replace n with n's right child
        else p->rightChild = n->rightChild;         //if the node is right child, replace node with its right child
        free(n);                                    //remove node from memory

    } else {                                        //node is a leaf (no children)
        if (n->key < p->key) p->leftChild = NULL;   //delete node by setting parent's left child to NULL
        else p->rightChild = NULL;                  //delete node by setting parent's right child to NULL
        free(n);                                    //remove node from memory
    }
}//delete()

int withdraw(Key k, Node *root, Node *n)
// Withdraw does two things:
//	return a copy of the node with key k (and value v)
//	Delete the node with key k from the tree while ensuring the tree remains valid
{
    Node *p, *m;
    m = find(k, root);

    if (m != NULL) {
        // create a copy of the node with the same key and value
        n = initNode(m->key, m->value);
        p = findParent(k, root);
        // can delete the node
        delete(p, m);
        return 1;
    }

    return 0;
}//withdraw()

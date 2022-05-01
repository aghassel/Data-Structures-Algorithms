#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Tree node definition
typedef struct _trnode TreeNode, *pTreeNode;

struct _trnode {
    char *pname;            // name of parameter
    char *pvalue;        // value of parameter
    TreeNode *leftChild;        // pointer to left subtree
    TreeNode *rightChild;    // pointer to right subtree
};

#define SZ_TRNODE    (sizeof (TreeNode))

TreeNode *CreateNode(char *key, char *value)
// Create new node with key and value passed as string parameters. Copies are
// made of strings passed. Node can be created without value, but key is
// required. Key-only totalNodes useful for binary data - key exists or it doesn't.
{
    TreeNode *pn = NULL;

    // Parameter check first. Insist on key, but accept value if it is NULL.
    // Allows for parameters inform by either existing or not existing.
    if (key != NULL) {
        pn = (TreeNode *) malloc(SZ_TRNODE);
        if (pn) {
            pn->pname = strdup(key);
            pn->pvalue = value == NULL ? NULL : strdup(value);
            pn->leftChild = NULL;
            pn->rightChild = NULL;
        }
    }//if at least key was provided
    return pn;
}//initNode()


int DeleteNode(TreeNode *ptn)
// Delete TreeNode structure.  Only deals with one structure; does not delete
// left or right subtrees if they exist. (They should already have been dealt
// with before node is deleted.
{
    int rslt = -1;
    if (ptn != NULL) {
        free(ptn->pname);            // give up space for name
        if (ptn->pvalue != NULL)    // is there explicit parameter value?
            free(ptn->pvalue);        // give up space for parameter value
        // dta has been discarded, now discard actual node
        free(ptn);
        rslt = 0;
    }
    return rslt;
}//DeleteNode()


int CompareNodes(TreeNode *psrc, TreeNode *pdst, int *prslt)
// Comparison routine used to order nodes. Given two totalNodes, compares key values
// using strcmp(), result is returned in variable pointed to by prslt.
// Function returns -1 if something failed, 0 otherwise.
{
    if ((psrc == NULL) || (pdst == NULL) || (prslt == NULL)) return -1;
    *prslt = strcmpi(psrc->pname, pdst->pname);
    return 0;
}//CompareNodes()

// Structure definition for a Tree.
// Tree is basically pointer to top node in a tree.
typedef struct _tree {
    TreeNode *root;
} Tree;

// ----------------------------------------------------------------------------

// Code to create and manage trees and treenodes

// This code is only going to use one tree - declare it now.
Tree mytree = {NULL};

int insert_node(TreeNode *pnew, TreeNode **proot)
// Insert node pointed to by pnew into tree that has its root node pointed to
// by pointer pointed to by proot. (Referring to the diagram above, proot will
// be a pointer to "root", or "left" in the node or "right" in the node - all
// pointers to trees [or subtrees])
{
    TreeNode *pr;
    int rslt = -1;        // default return value is failure
    int cmprslt;        // hold result of comparisons

    // Check for obvious errors
    if ((proot == NULL) || (pnew == NULL)) return rslt;
    // Trivial case - tree pointed to by pointer that proot points to is empty
    // and we're inserting first node into this tree
    if (*proot == NULL) {
        *proot = pnew;        // think about where value pn is assigned -
        // not to proot, but to location that proot
        // points to.
        rslt = 0;            // insert worked
        //printf(" --- Value %s inserted at root\n", pnew->pname);
    } else {
        // Non-trivial case - have to find where node is to go. Take into
        // consideration whether new node has smaller or larger value than
        // existing one.
        pr = *proot;        // get pointer to node - makes things easier
        // Now determine whether new node value is less than, greater than or
        // equal to current root node value. Equal is rejected.
        if (CompareNodes(pnew, pr, &cmprslt) == 0) {
            if (cmprslt > 0) {
                // value being inserted belongs in right subtree
                //printf(" --- %s goes into Right subtree of value %s\n",
                //    pnew->pname, pr->pname);
                rslt = insert_node(pnew, &(pr->rightChild));
            } else if (cmprslt < 0) {
                // value being inserted belongs in left subtree
                //printf(" --- %s goes into Left subtree of value %s\n",
                // pnew->pname, pr->pname);
                rslt = insert_node(pnew, &(pr->leftChild));
            }//endif compare successful
        } else exit(1); //program will terminate if CompareNodes is not valid
    }
    // Note that, by default, if values are same, rslt is still -1
    return rslt;
}//insert_node()


void print_preorder(TreeNode *pn)
// Print tree values based on preorder traversal. Function gets pointer to
// node, then prints node value, left subtree, right subtree.
{
    // If we were passed NULL, we have nothing to do
    if (pn == NULL) return;
    printf(" %s\n ", pn->pname);
    print_preorder(pn->leftChild);
    print_preorder(pn->rightChild);
}//print_preorder()


void print_postorder(TreeNode *pn)
// Print tree values based on postorder traversal. Function gets pointer to
// node, then prints left subtree, right subtree, node value.
{
    // If we were passed NULL, we have nothing to do
    if (pn == NULL) return;
    print_postorder(pn->leftChild);
    print_postorder(pn->rightChild);
    printf(" %s\n", pn->pname);
}//print_postorder()


void print_inorder(TreeNode *pn)
// Print tree values based on inorder traversal. Function gets pointer to
// node, then prints left subtree, node value, right subtree.
{
    // If we were passed NULL, we have nothing to do
    if (pn == NULL) return;
    print_inorder(pn->leftChild);
    printf(" %s\n", pn->pname);
    print_inorder(pn->rightChild);
}//print_inorder()

int totalNodes(pTreeNode root) {
    int total;
    if (root != NULL)
        total = 1 + totalNodes(root->leftChild) + totalNodes(root->rightChild); //recursive call to get all roots
    else return 0; //if root is null, return 0 (nothing added)
    return total;
}//totalNodes()

TreeNode *find(char *k, TreeNode *root)
// Function locates node with key value equal to parameter k. Parameter
// p holds pointer to p node of tree. Function returns immediately
// if either p pointer is null, or the node that p points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the leftChild or rightChild
// subtree.
{
    // termination conditions - either true, search is ended
    if ((root == NULL) || (root->pvalue == k)) return root;
    // search continues.  Since this is a search tree, we know that
    // every key in the rightChild subtree is bigger than the key in the tree's
    // p, and every key in the leftChild subtree is smaller than the key in
    // the tree's p.  That allows us to choose the appropriate subtree
    // to search.
    if (k > root->pvalue)
        // Key value sought is larger than current node key, so search rightChild
        // subtree
        return find(k, root->rightChild);
    else
        // Key value sought is smaller than current node key (the equal case
        // was handled as a termination condition in the first line), so
        // search leftChild subtree
        return find(k, root->leftChild);
}//find()

TreeNode *findParentHelper(char *k, TreeNode *root)
// Help find parent of node with key == k. Parameter p is node with
// at least one child (see findParent()).
{
    if (root == NULL) return NULL;
    //check that root's child is not NULL AND it is either equal to the root's left child OR right child
    if ((root->leftChild != NULL && root->leftChild->pvalue == k) ||
        (root->rightChild != NULL && root->rightChild->pvalue == k))
        return root;
    //if the key is greater than the root's key, than find parent recursively in the right child's subtree
    if (k > root->pvalue) return findParentHelper(k, root->rightChild);
    else return findParentHelper(k, root->leftChild); //otherwise, find it recursively in left child's subtree

}//findparenthelper()

TreeNode *findParent(char *k, TreeNode *root)
//
{
    // Deal with special cases which could only happen for p
    // of whole tree
    if (root == NULL) return NULL;
    // real p doesn't have parent so we make it parent of itself
    if (root->pvalue == k) return root;
    // p has no children
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
        return NULL;
    // Deal with cases where p has at least one child
    return findParentHelper(k, root);
}//findParent()

void delete(TreeNode *p, TreeNode *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
//Three Cases: Node i.e. n has two children, one child or no children
{
    if (p == NULL || n == NULL) return;
    if (n->leftChild != NULL && n->rightChild != NULL) {    //two children - replace node with min key in right subtree
        //Note: could also use max of left subtree
        TreeNode *parentTemp = n;                               //set parentTemp to node
        TreeNode *childTemp = n->rightChild;                    //set childTemp to node's left child

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
        if (n->pvalue < p->pvalue) p->leftChild = NULL;   //delete node by setting parent's left child to NULL
        else p->rightChild = NULL;                  //delete node by setting parent's right child to NULL
        free(n);                                    //remove node from memory
    }
}//delete()

int main(int argc, char *argv[], char *environ[])
// Test code to illustrate how binary search tree works with key and data
// being strings. We use a test file that resembles a DOS/Windows system
// configuration (INI) file.
{
    int i;
    TreeNode *pnode;
    int rslt;
    char *p, *q, *r, *pID, *pPassword, *qID, *qPassword, *rID, *rPassword;
    FILE *ids, *lookups, *deletes;
    char *pbuff;

    //read IDENTS.TXT file and checks if file could be read

    ids = fopen("IDENTS.txt", "r");
    if (deletes == NULL) {
        fprintf(stderr, "ERROR: Cannot open data file\n");
        return -1;
    }

    //read DELETES.TXT file and checks if file could be read
    deletes = fopen("DELETES.txt", "r");
    if (deletes == NULL) {
        fprintf(stderr, "ERROR: Cannot open data file\n");
        return -1;
    }

    //reads lookups file and checks if file could be read
    lookups = fopen("LOOKUPS.TXT", "r");
    if (deletes == NULL) {
        fprintf(stderr, "ERROR: Cannot open data file\n");
        return -1;
    }

    // Get buffer to read data file into.
    pbuff = (char *) malloc(256);
    if (pbuff == NULL) {
        fprintf(stderr, "ERROR: Cannot get memory for buffer\n");
        return -1;
    }

    while (!feof(ids)) { //iterate until we reached the end of the file
        p = fgets(pbuff, 256, ids);
        if (p == NULL) break;
        while (*p == ' ') p++;
        pID = p;
        p += 9;
        while (*p == ' ') p++;
        *p = '\0';
        p++;
        while (*p == ' ') p++;
        pPassword = p;
        p++;
        while (*p != '\n' && *p != '\r') p++;
        *p = '\0';
        pnode = CreateNode(pID, pPassword);     //create a new node for pID and pPassword
        insert_node(pnode, &mytree.root);       //insert the node into the BST
    }
    fclose(ids); //close the file

    printf("BST NODES: %d\n", totalNodes(mytree.root)); //prints the number of nodes in the BST
    //Note: I edited the function insert_node using CompareNodes(), so if it isn't a BST, it terminates the program

    //iterate until we reached the end of the file
    while (!feof(deletes)) {
        q = fgets(pbuff, 256, deletes);
        if (q == NULL) break;
        while (*q == ' ') q++;
        qID = q;
        q += 9;
        while (*q == ' ') q++;
        *q = '\0';
        q++;
        while (*q == ' ') q++;
        qPassword = q;
        q++;
        while (*q != '\n' && *q != '\r') q++;
        *q = '\0';

        pTreeNode nn = find(qID, mytree.root);          //find the ID we are trying to delete in the BST
        pTreeNode pp = findParent(qID, mytree.root);    //find the parent of the ID we are trying to delete in the BST
        delete(pp, nn);                                 //delete the ID, and rearrange the tree
        //I suspect there's an error with my find/findParent function since no nodes are deleted, I've spent countless
        //hours debugging my code and looking through it, without figuring it out
    }
    fclose(deletes);

    printf("NODES AFTER DELETES: %d\n", totalNodes(mytree.root)); //Prints number of nodes after deleted nodes

    //iterate until we reached the end of the file
    while (!feof(lookups)) {
        r = fgets(pbuff, 256, lookups);
        if (r == NULL) break;
        while (*r == ' ') r++;
        rID = r;
        r += 9;
        while (*r == ' ') r++;
        *r = '\0';
        r++;
        while (*r == ' ') r++;
        rPassword = r;
        r++;
        while (*r != '\n' && *r != '\r') r++;
        *r = '\0';

        //look for each ID in the BST
        pTreeNode lookupFinder = find(qID,
                                      mytree.root); //find the ID we are looking for in the BST (error with my find function)
        if (lookupFinder != NULL)
            printf("ID %s   PASSWORD %s\n", qID, lookupFinder->pvalue); //If the ID is found, print out the password
        else printf("ID %s   PASSWORD <NOT FOUND>\n", qID); //Otherwise print "NOT FOUND" if it's not in the BST
    }
    fclose(lookups);

    return 0;
}//main()

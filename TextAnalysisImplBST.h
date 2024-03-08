#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

// declare tree node with data, right and left child
struct node
{
    struct node *rightChild; // right child
    char data[100];          // data
    int count;
    struct node *leftChild; // left child
};

extern struct node *root; // initialize the root node

// define insertNode method that inserts a node on the tree
void insertNode(char A[]);


int maxTreeDepth(node *root);

/**
 * convert word to lower case and terminate when you get to the ' character
 */

void process_word(char A[]);

// recursive inorder traversal
void Inorder(node *p, FILE *o, int i);

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

struct node *root = nullptr; // initialize the root node

// define insertNode method that inserts a node on the tree
void insertNode(char A[])
{
    // declare and initialize current node pointer to root node
    struct node *current = root;
    struct node *previous, *newNode; // declare previous and newNode
    int compareResult;

    // check if root is a nullptr
    if (root == nullptr)
    {
        newNode = new node; // create a new node
        memset(newNode->data, '\0', sizeof(newNode->data));
        strcpy(newNode->data, A); // set it's data
        newNode->count = 1;
        newNode->leftChild = newNode->rightChild = nullptr; // set the left and right child to null

        root = newNode; // set root to point to the newNode

        return; // exit the method
    }

    while (current != nullptr)
    {
        // set previous equal to previous
        previous = current;

        compareResult = strcmp(A, current->data);

        if (compareResult < 0)
        {
            current = current->leftChild;
        }
        else if (compareResult > 0)
        {
            current = current->rightChild;
        }
        else
        {
            current->count++;
            return;
        }
    }

    newNode = new node; // create a new node
    memset(newNode->data, '\0', sizeof(newNode->data));
    strcpy(newNode->data, A);      // set it's data
    newNode->leftChild = nullptr;  // set left child to a null pointer
    newNode->rightChild = nullptr; // set right child to a null pointer
    newNode->count = 1;

    compareResult = strcmp(A, previous->data);

    if (compareResult < 0)
    {
        previous->leftChild = newNode;
    }
    else
    {
        previous->rightChild = newNode;
    }
}


int maxTreeDepth(node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        // Calculate the depth of the left and right
        int leftDepth = maxTreeDepth(root->leftChild);
        int rightDepth = maxTreeDepth(root->rightChild);

        // Return the maximum depth
        return max(leftDepth, rightDepth) + 1;
    }
}

/**
 * convert word to lower case and terminate when you get to the ' character
 */

void process_word(char A[])
{
    for (int i = 0; A[i] != '\0'; i++)
    {

        if (A[i] >= 'A' && A[i] <= 'Z')
        {
            A[i] += 32;
        }

        if (A[i] == '\'' || (!(A[i] >= 'a' && A[i] <= 'z') && A[i] != '-' ))
        {
            for (int j = i; A[j] != '\0'; j++)
            {
                A[j] = '\0';
            }
            return;
        }
    }
}

// recursive inorder traversal
void Inorder(node *p, FILE *o, int i)
{
    if (p)
    {
        Inorder(p->leftChild, o, i + 1);                                // recursive call
        // cout << p->data << " " << p->count << " (" << i << ")" << endl; // output to screen
        fprintf(o, "%-15s %-5d (%d) \n", p->data, p->count, i);           // write to file
        Inorder(p->rightChild, o, i + 1);                               // recursive call
    }
}

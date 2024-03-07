/*
Author: Peter Ahumuza
AndrewID: pahumuza

Usage: <executable> <input_file> <output_file>

Functionality: 
    This program reads words from multiple input text files, converts them to lowercase, t
    and inserts them into a binary search tree. 
    It then calculates the maximum and average number of probes required to insert the words into the tree 
    and outputs the results to an output file.

Format of Input: 
    Each input file contains a list of words separated by whitespace characters. 
    The program accepts multiple input files as command-line arguments.

Format of Output: 
    The output file contains the path of each input file processed, 
    followed by the maximum and average number of probes required for each file. 
    It also includes an inorder traversal of the binary search tree, 
    showing each word along with its count and depth in the tree.

Solution Strategy: 
    The program uses a binary search tree to efficiently store and retrieve words. 
    It processes each input file separately, inserting words into the tree and calculating the maximum 
    and average number of probes. 
    It then performs an inorder traversal of the tree to output the word counts and depths.

Testing: 
    The code was tested with various test cases, including empty input files, 
    input files with single and multiple words, 
    and input files with words containing special characters and uppercase letters.

Complexity Analysis: 
    The time complexity of the program is O(N*log(N)), 
    where N is the total number of words across all input files. 
    This is because each word insertion operation in the binary search tree takes O(log(N)) time, 
    and there are N words to be inserted. The space complexity is O(N), 
    where N is the total number of unique words across all input files, 
    as each word is stored once in the binary search tree.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

#define andrewID "pahumuza"


// declare tree node with data, right and left child
struct node
{
    struct node *rightChild; // right child
    char data[100]; // data 
    int count;
    struct node *leftChild; // left child
};


struct node *root =nullptr; // initialize the root node

// define insertNode method that inserts a node on the tree
void insertNode(char A[])
{
    //declare and initialize current node pointer to root node
    struct node *current = root;
    struct node *previous, *newNode; //declare previous and newNode
    int compareResult;

    //check if root is a nullptr
    if(root == nullptr)
    {
        newNode = new node; // create a new node
        memset(newNode->data, '\0', sizeof(newNode->data));
        strcpy(newNode->data, A); // set it's data
        newNode->count = 1;
        newNode->leftChild = newNode->rightChild = nullptr; // set the left and right child to null

        root = newNode; // set root to point to the newNode

        return; // exit the method
    }

    while(current != nullptr)
    {
        // set previous equal to previous
        previous = current;

        compareResult = strcmp(A,current->data);

        if(compareResult < 0)
        {
            current = current->leftChild;
        }
        else if(compareResult > 0)
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
    strcpy(newNode->data, A); // set it's data
    newNode->leftChild = nullptr; // set left child to a null pointer
    newNode->rightChild = nullptr; // set right child to a null pointer
    newNode->count = 1;

    compareResult = strcmp(A,previous->data);

    if(compareResult < 0){
        previous->leftChild = newNode;
    }
    else
    {
        previous->rightChild = newNode;
    }
}

int maxTreeDepth(node* root) {
    if (root == nullptr) {
        return 0;
    } else {
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

void process_word(char A[]){
    int del = 0;

    for(int i=0; A[i]!='\0'; i++){

        if(A[i] >= 'A' && A[i] <= 'Z'){
            A[i] += 32;
        }
        
        if( A[i] == '\''){
            A[i] = '\0';
            return;
        }
    }
}

//recursive inorder traversal
void Inorder(node *p,FILE *o, int i) {
    if (p){
        Inorder(p->leftChild,o,i+1); // recursive call
        cout << p->data <<" " << p->count << " (" << i <<")"<< endl; // output to screen
        fprintf(o, "%-10s %d (%d) \n", p->data, p->count, i); // write to file
        Inorder(p->rightChild,o,i+1); // recursive call
    }
}

int main(int argc, char *argv[]){

    if (argc != 3) {
        cout << "Error" << endl;
        cout << "Usage: " << argv[0] << " <input_file>" << " <output_file>" << endl;
        return 1;
    }

    char *input_txt, *output_txt;
    char path[100], word[100];
    char *textfile_paths[100]; // array to s
    int i=0;

    input_txt = argv[1];
    output_txt = argv[2];

    FILE* inputFile= fopen(input_txt,"r"); //open input file with read permission
    FILE* outputFile= fopen(output_txt,"w"); //open output file for writing

    fprintf(outputFile, "%s\n", andrewID);

     if (!inputFile) {
        cout << "Please make sure the input file exists." << endl;
        return 1;
    }

    while(fscanf(inputFile, "%s", &path) != EOF){
        textfile_paths[i] = new char[strlen(path) + 1]; // assign memory
        strcpy(textfile_paths[i], path); // copy path
        i++;
    }

    fclose(inputFile);

    for(int n = 0; n < i; n++){
        inputFile= fopen(textfile_paths[n],"r");

        if (!inputFile) {
            cout << "Unable to open file: " << textfile_paths[n] << endl;
            continue; // skip if the program cannot open the file
        }

        cout << textfile_paths[n] << endl;
        fprintf(outputFile, "%s \n", textfile_paths[n]);

        while(fscanf(inputFile, "%s", &word) != EOF)
        {
            process_word(word);
            
            insertNode(word);
            // cout << word << endl;
        }

        fclose(inputFile);

        int maxDepth = maxTreeDepth(root);
        fprintf(outputFile, "Maximum number of probes: %d \n", maxDepth);
        fprintf(outputFile, "Average number of probes: %.1f \n", static_cast<float>(maxDepth+1)/2 );

        Inorder(root,outputFile,0);//inorder traversel
        fprintf(outputFile, "%s \n", "--------------------");
        root = nullptr; //reset root

    }

    // Free memory
    for (int n = 0; n < i; n++) {
        delete[] textfile_paths[n];
    }

    return 0;
}
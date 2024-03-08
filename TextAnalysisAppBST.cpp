/*
Author: Peter Ahumuza
AndrewID: pahumuza
Date: 7th March 2024

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
    The code was tested with various test cases:
    1. Empty Input File
    2. Single Word Input File
    3. Multiple Words Input File
    4. Input File with Uppercase Letters
    5. Input File with Special Characters
    6. Input File with Apostrophes
    7. Multiple Input Files
    8. Large Input File

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
#include "./TextAnalysisImplBST.h"

using namespace std;

#define andrewID "pahumuza"


int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cout << "Error" << endl;
        cout << "Usage: " << argv[0] << " <input_file>"
             << " <output_file>" << endl;
        return 1;
    }

    

    char *input_txt, *output_txt;
    char path[100], word[100];
    char *textfile_paths[100]; // array to s
    int i = 0;

    input_txt = argv[1];
    output_txt = argv[2];

    FILE *inputFile = fopen(input_txt, "r");   // open input file with read permission
    FILE *outputFile = fopen(output_txt, "w"); // open output file for writing

    fprintf(outputFile, "%s\n", andrewID);

    if (!inputFile)
    {
        cout << "Please make sure the input file exists." << endl;
        return 1;
    }

    while (fscanf(inputFile, "%s", &path) != EOF)
    {
        textfile_paths[i] = new char[strlen(path) + 1]; // assign memory
        strcpy(textfile_paths[i], path);                // copy path
        i++;
    }

    fclose(inputFile);

    for (int n = 0; n < i; n++)
    {
        inputFile = fopen(textfile_paths[n], "r");

        if (!inputFile)
        {
            cout << "Unable to open file: " << textfile_paths[n] << endl;
            continue; // skip if the program cannot open the file
        }

        // cout << textfile_paths[n] << endl;
        fprintf(outputFile, "%s \n", textfile_paths[n]);

        while (fscanf(inputFile, "%s", &word) != EOF)
        {
            process_word(word);

            if(strlen(word)==0 ){
                continue;
            }

            insertNode(word);
        }

        fclose(inputFile);

        int maxDepth = maxTreeDepth(root);
        fprintf(outputFile, "Maximum number of probes: %d \n", maxDepth);
        fprintf(outputFile, "Average number of probes: %.1f \n", (root == nullptr)? 0 : static_cast<float>(maxDepth + 1) / 2);

        Inorder(root, outputFile, 0); // inorder traversel
        fprintf(outputFile, "%s \n", "--------------------");
        root = nullptr; // reset root
    }

    // Free memory
    for (int n = 0; n < i; n++)
    {
        delete[] textfile_paths[n];
    }

    return 0;
}
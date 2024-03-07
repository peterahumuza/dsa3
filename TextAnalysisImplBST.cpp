/*
Author: Peter Ahumuza
AndrewID: pahumuza

Functionality: 


Format of Input: 

Format of Output: 


Solution Strategy: 


Testing: The code was tested with various test cases including:


Complexity Analysis: 

*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 


using namespace std;

#define andrewID "pahumuza"

struct word_properties
{
   int ascii_val;
   char word[100];
};


int covert_to_ascii(char word[],int wordLength){
    int total,i =0;

    for(int i =0; i < wordLength; i++)
    {
        total += static_cast<int>(word[i]);
    }

    return total;
}

// declare tree node with data, right and left child
struct node
{
    struct node *rightChild; // right child
    char data[100]; // data 
    struct node *leftChild; // left child
};

void convert_to_lower_case(char A[]){

       for(int i=0; A[i]!='\0'; i++){

        if(A[i] >= 'A' && A[i] <= 'Z'){
            A[i] += 32;
        }
    }
}

int main(int argc, char *argv[]){

    if (argc != 2) {
        cout << "Error" << endl;
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    char *input_txt;
    char path[100], word[100];
    char *textfile_paths[100]; // array to s
    int i=0;

    input_txt = argv[1];

    FILE* inputFile= fopen(input_txt,"r"); //open input file with read permission

     if (!inputFile) {
        cout << "Please make sure the file exists." << endl;
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

        while(fscanf(inputFile, "%s", &word) != EOF)
        {
            convert_to_lower_case(word);
            cout << word << endl;
        }

        fclose(inputFile);

    }

    // Free memory
    for (int n = 0; n < i; n++) {
        delete[] textfile_paths[n];
    }

    return 0;
}
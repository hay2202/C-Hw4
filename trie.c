#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NUM_LETTERS ((int)26)

typedef struct node {
    char letter;           
    long unsigned int count;
    struct node* children[NUM_LETTERS];
    enum {FALSE=0, TRUE=1} end;
    int numOfChild;
} node;

// return a new node
node* new_node(){
    node *p_node = NULL;
    p_node = (node*) malloc(sizeof(node));
    if(p_node){
        p_node -> end = FALSE;      //if its end of word
        p_node -> count = 0;        //num of apperance
        p_node -> numOfChild = 0;   
        for(int i=0; i<NUM_LETTERS; i++)
            p_node -> children[i] = NULL;
    }
    return p_node;
}

// upper case to lower case and return index
int charToIndex(char c){
   if(c >= 65 && c <= 90)
         c = c+32;
    if (c <= 96 && c >= 123)        //if its not a ABC char
        return -1;
    return (c -'a');
}

// insert a word to TRIE
void insert(node *root, char *w){
    int len = strlen(w);
    int index;
    node *curr = root;

    for (size_t i = 0; i < len; i++)
    {
       if((index = charToIndex(w[i])) != -1){
            if (!curr -> children[index]){
                curr -> children[index] = new_node();
                curr -> numOfChild++;
            }  
        curr = curr -> children[index];
       }
    }

    curr -> end = TRUE;
    curr -> count++;
}

void print_word(node *root, char s[], int level){
    if (root -> end)
    {
        s[level] =0;
        printf("%s\t%ld\n", s, root -> count);
    }
    
    for (int i = 0; i < NUM_LETTERS; i++)  
    { 
        if (root->children[i])  
        { 
            s[level] = i + 'a'; 
            print_word(root->children[i], s, level + 1); 
        } 
    }
}

void r_print_word(node *root, char s[], int level){
    if (root -> end)
    {
        s[level] =0;
        printf("%s\t%ld\n", s, root -> count);
    }
    
    for (int i = NUM_LETTERS-1 ; i >=0 ; i--)  
    { 
        if (root->children[i])  
        { 
            s[level] = i + 'a'; 
            r_print_word(root->children[i], s, level + 1); 
        } 
    }
}

int main(int argc, char *argv[]){
  char keys[][6] = {"aBc", "b#ac", "bac", "abc", "ddd", "aaa"}; 
  
    node *root = new_node(); 
    int n = sizeof(keys)/sizeof(keys[0]); 

    for (int j = 0; j < n; j++) 
        insert(root, keys[j]); 
  
    int level = 0; 
    char str[20]; 
    
    if (argv[1] == 'r')
        r_print_word(root, str, level); 
    else
        print_word(root, str, level); 
    
    return 0;
}




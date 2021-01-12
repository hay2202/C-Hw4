#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NUM_LETTERS 26
#define WORD 30

typedef struct node {
    long unsigned int count;        //num of apperance
    struct node* children[NUM_LETTERS];
    enum {FALSE=0, TRUE=1} end;        //if its end of word
    int numOfChild;                 // how many child has
} node;

// return a new node
node* new_node(){
    node *p_node = NULL;
    p_node = (node*) malloc(sizeof(node));
    if(p_node){
        p_node -> end = FALSE;      
        p_node -> count = 0;        
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
    if (c <= 96 || c >= 123)        //if its not a ABC char
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
    
    if (len > 0)
    {
        curr -> end = TRUE;
        curr -> count++;
    }
}

// print trie 
void print_word(node *root, char s[], int level){
    node * curr =root;
    if (!curr)
        return;
    if (curr -> end)
    {
        s[level] =0;
        printf("%s\t%ld\n", s, curr -> count);
    }

    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (curr->children[i])
        {
            s[level] = i + 'a';
            print_word(curr->children[i], s, level + 1);
        }
    }
}

// print reverse order
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

//getting word
int get_word(char w[]){
    int num_of_char = 1;
    char c ;

    if(scanf("%c", &c)<0)
        return 0;

    while(c != '\n' && c != '\t' && c != ' ' && c != '\r' && num_of_char != WORD){
        strncat(w,&c,1);
        num_of_char++;
        scanf("%c", &c);
    }
    return num_of_char;
}

// free all dynamic memory
void clean(node *root){
    if (!root)
        return;
    node * temp = root;
    for (int i = 0; i <NUM_LETTERS ; ++i) {
        clean(temp -> children[i]);
        free(temp->children[i]);
    }
}

int main(int argc, char *argv[]){
    char *word = (char*) calloc(WORD,sizeof(char));

    node *root = new_node();

    while (get_word(word) > 0)
    {
        insert(root, word);
        memset(word, 0, WORD);
    }

    free(word);
    int level = 0;
    char str[30];

    if (argc > 1)
        r_print_word(root, str, level);
    else
        print_word(root, str, level);

    clean(root);
    free(root);
    return 0;
}




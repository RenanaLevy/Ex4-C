#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "frequency.h"

//Converts upper letter to lower letter.
char convertToLowerLetter(char c){
    if (c < 'a')
    {
        return 'a' + (c - 'A');
    }
    else
    {
        return c;
    }
}

//Allocation to new node.
node* newNode(char c, node* parent){
    node *n = NULL;
    n = (node*)malloc(sizeof(node));
    if(!n) {return NULL;}

    //Initialize the new node.
    n->letter = c;
    n->prev = parent;
    n->haveChildren = FALSE;
    n->numOfWord = 0;
    for (size_t i = 0; i < NUM_LETTERS; i++)
    {
        n->children[i] = NULL;
    }
    return n;
}

//Enter new word to the given trie.
boolean newWord(node *t, char *s, char const flag){
    char lowerLetter;
    node **current = &t;
    while (*s)
    {
        if(((*s < 'a') || (*s > 'z')) && ((*s <'A') || (*s > 'Z')))
        {
            s++;
            continue;
        }

        lowerLetter = convertToLowerLetter(*s);

        t->haveChildren = TRUE;
        if (flag == 'l')
        {
            current = &((*current)->children[lowerLetter - 'a']);
        }
        else if(flag == 'r')
        {
            current = &((*current)->children['z' - lowerLetter]);
        }
        
        //lowerLetter = convertToLowerLetter(*s);

        if (!(*current))
        {
            *current = newNode(lowerLetter, t);
            if (!(*current))
            {
                return FALSE;
            }
        }
        t = *current;
        s++;
    }
    (*current)->numOfWord += 1;
    return TRUE;
}

//Print a word w.
void printWord(node *w, char const flag){
    printf("%c", w->letter);
    while (w->haveChildren)
    {
        if (w->numOfWord)
        {
            printf(" %d\n", w->numOfWord);
            return;
        }
        int i;
        for (i = 0; i < NUM_LETTERS; i++)
        {
            if (w->children[i])
            {
                w = w->children[i];
                break;
            }
            
        }
        if (i == NUM_LETTERS)
        {
            w->haveChildren = FALSE;
        }
        
        printf("%c", w->letter);
    }
    if (w->numOfWord)
    {
        printf(" %d\n", w->numOfWord);
    }
    delet(w, flag); 
}

//Print all the words in the dictionary.
void printAll(node *t, char const flag){
    if (t->haveChildren)
    {
        for (size_t i = 0; i < NUM_LETTERS; i++)
        {
            while (t->children[i])
            {
                printWord(t->children[i], flag);
            }
        }
    }
    free(t);
}

//Free memory if the program successful.
void delet(node *n, char const flag){
    while (!n->haveChildren && n->prev)
    {
        node *del = n;
        n = n->prev;
        char c = del->letter;
        free(del);
        size_t i;
        if (flag == 'l')
        {
            i = c - 'a';
        }
        else if (flag == 'r')
        {
            i = 'z' - c;
        }
        
        n->children[i] = 0;
        for (; i < NUM_LETTERS; i++)
        {
            if (n->children[i])
            {
                return;
            }
        }
        n->haveChildren = FALSE;
    }
}

//Free trie if the allocation is failed.
void freeErr(node *trie){
    if (!trie->haveChildren)
    {
        free(trie);
        return;
    }
    
    for (size_t i = 0; i < NUM_LETTERS; i++)
    {
        if (trie->children[i])
        {
            freeErr(trie->children[i]);
        }
        
    }

    trie->haveChildren = FALSE;
    freeErr(trie);
}


int main(int argc, char const *argv[]){
    node *trie = newNode(0, 0);
    char flag;
    char c;
    char *word = 0;
    int len = 1;
    if (argc == 1)
    {
        flag = 'l';
    }
    else if (*argv[1] == 'r')
    {
        flag = 'r';
    }
    while (scanf("%c", &c) != EOF)
    {
        if ((c != ' ') && (c != '\n') && (c != '\t'))
        {
            len++;
            word = (char*)realloc(word, sizeof(char)*len);
            word[len - 2] = c;
            word[len - 1] = '\0';
        }
        else
        {
            boolean success = newWord(trie, word, flag);
            if(!success)
            {
                freeErr(trie);
                perror("The allocation is failed");
                exit(1);
            }
            char *del = word;
            word = 0;
            len = 1;
            free(del);
        }
        
    }
    if (word)
    {
        boolean success = newWord(trie, word, flag);
        if(!success)
        {
            freeErr(trie);
            perror("The allocation is failed");
            exit(1);
        }
        if (word)
        {
            free(word);
        }
    }
    printAll(trie, flag);
}
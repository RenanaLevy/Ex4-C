#ifndef NUM_LETTERS 
    #define NUM_LETTERS ((int)26)
#endif

#ifndef boolean
    typedef enum {FALSE=0, TRUE=1} boolean;
#endif

#ifndef node
    typedef struct node{
        char letter;
        int numOfWord;
        struct node *children[NUM_LETTERS];
        int haveChildren;
        struct node *prev;
    }node;
#endif

char convertToLowerLetter(char);
boolean newWord(node *, char *, char const);
node* newNode(char, node *);
void printAll(node *, char const);
void printWord(node *, char const);
void delet(node *, char const);
void freeErr(node *);
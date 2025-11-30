#ifndef C_YA_TOKENIZER_H
#define C_YA_TOKENIZER_H

#include <stdbool.h>

#define ITEM_CONST 5000
#define MAX_LEN 200
#define SIZE_CONST 1000 // All sizes will fall in the 1000 to 4999 range.
#define ITEM_CONST 5000 // All items will fall in the 5000 to 19999 range.
#define MODIFIER_CONST 20000 // All modifiers will fall in the 20000 to 99999 range.
#define DEBUG_CONST 100000 // All debugs will be in the 100000's and above.

struct AppState;

struct Order {
    int num;
    int size;
    int item;
    int modifier;
    int debug;
};

struct WordNumber {
    char *word;
    int value;
};

extern struct WordNumber table[];

bool is_number(char word[MAX_LEN]);
bool is_size(char word[MAX_LEN]);
bool is_item(char word[MAX_LEN]);
bool is_debug_cmd(char word[MAX_LEN], char input[MAX_LEN]);
bool is_modifier(char word[MAX_LEN]);
bool is_numword(char word[MAX_LEN]);

void singularize(char word[MAX_LEN]);
void join_tokens(char *out, char tokens[][200], int start, int end);
int ascii_word(char word[MAX_LEN]);
int parse_item_words(char *words[], int count);
int parse_modifier_words(char *words[], int count);
int parse_number_words(char *words[], int count);
int number_word_to_value(const char *word);

int tokenize(char input[], struct Order *order_pointer, struct AppState *app_pointer);

#endif

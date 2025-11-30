#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "c-ya_tokenizer.h"
#include "the17th.h"

#define WHITE_SPACE 32
#define NEWLINE 10
#define UNDERSCORE 95
#define FORWARDSLASH 47
#define HYPHEN 45
#define PERIOD 46
#define NUM_START 48
#define NUM_END 57
#define CAPITAL_START 65
#define CAPITAL_END 90
#define LOWER_START 97
#define LOWER_END 122

#define MAX_TOKENS 50
#define MAX_ITEM_WORDS 20
#define MAX_MOD_WORDS 20
#define MAX_NUM_WORDS 20

struct WordNumber table[] = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3},
    {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7},
    {"eight", 8}, {"nine", 9}, {"ten", 10},
    {"eleven", 11}, {"twelve", 12}, {"thirteen", 13},
    {"fourteen", 14}, {"fifteen", 15}, {"sixteen", 16},
    {"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19},
    {"twenty", 20}, {"thirty", 30}, {"forty", 40},
    {"fifty", 50}, {"sixty", 60}, {"seventy", 70},
    {"eighty", 80}, {"ninety", 90},
    {"hundred", 100}, {"thousand", 1000}
};

void singularize(char *word) {
    int length = strlen(word);

    if (strcmp(word, "fries") == 0) {
        strcpy(word, "fry");
        return;
    }

    if (strcmp(word, "sandwiches") == 0) {
        strcpy(word, "sandwich");
        return;
    }

    length = strlen(word);

    if (length > 0 && word[length - 1] == 's') {
        word[length - 1] = '\0';
        return;
    }
}

void join_tokens(char *out, char tokens[][200], int start, int end) {
    out[0] = '\0';

    for (int k = start; k <= end; k++) {
        strcat(out, tokens[k]);
        if (k < end) strcat(out, "_");
    }
}

int ascii_word(char word[MAX_LEN]) {
    // Major edit of 11-30-2025, at 4:37 AM EST. Changing to a polynomial rolling hash.

    int hash = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        hash = hash * 31 + word[i];
    }

    return hash;
}

int number_word_to_value(const char *word) {
    int count = sizeof(table) / sizeof(table[0]);

    for (int i = 0; i < count; i++) {
        if (strcmp(word, table[i].word) == 0) {
            return table[i].value;
        }
    }

    return -1;
}

int parse_item_words(char *words[], int count) {
    int total = 0;

    for (int i = 0; i < count; i++) {
        total += ascii_word(words[i]) + ITEM_CONST;
    }

    return total;
}

int parse_modifier_words(char *words[], int count) {
    int total = 0;

    for (int i = 0; i < count; i++) {
        total += ascii_word(words[i]) + MODIFIER_CONST;
    }

    return total;
}

int parse_number_words(char *words[], int count) {
    int total = 0;
    int current = 0;

    for (int i = 0; i < count; i++) {
        int v = number_word_to_value(words[i]);

        if (v == 100) {
            if (current == 0) {
                current = 1;
            }
            current *= 100;
        }

        else {
            current += v;
        }
    }

    total += current;
    return total;
}

bool is_number(char word[MAX_LEN]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!(word[i] >= NUM_START && word[i] <= NUM_END)) {
            return false; // Found a non-digit.
        }
    }
    return true; // All characters were apparently digits.
}

bool is_size(char word[MAX_LEN]) {
    char *pointer = word;

    singularize(pointer);

    if (strcmp(word, "sm") == 0) {
        return true;
    }

    else if (strcmp(word, "small") == 0) {
        return true;
    }

    else if (strcmp(word, "md") == 0) {
        return true;
    }

    else if (strcmp(word, "medium") == 0) {
        return true;
    }

    else if (strcmp(word, "lg") == 0) {
        return true;
    }

    else if (strcmp(word, "large") == 0) {
        return true;
    }

    else if (strcmp(word, "pc") == 0) {
        return true;
    }

    else if (strcmp(word, "piece") == 0) {
        return true;
    }

    else {
        return false;
    }
}

bool is_item(char word[MAX_LEN]) {
    char *pointer = word;

    singularize(pointer);

    if (strcmp(word, "fry") == 0) {
        return true;
    }

    else if (strcmp(word, "burger") == 0) {
        return true;
    }

    else if (strcmp(word, "cheeseburger") == 0) {
        return true;
    }

    else if (strcmp(word, "chicken") == 0) {
        return true;
    }

    else if (strcmp(word, "tender") == 0) {
        return true;
    }

    else if (strcmp(word, "sandwich") == 0) {
        return true;
    }

    else if (strcmp(word, "nugget") == 0) {
        return true;
    }

    else if (strcmp(word, "wing") == 0) {
        return true;
    }

    else if (strcmp(word, "onion") == 0) {
        return true;
    }

    else if (strcmp(word, "ring") == 0) {
        return true;
    }

    else if (strcmp(word, "hotdog") == 0) {
        return true;
    }

    else if (strcmp(word, "house") == 0) {
        return true;
    }

    else if (strcmp(word, "caesar") == 0) {
        return true;
    }

    else if (strcmp(word, "salad") == 0) {
        return true;
    }

    else if (strcmp(word, "soda") == 0) {
        return true;
    }

    else if (strcmp(word, "milk") == 0) {
        return true;
    }

    else if (strcmp(word, "chocolate") == 0) {
        return true;
    }

    else if (strcmp(word, "white") == 0) {
        return true;
    }

    else if (strcmp(word, "juice") == 0) {
        return true;
    }

    else if (strcmp(word, "water") == 0) {
        return true;
    }

    else {
        return false;
    }
}

bool is_debug_cmd(char word[MAX_LEN], char input[MAX_LEN]) {
    if (strcmp(word, "debug") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "add_item") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "sub_item") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "test_order") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "reset_order") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "edit_order") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "edit_menu") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "edit_all") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "random_menu") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "random_order") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "restore_menu") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "show_command") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "show_tax") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "change_tax") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "change_menu") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "calculator") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "warning_mode") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else if (strcmp(word, "help") == 0 && input[0] == FORWARDSLASH) {
        return true;
    }

    else {
        return false;
    }
}

bool is_modifier(char word[MAX_LEN]) {
    char *pointer = word;

    singularize(pointer);

    if (strcmp(word, "deluxe") == 0) {
        return true;
    }

    else if (strcmp(word, "meal") == 0) {
        return true;
    }

    else if (strcmp(word, "spicy") == 0) {
        return true;
    }

    else if (strcmp(word, "double") == 0) {
        return true;
    }

    else if (strcmp(word, "triple") == 0) {
        return true;
    }

    else if (strcmp(word, "extra") == 0) {
        return true;
    }

    else {
        return false;
    }
}

bool is_numword(char word[MAX_LEN]) {
    int value = number_word_to_value(word);

    if (value != -1) {
        return true;
    }

    else {
        return false;
    }
}

int tokenize(char input[], struct Order *order_pointer, struct AppState *app_pointer) {
    char tokens[50][200]; // Input with more than 50 tokens is undefined behavior.
    int token_count = 0;

    char current_word[200];
    int index = 0, cur_index = 0;

    char lower_case[200] = {0};

    // Collects multiple item-based words before parsing them.
    char *item_words[20];
    int item_word_count = 0;

    // Collects multiple modifier-based words before parsing them.
    char *modifier_words[20];
    int modifier_word_count = 0;

    // Collects number-words before parsing them.
    char *number_words[20];
    int number_word_count = 0;

    order_pointer->num = 0;
    order_pointer->size = 0;
    order_pointer->item = 0;
    order_pointer->modifier = 0;
    order_pointer->debug = 0;

    // This for loop makes the array all into lowercase.
    for (index = 0; input[index] != '\0'; index++) {
        lower_case[index] = tolower(input[index]);
        input[index] = lower_case[index];
    }

    for (index = 0; input[index] != '\0'; index++) {

        // Capital/lowercase letter or digit.
        if ( (input[index] >= NUM_START && input[index] <= NUM_END) ||
            (input[index] >= CAPITAL_START && input[index] <= CAPITAL_END) ||
            (input[index] >= LOWER_START && input[index] <= LOWER_END) ) {
            current_word[cur_index] = input[index];
            cur_index++;
        }

        else if (input[index] == UNDERSCORE || input[index] == PERIOD) {
            current_word[cur_index] = input[index];
            cur_index++;
        }

        // Space, newline, or hyphen.
        else if (input[index] == WHITE_SPACE || input[index] == NEWLINE || input[index] == HYPHEN) {
            if (cur_index < MAX_LEN - 1)  {
                current_word[cur_index] = '\0'; // End the word.

                // Fixes out-of-bounds segfault.
                if (token_count < MAX_TOKENS) {
                    strcpy(tokens[token_count], current_word);
                    token_count++;
                    memset(current_word, 0, sizeof(current_word));
                    cur_index = 0; // Resets token.
                }

                else {
                    fprintf(stderr, "\nToo many tokens, truncating input...\n");
                }
            }
        }
    }

    // End of string case.
    if (cur_index > 0) {
        current_word[cur_index] = '\0';
        strcpy(tokens[token_count], current_word);
        token_count++;
    }

    // Print tokens to see if it works.
    for (int i = 0; i < token_count; i++) {
        printf("Token %d: %s\n", i, tokens[i]);

        if (is_number(tokens[i])) {
            order_pointer->num = atoi(tokens[i]);
        }

        else if (is_size(tokens[i])) {
            if (strcmp(tokens[i], "sm") == 0) {
                strcpy(tokens[i], "small");
            }

            else if (strcmp(tokens[i], "md") == 0) {
                strcpy(tokens[i], "medium");
            }

            else if (strcmp(tokens[i], "lg") == 0) {
                strcpy(tokens[i], "large");
            }

            else if (strcmp(tokens[i], "pc") == 0) {
                strcpy(tokens[i], "piece");
            }

            order_pointer->size = ascii_word(tokens[i]) + SIZE_CONST;
        }

        else if (is_item(tokens[i])) {
            char *pointer = tokens[i];

            singularize(pointer);

            if (item_word_count < MAX_ITEM_WORDS) {
                item_words[item_word_count++] = tokens[i];
            }

            continue;
        }

        else if (is_debug_cmd(tokens[i], input)) {
            order_pointer->debug = ascii_word(tokens[i]) + DEBUG_CONST;
            // printf("\nDebug!\n");
        }

        else if (is_modifier(tokens[i])) {
            char *pointer = tokens[i];

            singularize(pointer);

            if (modifier_word_count < MAX_MOD_WORDS) {
                modifier_words[modifier_word_count++] = tokens[i];
            }

            continue;
        }

        else if (is_numword(tokens[i])) {
            if (number_word_count < MAX_NUM_WORDS) {
                number_words[number_word_count++] = tokens[i];
            }

            continue;
        }

        else {
            ;// printf("\nERROR!\n");
        }
    }

    // Parses multi-word items if any were found.
    if (item_word_count > 0) {
        order_pointer->item = parse_item_words(item_words, item_word_count);
    }

    // Parses multi-word modifiers if any were found.
    if (modifier_word_count > 0) {
        order_pointer->modifier = parse_modifier_words(modifier_words, modifier_word_count);
    }

    // Parses multi-word number if any were found.
    if (number_word_count > 0) {
        order_pointer->num = parse_number_words(number_words, number_word_count);
    }

    // Tries every token combination as a possible multi-word item.
    for (int i = 0; i < token_count; i++) {
        for (int j = i; j < token_count; j++) {

            char phrase[200];
            join_tokens(phrase, tokens, i, j);

            // Splits the phrase into words[] by '_' characters
            char phrase_copy[200];
            strcpy(phrase_copy, phrase);

            char *words2[10];
            int wcount = 0;

            char *tmp = strtok(phrase_copy, "_");
            while (tmp && wcount < 10) {
                words2[wcount++] = tmp;
                tmp = strtok(NULL, "_");
            }

            // Converts words into hashed ID using existing logic.
            int foreign_id = parse_item_words(words2, wcount);

            // Checks if the ID exists in dynamic menu
            if (match_dynamic_item_id(foreign_id, app_pointer) != -1) {
                order_pointer->item = foreign_id;
            }
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define WHITE_SPACE 32
#define NEWLINE 10
#define NUM_START 48
#define NUM_END 57
#define CAPITAL_START 65
#define CAPITAL_END 90
#define LOWER_START 97
#define LOWER_END 122

int ascii_word(char word[40]) {
    int sum = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        sum += word[i];
    }

    return sum;
}

bool is_number(char word[40]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!(word[i] >= NUM_START && word[i] <= NUM_END)) {
            return false; // Found a non-digit
        }
    }
    return true; // All characters were digits
}

bool is_size(char word[40]) {
    if (strcmp(word, "sm") == 0) {
        return true;
    }

    else if (strcmp(word, "md") == 0) {
        return true;
    }

    else if (strcmp(word, "lg") == 0) {
        return true;
    }

    else {
        return false;
    }
}

bool is_item(char word[40]) {
    if (strcmp(word, "fry") == 0) {
        return true;
    }

    else if (strcmp(word, "fries") == 0) {
        return true;
    }

    else if (strcmp(word, "burger") == 0) {
        return true;
    }

    else if (strcmp(word, "nuggets") == 0) {
        return true;
    }

    else {
        return false;
    }
}

int main() {
    char input[40];
    char tokens[10][20];
    int token_count = 0;

    char current_word[20];
    int index = 0;
    int cur_index = 0;

    int num, size, item;

    char lower_case[40] = {0};

    printf("Enter what you want: \n");
    fgets(input, sizeof(input), stdin);

    // This for loop makes it the array all into lowercase.
    for (index = 0; input[index] != '\0'; index++) {
        lower_case[index] = tolower(input[index]);
        input[index] = lower_case[index];
    }

    for (index = 0; input[index] != '\0'; index++) {

        // Letter or digit.
        if ( (input[index] >= NUM_START && input[index] <= NUM_END) ||
            (input[index] >= CAPITAL_START && input[index] <= CAPITAL_END) ||
            (input[index] >= LOWER_START && input[index] <= LOWER_END) )
        {
            current_word[cur_index] = input[index];
            cur_index++;
        }

        // Space or newline.
        else if (input[index] == WHITE_SPACE || input[index] == NEWLINE) {
            if (cur_index > 0) {
                current_word[cur_index] = '\0';     // End word.
                strcpy(tokens[token_count], current_word);
                token_count++;
                memset(current_word, 0, sizeof(current_word));
                cur_index = 0;                      // Reset token.
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
            num = ascii_word(tokens[i]);
        }

        else if (is_size(tokens[i])) {
            size = ascii_word(tokens[i]);
        }

        else if (is_item(tokens[i])) {
            item = ascii_word(tokens[i]);
        }

        else {
            printf("ERROR!");
        }
    }

    printf("\nFinal numeric tokens:\n");
    printf("num = %d\n", num);
    printf("size = %d\n", size);
    printf("item = %d\n", item);

    return 0;
}
